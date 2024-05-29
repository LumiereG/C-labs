#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

//----------------------------------------------
#define  N  52		//iloœæ kart w talii
#define  KOLOR  13	//iloœæ kart w kolorze

#define  ILE 10	//ile staræ w grze
//----------------------------------------------

//ETAP1 (2pkt)
void init(int[], int);
void wypisz(int[], int);

////ETAP2 (2pkt)
void tasuj(int[], int);
void rozdaj(int* t, int n, int* g1, int* n_g1, int* g2, int* n_g2); //GOTOWA
int pierwsza_karta(int*, int*);
void dodaj_karte_na_koniec(int*, int*, int);
//
////ETAP3 (3pkt- w tym 1,5 pkt za wojnê)
int gra(int* g1, int* n_g1, int* g2, int* n_g2);
//void rozgrzewka(int karta1, int karta2);




//--------------------------------------------------------
int main()
{
	int nowa_talia[N];
	int g1[N], n_g1 = 0;	//tablica kart gracza g1 oraz liczba kart gracza
	int g2[N], n_g2 = 0;	//tablica kart gracza g2 oraz liczba kart gracza

	//ETAP1
	printf("\n\n---------  NOWA TALIA KART:\n");
	init(nowa_talia, N);
	wypisz(nowa_talia, N);

	//ETAP2
	srand((unsigned)time(NULL));
	printf("\n\n---------  POTASOWANA TALIA KART:\n");
	tasuj(nowa_talia, N);
	wypisz(nowa_talia, N);

	rozdaj(nowa_talia, N, g1, &n_g1, g2, &n_g2);	//GOTOWA
	printf("\n\n---------  KARTY GRACZA g1:\n");
	wypisz(g1, n_g1);
	printf("\n\n---------  KARTY GRACZA g2:\n");
	wypisz(g2, n_g2);

	//ETAP3
	printf("\n\n----------  ROZGRYWKA:\n");
	int kto = gra(g1, &n_g1, g2, &n_g2);

	if (kto > 0)
		printf("\nWygrywa g%d !!! GRATULACJE !!!\n", kto);
	else
		printf("\nREMIS !!!\n");


	return 0;
}

//-----------------------------------------
void init(int tab[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		tab[i] = i;

}
//-----------------------------------------
void wypisz(int tab[], int n)
{
	int i, kolor, wartosc;
	for (i = 0; i < n; i++)
	{
		kolor = tab[i] / KOLOR;
		wartosc = tab[i] % KOLOR;
		switch (wartosc)
		{
		case 0:
			printf("2");
			break;
		case 1:
			printf("3");
			break;
		case 2:
			printf("4");
			break;
		case 3:
			printf("5");
			break;
		case 4:
			printf("6");
			break;
		case 5:
			printf("7");
			break;
		case 6:
			printf("8");
			break;
		case 7:
			printf("9");
			break;
		case 8:
			printf("10");
			break;
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
		}
		switch (kolor)
		{
		case 0:
			printf("%c ", 3);
			break;
		case 1:
			printf("%c ", 4);
			break;
		case 2:
			printf("%c ", 5);
			break;
		case 3:
			printf("%c ", 6);
			break;
		}
	}
}

//-----------------------------------------
void tasuj(int tab[], int n)
{
	int i, j, tmp;
	for (i = 0; i < n; i++)
	{
		j = rand() % 52;
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
	}
}
//--------------------------------------------
void rozdaj(int* t, int n, int* g1, int* n_g1, int* g2, int* n_g2)
{
	while (n > 0)
	{
		dodaj_karte_na_koniec(g1, n_g1, pierwsza_karta(t, &n));
		dodaj_karte_na_koniec(g2, n_g2, pierwsza_karta(t, &n));
	}
}
//----------------------------------------------
int pierwsza_karta(int* g1, int* n)
{
	int i, karta;
	karta = g1[0];
	*n = *n - 1;
	for (i = 0; i < *n; i++)
	{
		g1[i] = g1[i + 1];
	}
	return karta;
}
//----------------------------------------------
void dodaj_karte_na_koniec(int g[], int* n, int karta)
{
	if (*n < N) {
		g[*n] = karta;
	}
	*n = *n + 1;
}
//----------------------------------------------
int gra(int* g1, int* n_g1, int* g2, int* n_g2)
{
	for (int i = 0; i < ILE && n_g1>0 && n_g2 > 0; ++i)
	{
		int n = 0;
		printf("\n\nSTARCIE nr=%d\n", i + 1);
		do
		{
			if (*g1 % KOLOR > *g2 % KOLOR)
			{
				printf("Karty zabiera gracz g1\n");
				g1 -= n;
				g2 -= n;
				for (int i = 0; i <= n; i++)
				{
					dodaj_karte_na_koniec(g1, n_g1, pierwsza_karta(g1, n_g1));
					dodaj_karte_na_koniec(g1, n_g1, pierwsza_karta(g2, n_g2));
				}
				printf("G1: ");
				wypisz(g1, *n_g1);
				printf("\n");
				printf("G2: ");
				wypisz(g2, *n_g2);
				break;
			}
			if (*g1 % KOLOR < *g2 % KOLOR)
			{
				printf("Karty zabiera gracz g2\n");
				g1 -= n;
				g2 -= n;
				for (int i = 0; i <= n; i++)
				{
					dodaj_karte_na_koniec(g2, n_g2, pierwsza_karta(g1, n_g1));
					dodaj_karte_na_koniec(g2, n_g2, pierwsza_karta(g2, n_g2));
				}
				printf("G1: ");
				wypisz(g1, *n_g1);
				printf("\n");
				printf("G2: ");
				wypisz(g2, *n_g2);
				break;
			}
			printf("Wojna! \n");
			n++;
			g1++;
			g2++;
		} while (*(g1 - 1) % KOLOR == *(g2 - 1) % KOLOR);

	}

	if (*n_g1 > *n_g2)	return 1;	//ostatecznie decyduje liczba kart gracza
	if (*n_g1 < *n_g2)	return 2;

	return 0;

}
//----------------------------------------------





