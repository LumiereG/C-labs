#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define N 25		//liczba kart: A♥ + 12 par (kiery i kara): od 2♥ do K♥, od 2♦ do K♦
#define AS 12
#define KOLOR 13	

//-----------------------------------------------------
typedef struct karta {
	int kolor;	//tylko kier i karo (♥ oraz ♦)
	int wartosc; //0 do 12, jedna karta o wartości 13 (co odpowiada A♥)
}karta;

typedef struct karty {
	karta* k;
	int n;	//liczba kart w dynamicznej tablicy k (jednocześnie jej rozmiar)
}karty;

//-----------------------------------------------------
//ETAP1 ( 1.5p )
int init(karty*);
void wypisz_karte(karta);	//wypisanie pojedynczej karty
void wypisz(karty);		//tutaj wykorzystaj funkcję wypisz_karte

////ETAP2 ( 1.5p )
void tasuj(karty);
int rozdaj(karty*, karty*, karty*);
//
////ETAP3 ( 2p )
void usuwaj_karte(karty* g, int nr); 
void usuwaj_pary(karty* g);
//
////ETAP4 ( 2p )
int wyciagnij_karte(karty* g1, karty* g2);
int gra(karty* g1, karty* g2);

//-----------------------------------------------------
int main()
{
	karty talia = { NULL,0 }, g1 = { NULL,0 }, g2 = { NULL,0 };


	//ETAP1
	printf("\n---------- KARTY:\n");
	if (!init(&talia))
	{
		printf("\ninit - nie zakupiono kart !!!\n");
		return 0;
	}
	wypisz(talia);

	////ETAP2
	srand((unsigned)time(NULL));
	printf("\n---------- POTASOWANE:\n");
	tasuj(talia);
	wypisz(talia);

	printf("\n----------- ROZDANIE KART:\n");
	if (!rozdaj(&talia, &g1, &g2))
	{
		printf("\nrozdaj - nie rozdano kart !!!\n");
		free(talia.k);
		return 0;
	}
	printf("\nKARTY gracza G1\n");
	wypisz(g1);
	printf("\nKARTY gracza G2\n");
	wypisz(g2);

	//
	////ETAP3
	printf("\n----------- USUWANIE PAR u graczy:\n");
	usuwaj_pary(&g1);
	printf("\nG1 - karty po USUWANIU par\n");
	wypisz(g1);
	usuwaj_pary(&g2);
	printf("\nG2 - karty po USUWANIU par\n");
	wypisz(g2);
	//
	////ETAP4
	printf("\n----------- GRA:\n");
	if (gra(&g1,&g2))
		printf("\nWygrywam G1 !!!\n");
	else
		printf("\nWygrywa G2 !!!\n");


	printf("\n----------- KONIEC\n");
	if (talia.n > 0) free(talia.k);
	if (g1.n > 0) free(g1.k);
	if (g2.n > 0) free(g2.k);

	return 0;
}




//---------------------------------------------------
int gra(karty* g1, karty* g2)
{
	int gra_g1=0;
	int starcie = 1;

	if (g1->n < g2->n)	// zaczyna - ten kto ma mniej kart
		gra_g1 = 1;

	// aż nie zostanie ktoś z Asem (czyli ktoś nie ma już kart) - ciągnij na zmianę
	while(g1->n > 0 && g2->n > 0)
	{
		printf("\nSTARCIE %d  ", starcie++);

		if (gra_g1)
		{
			printf(", G1 wyciaga karte od G2  ");
			wyciagnij_karte(g1,g2);
			gra_g1 = 0;
		}
		else
		{
			printf(", G2 wyciaga karte od G1  ");
			wyciagnij_karte(g2,g1);
			gra_g1 = 1;
		}
		// wyświetl karty
		printf("\nkarty G1: ");
		wypisz(*g1);
		printf("\nkarty G2: ");
		wypisz(*g2);
	}

	if (g1->n > 0) return 0;
	return 1;

}//----------------------------------------------------
int init(karty* talia)
{
	talia->k = (karta*)malloc(N * sizeof(karta));
	if (talia->k == NULL) return 0;
	talia->n = N;
	for (int i = 0; i < N; i++)
	{
		talia->k[i].kolor = i / KOLOR;
		talia->k[i].wartosc = i % KOLOR;
	}
	return 1;
}
void wypisz_karte(karta k)
{
	switch (k.wartosc)
	{
	case 9:
		printf("J");
		break;
	case 10:
		printf("Q");
		break;
	case 11:
		printf("K");
		break;
	case 12:
		printf("A");
		break;
	default:
		printf("%d", k.wartosc + 2);
	}
	printf("%c ", (char)k.kolor + 3);
}
void wypisz(karty talia)
{
	for (int i = 0; i < talia.n; i++)
	{
		wypisz_karte(talia.k[i]);
	}
}
void tasuj(karty talia)
{
	for (int i = 0; i < talia.n; i++)
	{
		int j = rand() % N;
		karta tmp = talia.k[j];
		talia.k[j] = talia.k[i];
		talia.k[i] = tmp;
	}
}
int rozdaj(karty* talia, karty* g1, karty* g2)
{
	g1->k = (karty*)calloc(N / 2 + 1, sizeof(karta));
	if (g1->k == NULL) return 0;
	g2->k = (karty*)calloc(talia->n / 2, sizeof(karta));
	if (g2->k == NULL) return 0;
	for (int i = 0; i < talia->n; i++)
	{
		if (i % 2 == 0)
		{
			g1->k[i / 2].kolor = talia->k[i].kolor;
			g1->k[i / 2].wartosc = talia->k[i].wartosc;
		}
		else
		{
			g2->k[i / 2].kolor = talia->k[i].kolor;
			g2->k[i / 2].wartosc = talia->k[i].wartosc;
		}
	}
	g2->n = N/2;
	g1->n = N / 2 + 1;
	return 1;
}
void usuwaj_karte(karty* g, int nr)
{
	if (nr < 0 && nr>g->n -1) return;
	for (int i = nr; i < (g->n)-1; i++)
		g->k[i] = g->k[i + 1];
	g->k = (karty*)realloc(g->k, ((g->n) - 1)*sizeof(karta));
	g->n -=1;
}
void usuwaj_pary(karty* g)
{
	for(int i = 0; i < g->n -1; i++)
		for (int j = i+1; j < g->n; j++)
		{
			if (g->k[i].wartosc == g->k[j].wartosc)
			{
				usuwaj_karte(g, i);
				j = j - 1;
				i = i - 1;
				usuwaj_karte(g, j);
				j = j - 1;
				i = i - 1;
			}
		}
}
int wyciagnij_karte(karty* g1, karty* g2)
{
	int losowanie = rand() % g2->n;
	wypisz_karte(g2->k[losowanie]);
	if (g2->k[losowanie].wartosc == 12)
	{
		karta tmp = g2->k[losowanie];
		usuwaj_karte(g2, losowanie);
		g1->n += 1;
		g1->k = (karty*)calloc(g1->n, sizeof(karta));
		if (g1->k == NULL) return 0;
		g1->k[(g1->n)-1] = tmp;
	}
	else
	{
		int wart = g2->k[losowanie].wartosc;
		usuwaj_karte(g2, losowanie);
		for(int i = 0; i < g1->n; i++)
			if (g1->k[i].wartosc == wart)
			{
				usuwaj_karte(g1, i);
				break;
			}
	}
	return 1;
}






