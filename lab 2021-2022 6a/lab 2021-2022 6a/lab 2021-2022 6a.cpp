#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define N 17

typedef struct karta {
	const char* nazwa;
	struct karta* nast;
} karta;

typedef struct gracz {
	karta* glowa;
	karta* ogon;
}gracz;

//-----------------------------------------------------
//ETAP1 - 2pkt
karta* tworz_karte(const char* nazwa);
int wstaw(gracz* g, karta* k); //na koniec
int init(gracz* g, const char* karty_startowe[N]); //gotowa
void wypisz(gracz g);
void zwolnij(gracz* g);

//ETAP2 - 1,5pkt
void tasuj(gracz* g);
void rozdaj(gracz* karty, gracz* g1, gracz* g2);

//ETAP3 - 1,5pkt
void usuwaj_pary(gracz* g);

//ETAP4 - 2pkt
void usuwaj_karte(gracz* g, const char* nazwa);
void wyciagnij_karte(gracz* g1, gracz* g2);

//----------------------------
int gra(gracz* g1, gracz* g2); //gotowa

//-----------------------------------------------------
int main()
{
	const char* karty_startowe[N] = { "zyrafa","papuga","lew","kot","pies","tygrys","pantera","motyl","goryl",
								"puchacz","krokodyl","kaczka","szczur","mysz","bocian","krecik","piotrek" };

	gracz talia = { NULL,NULL }, g1 = { NULL,NULL }, g2 = { NULL,NULL };


	printf("\nETAP1------------------------------------------------\n");
	printf("\nKARTY:\n");
	if (!init(&talia, karty_startowe))
	{
		printf("\nNie ma kart do grania !!!\n");
		zwolnij(&talia);
		return 1;
	}
	wypisz(talia);

	printf("\nETAP2------------------------------------------------\n");
	srand(3);
	//srand((unsigned)time(NULL));

	printf("\nPOTASOWANE:\n");
	tasuj(&talia);
	//tasuj(&talia);	//ETAP3: zakomentuj, żeby nie było par u gracza
	wypisz(talia);

	rozdaj(&talia, &g1, &g2);
	printf("\nKARTY G1\n");
	wypisz(g1);
	printf("\nKARTY G2\n");
	wypisz(g2);

	printf("\nETAP3------------------------------------------------\n");
	usuwaj_pary(&g1);
	printf("\nKARTY G1 ( po USUWANIU par )\n");
	wypisz(g1);
	usuwaj_pary(&g2);
	printf("\nKARTY G2 ( po USUWANIU par )\n");
	wypisz(g2);

	printf("\nETAP4------------------------------------------------\n");
	////gra
	if (gra(&g1, &g2))
	printf("\nWygrywa G1 !!!\n");
	else
	printf("\nWygrywa G2 !!!\n");

	//zwolnij(&talia);
	//zwolnij(&g1);
	//zwolnij(&g2);

	return 0;
}

//IMPLEMENTACJE
//----------------------------------------------
karta* tworz_karte(const char* nazwa)
{
	karta* k = (karta*)malloc(sizeof(karta));
	k->nazwa = (const char*)malloc(strlen(nazwa) + 1);
	k->nazwa = nazwa;
	if (!k->nazwa || !k)
	{
		free((void*)k->nazwa);
		free(k);
		return NULL;
	}
	return k; // popraw to!
}
//----------------------------------------------
int wstaw(gracz* g, karta* k) //na koniec
{
	if (g->ogon == NULL)
	{
		g->glowa = k;
		g->ogon = k;
		k->nast = NULL;
		return 1;
	}
	g->ogon->nast = k;
	k->nast = NULL;
	g->ogon = k;
	return 1;
}

//----------------------------------------------
int init(gracz* g, const char* karty_startowe[N])  //gotowa
{

	for (int i = 0; i < N - 1; i++)
	{

		if (!wstaw(g, tworz_karte(karty_startowe[i]))) return 0;
		if (!wstaw(g, tworz_karte(karty_startowe[i]))) return 0;
	}

	//ostatnia karta pojedyncza (piotrek)
	if (!wstaw(g, tworz_karte(karty_startowe[N - 1]))) return 0;

	return 1;
}

