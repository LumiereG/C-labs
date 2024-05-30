#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>


#define M 11			//liczba wierszy szarady
#define GWIAZDKA '*'

typedef struct szarada {
	
	char* rozw[M];		//rozwiązana krzyzówka zapisana wierszami (o różnych długościach)

	char* todo[M];		//todo krzyżówka przygotowana do rozwiązywania

	char* poziomo;		//opisy poziomo
	char* pionowo;		//opisy pionowo

} szarada;


//ETAP 1
int start(szarada* sz, const char* d[], const char* poziomo, const char* pionowo);
void wypisz_opis(char* s);
void wypisz(szarada sz, int filled);	//filled: 0 (wypisz rozw) , 1 (wypisz todo)
//ETAP 2
void wykropkuj_opis(char* s, int i);	//wykropkuj opis i-go hasła (i-indeks)
int szukaj_haslo_poziomo(szarada sz, char* haslo); //zwraca 1 gdy znaleziono haslo w wierszu, wpp 0
//ETAP 3
//int szukaj_haslo_pionowo(szarada sz, char* haslo); //zwraca 1 gdy znaleziono haslo w kolumnie, wpp 0
//ETAP 4 (gotowy)
void zwolnij(szarada* sz);


//--------------------------------------------------------------------------------------------------
int main()
{
	//nie kasuj tutaj żadnych znaków !!!
	const char* d[M] = {" J C P  Z", "AUREOLA E   O", " L N A  LAGER", "CIOTUCHNA   N",
				  " A  K   SPISA",  "G E L   T   K", "R D A   W", "A Y DARMOZJAD",
				  "FOTKA  I U", "  O C  LUZ",  "  RYZA A A" };
	const char* poziomo = "**nad glowa swietego*piwo dolnej fermentacji*ciotka, ciocia,..."
		                  "*bron drzewcowa, pika***nic nie robi, ale apetyt ma"
		                  "*sweet focia, selfie*styl bycia, zycia*piecset arkuszy papieru";
	const char* pionowo = "*diagram*stala w Weronie na balkonie*wydawca"
						  "*amerykanski grosz*autor podlogi z plytek*np miejski rynek"
						  "**morska lub angielska*zlom, szmels"
						  "*imie zenskie***pasmo w Tatrach Zachodnich";
	
	szarada sz;

	int liczba_hasel = 0;		//zlicza odgadnięte hasła przy rozwiązywaniu szarady
	
	//---------------------------------------------------------------------------------------------
	
	if (!start(&sz, d, poziomo, pionowo)) { printf("\nKONIEC");  return 0; }

	printf("\n\nROZWIAZANA szarada\n\n"); //tylko na początku wypisujemy kontrolnie
	wypisz(sz, 1);
	printf("\n\ntodo szarada\n\n");
	wypisz(sz, 0);

	
	printf("\n\nROZWIAZYWANIE\n");

	do
	{
		char haslo[100] = { 0 };	//tablica do wczytywania hasła
		int k;

		printf("\n\nPodaj wyraz do wpisania \n(DUZYMI LITERAMI i bez polskich liter): ");
        scanf_s("%99s", haslo, 100);
		

		if (strcmp(haslo, "*") == 0) break;

		//szukamy wyrazu w wierszach
		k = szukaj_haslo_poziomo(sz, haslo);

		//if (k == 0)
			//teraz będziemy szukać wyrazu w kolumnach; 
			//k = szukaj_haslo_pionowo(sz, haslo);
		
		wypisz(sz, 0);
		liczba_hasel += k;

	} while (1);

	zwolnij(&sz);
	
	printf("\n-------------------------------------");
	printf("\nLiczba hasel=%d\n", liczba_hasel);   //ile haseł odgadnięto?
	printf("\n-------------------------------------");
	

	printf("\n\n*** WESOLYCH SWIAT !!! ***\n\n");
	return 0;
}

//---------------------------------------------------
//poniżej zaimplementuj wymagane funkcje
int start(szarada* sz, const char* d[], const char* poziomo, const char* pionowo)
{
	sz->pionowo = (char*)malloc(strlen(pionowo)+1);
	sz->poziomo = (char*)malloc(strlen(poziomo)+1);
	sz->pionowo = strcpy(sz->pionowo, pionowo);
	sz->poziomo = strcpy(sz->poziomo, poziomo);
	for (int i = 0; i < M; i++)
	{
		*(sz->rozw+i) = (char*)malloc(sizeof(char)* (strlen(d[i])+1));
		*(sz->todo+i) = (char*)malloc(sizeof(char)* (strlen(d[i])+1));
	}
	for (int i = 0; i < M; i++)
	{
		sz->rozw[i] = strcpy(sz->rozw[i], d[i]);
	}
	for (int i = 0; i < M; i++)
	{
		sz->todo[i] = strcpy(sz->todo[i], d[i]);
		for (int j = 0; j < strlen(d[i]); j++)
		{
			if (sz->todo[i][j] == ' ') continue;
			else { sz->todo[i][j] = GWIAZDKA; }
		}
	}
	return 1;
}
void wypisz_opis(char* s)
{
	/*char* p = s;
	for (int i = 0; i < strlen(s); i++)
	{
		if (*p == GWIAZDKA) continue;
		printf("%c", p);
	}*/
	char* p1 = NULL;
	p1 = (char*)malloc(strlen(s) + 1);
	char seps[] = "*";
	for (int i = 0; i < strlen(s); i++)
		*(p1 + i) = *(s + i);
	*(p1 + strlen(s) - 1) = '\0';
	char *token = strtok(p1, seps);
	int i = 1;
	while (token != NULL)
	{
		printf("%d. %s\n",i, token);
		token = strtok(NULL, seps);
		i++;
	}
	printf("%s\n", s);
}
void wypisz(szarada sz, int filled)
{
	if (filled == 1)
	{
		for (int i = 0; i < M; i++)
			printf("%s\n", sz.rozw[i]);
	}
	if (filled == 0)
	{
		for (int i = 0; i < M; i++)
			printf("%s\n", sz.todo[i]);
	}
	printf("poziomo\n");
	wypisz_opis(sz.poziomo);
	printf("pionowo\n");
	wypisz_opis(sz.pionowo);
}
int szukaj_haslo_poziomo(szarada sz, char* haslo)
{
	for (int i = 0; i < M; i++)
	{
		char* wynik = strstr(sz.rozw[i], haslo);
		if (wynik == NULL) continue;
		for (int j = 0; j < strlen(haslo); j++)
			sz.todo[i][j] = haslo[i];
	}
	return 1;
}
//----------------------------------------------------------
void zwolnij(szarada* sz)	//gotowa
{
	int i;

	for (i = 0; i < M; i++)
	{
		free(sz->rozw[i]);
		free(sz->todo[i]);
	}
	free(sz->poziomo);
	free(sz->pionowo);
	sz->poziomo = sz->pionowo = NULL;
}
//-----------------------------------------------------------


