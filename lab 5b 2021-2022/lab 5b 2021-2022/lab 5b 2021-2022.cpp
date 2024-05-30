#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

typedef struct tekst
{
	int ilosc_znakow;
	char* lancuch;
} tekst;

void wyswietl(const char* T[], int ilosc_wierszy);
tekst* tekst_2_struktura(const char* T[], int ilosc_wierszy);
void przetwarzanie_wstepne(tekst* T,const char* znaki_do_usuniecia);
void male(tekst* T);
void zamiana_dwuznakow(tekst* T, const char* DW, char z);

int main(void)
{
	unsigned int ilosc_wierszy = 0;
	const char* do_usuniecia = ".,!@#$%^&*()-+—_?<>:;'%%\"\\/–\n";
	tekst* T_0;

	const char* azazel[] = {
	"Joseph Heller - Paragraf 22",
	"_____________________________",
	"1 Teksańczyk",
	"Była to miłość od pierwszego wejrzenia.",
	"Kiedy Yossarian po raz pierwszy ujrzał kapelana, natychmiast zapałał do niego szalonym uczuciem.",
	"Yossarian leżał w szpitalu z bólami wątroby, które jakoś nie mogły się przerodzić w pospolitą",
	"żółtaczkę. Lekarzy zbijało to z tropu. Gdyby to była żółtaczka, mogliby przystąpić do leczenia.",
	"Gdyby to nie była żółtaczka i bóle ustąpiłyby same, mogliby go wypisać ze szpitala. Tymczasem fakt,",
	"że było to cały czas takie ni to, ni owo, wprawiał ich w zakłopotanie.",
	"Codziennie rano przychodziło trzech energicznych, poważnych dżentelmenów, wygadanych i krótkowzrocznych,",
	"w asyście równie energicznej i poważnej siostry Duckett, jednej z pielęgniarek,",
	"które nie lubiły Yossariana. Oglądali kartę choroby wiszącą w nogach łóżka i wypytywali go",
	"niecierpliwie o bóle. Denerwowało ich, kiedy mówił, że bóle są takie same jak dotychczas." };

	setlocale(LC_ALL, "Polish"); //polskie znaki w konsoli

	ilosc_wierszy = sizeof(azazel) / sizeof(char*);

	//Etap 1
	printf("--------------");
	printf("\n--==ETAP 1==--\n");
	printf("--------------\n\n");
	wyswietl(azazel, ilosc_wierszy);

	////Etap 2
	printf("\n--------------");
	printf("\n--==ETAP 2==--\n");
	printf("--------------");
	T_0 = tekst_2_struktura(azazel, ilosc_wierszy);
	printf("\n\n%s\n", T_0->lancuch);
	printf("\nIlość znaków: %d", T_0->ilosc_znakow);

	////Etap 3
	printf("\n\n--------------");
	printf("\n--==ETAP 3==--\n");
	printf("--------------");
	male(T_0);
	przetwarzanie_wstepne(T_0, do_usuniecia);
	printf("\n\n%s\n", T_0->lancuch);
	printf("\nIlość znaków: %d", T_0->ilosc_znakow);

	////Etap 4
	printf("\n\n--------------");
	printf("\n--==ETAP 4==--\n");
	printf("--------------");
	zamiana_dwuznakow(T_0, "rz", 'ż');
	zamiana_dwuznakow(T_0, "sz", 'S');
	zamiana_dwuznakow(T_0, "cz", 'C');
	zamiana_dwuznakow(T_0, "dz", 'D');
	zamiana_dwuznakow(T_0, "ch", 'h');
	printf("\n\n%s\n", T_0->lancuch);
	printf("\nIlość znaków: %d", T_0->ilosc_znakow);

	//free(T_0);
	printf("\n\n");
	system("pause");
	return 0;
}
void wyswietl(const char* T[], int ilosc_wierszy)
{
	for (int i = 0; i < ilosc_wierszy; i++)
		printf("%s\n", T[i]);
}
tekst* tekst_2_struktura(const char* T[], int ilosc_wierszy)
{
	int tmp = 0;
	for (int i = 0; i < ilosc_wierszy; i++)
		tmp += strlen(T[i]);
	tekst* tab = (tekst*)malloc(sizeof(tekst));
	tab->ilosc_znakow = tmp + ilosc_wierszy-1;
	tab->lancuch = (char*)calloc(tab->ilosc_znakow, sizeof(char));
	tmp = 0;
	for (int i = 0; i < ilosc_wierszy; i++)
	{
		for (int j = 0; j < strlen(T[i]); j++)
		{
			*(tab->lancuch + tmp) = T[i][j];
			tmp++;
		}
		if (i == ilosc_wierszy - 1) continue;
		*(tab->lancuch + tmp) = ' ';
		tmp++;
	}
	*(tab->lancuch + tab->ilosc_znakow) = '\0';
	return tab;	
}
void male(tekst* T)
{
	for (int i = 0; i<T->ilosc_znakow; i++)
		if (T->lancuch[i] > 64 && T->lancuch[i] < 91) T->lancuch[i] += 32;
}
void przetwarzanie_wstepne(tekst* T, const char* znaki_do_usuniecia)
{
	char* p = T->lancuch;
	do
	{
		p = strpbrk(T->lancuch, znaki_do_usuniecia);
		if (p == NULL) break;
		for (int i = 0; i < (T->ilosc_znakow - 1 - (p - T->lancuch) / sizeof(char)); i++)
			*(p + i) = *(p + 1 + i);
		T->lancuch = (char*)realloc(T->lancuch, T->ilosc_znakow - 1);
		T->ilosc_znakow--;
		T->lancuch[T->ilosc_znakow] = '\0';
	} while (p);
}
void zamiana_dwuznakow(tekst* T, const char* DW, char z)
{
	char* p;
	do
	{
		p = strstr(T->lancuch, DW);
		if (p == NULL) break;
		for (int i = 0; i < (T->ilosc_znakow - 1 - (p+1 - T->lancuch) / sizeof(char)); i++)
			*(p+1 + i) = *(p + 2 + i);
		*p = z;
		T->lancuch = (char*)realloc(T->lancuch, T->ilosc_znakow - 1);
		T->ilosc_znakow--;
		T->lancuch[T->ilosc_znakow] = '\0';
	} while (p);
}