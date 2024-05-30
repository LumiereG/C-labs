#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Dane przechowywane w liœcie
typedef struct narzedzie
{
    const char* nazwa;
    int ilosc;
}tool;

// Typ elementów listy
typedef struct wezel
{
    tool* dane;
    struct wezel* nastepny;
    struct wezel* poprzedni;
} wezel;

// Lista
typedef struct lista_dwukierunkowa
{
    wezel* glowa, * ogon;
} lista_dwukierunkowa;

lista_dwukierunkowa* inicjalizacja(); //0.5p
int wstaw_na_koniec(lista_dwukierunkowa* L, const char* tool_name); //1.5p
void wypisz(lista_dwukierunkowa* L); //0.5p
int znajdz(lista_dwukierunkowa* L, const char* tool_name); //0.5p
void usun_wezel(lista_dwukierunkowa* L, int nr); //2.0p
void scal(lista_dwukierunkowa* L); //2.0p

int main()
{
    lista_dwukierunkowa* narzedzia_ogrodnicze;
    int i, nr, ok;
    wezel* n;

    //Etap 1 = 2.5 pkt
    printf("*******E T A P   1********\n");
    narzedzia_ogrodnicze = inicjalizacja();
    if (narzedzia_ogrodnicze && !narzedzia_ogrodnicze->glowa && !narzedzia_ogrodnicze->ogon) printf("Lista zainicjowana");
    else printf("Inicjalizacja sie nie powiodla");

    ok = wstaw_na_koniec(narzedzia_ogrodnicze, "grabie");
    if (ok) printf("\n\nDostepne narzedzia:\n%s, ilosc: %d", narzedzia_ogrodnicze->glowa->dane->nazwa, narzedzia_ogrodnicze->glowa->dane->ilosc);
    else printf("Dodanie narzedzi sie nie powiodlo");

    ok = wstaw_na_koniec(narzedzia_ogrodnicze, "szpadel");
    printf("\n\nDostepne narzedzia:\n");
    if (ok) wypisz(narzedzia_ogrodnicze);
    else printf("Dodanie narzedzi sie nie powiodlo");

    //Etap 2 = 2.5 pkt
    printf("\n\n*******E T A P   2********\n");
    wstaw_na_koniec(narzedzia_ogrodnicze, "sekator");
    printf("Dostepne narzedzia:\n");
    wypisz(narzedzia_ogrodnicze);
    nr = znajdz(narzedzia_ogrodnicze, "grabie");
    if (nr >= 0)
    {
        n = narzedzia_ogrodnicze->glowa;
        for (i = 0; i < nr; i++) n = n->nastepny;
        printf("\n\nZnaleziono: %s, ilosc: %d", n->dane->nazwa, n->dane->ilosc);
    }
    else printf("Nie ma takiego narzedzia");
    usun_wezel(narzedzia_ogrodnicze, nr);
    printf("\nPo usunieciu:\n");
    wypisz(narzedzia_ogrodnicze);
    nr = znajdz(narzedzia_ogrodnicze, "szpadel");
    if (nr >= 0)
    {
        n = narzedzia_ogrodnicze->glowa;
        for (i = 0; i < nr; i++) n = n->nastepny;
        printf("\n\nZnaleziono: %s, ilosc: %d", n->dane->nazwa, n->dane->ilosc);
    }
    else printf("Nie ma takiego narzedzia");
    usun_wezel(narzedzia_ogrodnicze, nr);
    printf("\nPo usunieciu:\n");
    wypisz(narzedzia_ogrodnicze);
    nr = znajdz(narzedzia_ogrodnicze, "sekator");
    if (nr >= 0)
    {
        n = narzedzia_ogrodnicze->glowa;
        for (i = 0; i < nr; i++) n = n->nastepny;
        printf("\n\nZnaleziono: %s, ilosc: %d", n->dane->nazwa, n->dane->ilosc);
    }
    else printf("Nie ma takiego narzedzia");
    usun_wezel(narzedzia_ogrodnicze, nr);
    printf("\nPo usunieciu:\n");
    if (narzedzia_ogrodnicze->glowa) wypisz(narzedzia_ogrodnicze);
    else printf("Lista pusta");

    //Etap 3 = 2.0 pkt
    printf("\n\n*******E T A P   3********\n");
    wstaw_na_koniec(narzedzia_ogrodnicze, "sekator");
    wstaw_na_koniec(narzedzia_ogrodnicze, "szpadel");
    wstaw_na_koniec(narzedzia_ogrodnicze, "grabie");
    wstaw_na_koniec(narzedzia_ogrodnicze, "szpadel");
    wstaw_na_koniec(narzedzia_ogrodnicze, "grabie");
    wstaw_na_koniec(narzedzia_ogrodnicze, "grabie");
    printf("Dostepne narzedzia:\n");
    wypisz(narzedzia_ogrodnicze);
    scal(narzedzia_ogrodnicze);
    printf("\nPo scaleniu:\n");
    wypisz(narzedzia_ogrodnicze);


    nr = znajdz(narzedzia_ogrodnicze, "grabie");
    usun_wezel(narzedzia_ogrodnicze, nr);
    nr = znajdz(narzedzia_ogrodnicze, "szpadel");
    usun_wezel(narzedzia_ogrodnicze, nr);
    nr = znajdz(narzedzia_ogrodnicze, "sekator");
    usun_wezel(narzedzia_ogrodnicze, nr);
    if (!narzedzia_ogrodnicze->glowa && !narzedzia_ogrodnicze->ogon)
        printf("\n\n*******K O N I E C********\n");
    return 0;
}
lista_dwukierunkowa* inicjalizacja()
{
    lista_dwukierunkowa* list = (lista_dwukierunkowa*)malloc(sizeof(lista_dwukierunkowa));
    list->glowa = NULL;
    list->ogon = NULL;
    return list;
}
int wstaw_na_koniec(lista_dwukierunkowa* L, const char* tool_name)
{
    if (L->ogon == NULL || L->glowa == NULL)
    {
        wezel* new_node = (wezel*)malloc(sizeof(wezel));
        tool* new_dane = (tool*)malloc(sizeof(tool));
        new_dane->nazwa = tool_name;
        new_dane->ilosc = 1;
        new_node->dane = new_dane;
        if (!new_node) return 0;
        new_node->nastepny = NULL;
        new_node->poprzedni = NULL;
        L->ogon = new_node;
        L->glowa = new_node;
        return 1;
    }
    else
    {
        wezel* new_node = (wezel*)malloc(sizeof(wezel));
        tool* new_dane = (tool*)malloc(sizeof(tool));
        new_dane->nazwa = tool_name;
        new_dane->ilosc = 1;
        new_node->dane = new_dane;
        new_node->nastepny = NULL;
        new_node->poprzedni = L->ogon;
        L->ogon->nastepny = new_node;
        L -> ogon = new_node;
        return 1;
    }
}
void wypisz(lista_dwukierunkowa* L)
{
    wezel* tmp = L->glowa;
    while (tmp != NULL)
    {
        printf("%s, ilosc: %d\n", tmp->dane->nazwa, tmp->dane->ilosc);
        tmp = tmp->nastepny;
    }
}
int znajdz(lista_dwukierunkowa* L, const char* tool_name)
{
    wezel* tmp = L->glowa;
    int counter = 0;
    while (tmp != NULL)
    {
        if (strcmp(tmp->dane->nazwa, tool_name) == 0)
        {
            return counter;
        }
        tmp = tmp->nastepny;
        counter++;
    }
    return -1;
}
void usun_wezel(lista_dwukierunkowa* L, int nr)
{
    wezel* tmp = L->glowa;
    for (int i = 0; i < nr; i++)
    {
        tmp = tmp->nastepny;
    }
    if (tmp == L->glowa)
    {
        L->glowa = L->glowa->nastepny;
        if (L->glowa == NULL) return;
        L->glowa->poprzedni = NULL;
        free(tmp->dane);
        free(tmp);
        return;
    }
    if (tmp == L->ogon)
    {
        L->ogon = L->ogon->poprzedni;
        L->ogon->nastepny = NULL;
        free(tmp->dane);
        free(tmp);
        return;
    }
    tmp->poprzedni->nastepny = tmp->nastepny;
    tmp->nastepny->poprzedni = tmp->poprzedni;
    free(tmp->dane);
    free(tmp);
}
void scal(lista_dwukierunkowa* L)
{
    wezel* tmp = L->glowa;
    while (tmp != NULL)
    {
        wezel* p = tmp->nastepny;
        while (p != NULL)
        {
            if (strcmp(p->dane->nazwa, tmp->dane->nazwa) == 0)
            {
                wezel* k = p->nastepny;
                if (p == L->glowa)
                {
                    L->glowa = L->glowa->nastepny;
                    L->glowa->poprzedni = NULL;
                    free(p->dane);
                    free(p);
                    p = k;
                    tmp->dane->ilosc++;
                    continue;
                    
                }
                if (p == L->ogon)
                {
                    L->ogon = L->ogon->poprzedni;
                    L->ogon->nastepny = NULL;
                    free(p->dane);
                    free(p);
                    p = k;
                    tmp->dane->ilosc++;
                    continue;
                }
                p->poprzedni->nastepny = p->nastepny;
                p->nastepny->poprzedni = p->poprzedni;
                free(p->dane);
                free(p);
                p = k;
                tmp->dane->ilosc++;
                continue;
            }
            p = p->nastepny;
        }
        tmp = tmp->nastepny;
    }
}