//-----------------------------------------------

void wypisz(gracz g)
{
	karta* tmp = g.glowa;
	while (tmp != NULL)
	{
		printf("%s ", tmp->nazwa);
		tmp = tmp->nast;
	}
	printf("\n");
}
//-----------------------------------------------
void zwolnij(gracz* g)
{
	karta* tmp = g->glowa;
	while (tmp == NULL)
	{
		karta* p = tmp->nast;
		free(tmp);
		tmp = p;
	}
	free(g);
}

//--------------------------------------------------
void usuwaj_pary(gracz* g)
{
	karta* k = g->glowa;
	while (k != NULL)
	{
		karta* tmp = k->nast;

		if (tmp != NULL)
		{
			while ((tmp->nast != k) && (tmp->nast != NULL))
			{
				tmp = tmp->nast;
			}
			if (tmp->nast == k)
			{
				if (tmp->nast == g->ogon) g->ogon = tmp;
				tmp->nast = tmp->nast->nast;
				if (k == g->glowa) g->glowa == k->nast;
				else
				{
					karta* o = g->glowa;
					while (o->nast != k)
					{
						o = o->nast;
					}
					o->nast = k->nast;
					k = o->nast;
					continue;
				}
			}
		}
		k = k->nast;
	}
}
//--------------------------------------------------
void usuwaj_karte(gracz* g, const char* nazwa)	//usuwaj 1 karte o podanej nazwie
{
	karta* tmp = g->glowa;
	if (tmp->nazwa == nazwa)
	{
		g->glowa = tmp->nast;
		return;
	}
	while (tmp->nast->nazwa != nazwa && tmp->nast != NULL)
	{
		tmp = tmp->nast;
	}
	if (tmp->nast->nazwa == nazwa)
	{
		if (tmp->nast == g->ogon) g->ogon = tmp;
		tmp->nast = tmp->nast->nast;
		return;
	}
}
//--------------------------------------------------
void wyciagnij_karte(gracz* g1, gracz* g2)
{
	karta* k = g2->glowa;
	if (strcmp("piotrek", k->nazwa) == 0)
	{
		usuwaj_karte(g2, k->nazwa);
		wstaw(g1, k);
	}
	else
	{
		g2->glowa = g2->glowa->nast;
		usuwaj_karte(g1, k->nazwa);
	}
}

//---------------------------------------------------
int gra(gracz* g1, gracz* g2) //gotowa
{
	int gra_g1 = 1;
	int starcie = 1;

	// aż nie zostanie ktoś z Piotrkiem (czyli ktoś nie ma już kart) - ciągnij na zmianę
	while (g1->glowa && g2->glowa)
	{
		printf("\nSTARCIE %d", starcie++);
		//if (starcie > 100) break;

		if (gra_g1)
		{
			wyciagnij_karte(g1, g2);		//G1 bierze kartę od G2
			gra_g1 = 0;
		}
		else
		{
			wyciagnij_karte(g2, g1);		//G2 bierze kartę od G1
			gra_g1 = 1;
		}

		// wyświetl karty
		printf("\nkarty G1: ");
		wypisz(*g1);
		printf("\nkarty G2: ");
		wypisz(*g2);
	}

	if (g1->glowa) return 0;

	return 1;

}//----------------------------------------------------
void tasuj(gracz* g)
{
	karta* tmp = g->glowa;
	int j;
	while (tmp != NULL)
	{
		karta* k = g->glowa;
		j = rand() % 8;
		if (j == 1 || j == 2 || j == 3)
		{
			if (tmp != g->glowa)
			{
				while (k->nast != tmp)
				{
					k = k->nast;
				}
				k->nast = tmp->nast;
				tmp->nast = g->glowa;
				g->glowa = tmp;
				tmp = k->nast;
				continue;
			}
		}
		tmp = tmp->nast;
	}
}
void rozdaj(gracz* karty, gracz* g1, gracz* g2)
{
	int i =0;
	while (karty->glowa != NULL)
	{
		karta* k = karty->glowa;
		karty->glowa = k->nast;
		if (i % 2 == 0) wstaw(g1, k);
		else wstaw(g2, k);
		i++;
	}
}










