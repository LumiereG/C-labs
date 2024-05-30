#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 

#define LIMIT 100

// Dane osobowe
//-------------
typedef struct osoba
{
	char imie[LIMIT];
	char nazwisko[LIMIT];
}osoba;

// Dane przechowywane w liście
//----------------------------
typedef struct samochod
{
	const char* model;
	osoba* kierowca;
}samochod;

// Typ elementów listy
//--------------------
typedef struct node
{
	struct node* next, * prev;
	samochod* data;
} node;

// Zmienna obsługująca listę
//--------------------------
typedef struct list
{
	node* head, * tail;
} list;

list* init_list(); //0,5p
int push_front(list* L, const char* model); //1,0p
void print_list(list* L); //0,5p

int push_priority(list* L, const char* model); //2,0p
void tab2list(const char* T[][2], list* L1, list* L2, int ilosc); //1,0p

node* search(list* L, const char* model); //1,0p
osoba* za_kolko(node* s, const char* imie, const char* nazwisko); //1,0p

int main(void)
{
	list* renault, * toyota;
	int ok1, ok2;
	node* n;
	osoba* o;

	const char* samochody[][2] = { {"renault", "Megane"},{"renault", "Talisman"},{"toyota", "Yaris"},
							 {"renault", "Scenic"},{"toyota", "Rav 4"},{"renault", "Laguna 1"},
							 {"renault", "Clio 2"},{"toyota", "Corolla"},{"toyota", "Avensis"},
							 {"toyota", "Corolla"} };


	//Etap 1
	printf("*******ETAP 1********\n");
	renault = init_list();
	if (!renault->head && !renault->tail) printf("Lista zainicjowana");
	else printf("Inicjacja sie nie powiodla");

	ok1 = push_front(renault, "Laguna 1");
	if (ok1) printf("\nPierwszy samochod: %s", renault->head->data->model);
	else printf("Dodanie samochodu się nie powiodlo");

	ok1 = push_front(renault, "Clio 1");
	printf("\n\nLista samochodow:\n");
	if (ok1) print_list(renault);
	else printf("Coś nie działa przy dodawaniu kolejnego samochopdu");
	printf("\nA teraz od konca listy:\n");
	printf("%s\n", renault->tail->data->model);
	printf("%s\n", renault->tail->prev->data->model);

	//Etap 2
	printf("\n*******ETAP 2********\n");
	toyota = init_list();
	ok1 = push_priority(toyota, "Corolla");
	printf("\nAlfabetyczna lista samochodow Toyoty:\n");
	if (ok1) print_list(toyota);
	ok1 = push_priority(toyota, "Avensis");
	printf("\nAlfabetyczna lista samochodow Toyoty:\n");
	if (ok1) print_list(toyota);
	ok1 = push_priority(toyota, "Rav 4");
	printf("\nAlfabetyczna lista samochodow Toyoty:\n");
	if (ok1) print_list(toyota);
	ok1 = push_priority(toyota, "Corolla");
	printf("\nAlfabetyczna lista samochodow Toyoty:\n");
	if (ok1) print_list(toyota);
	printf("\nA teraz od konca dwa ostatnie:\n");
	printf("%s\n", toyota->tail->data->model);
	printf("%s\n", toyota->tail->prev->data->model);
	printf("\nDodanie wszystkich samochodow z tablicy:\n");
	tab2list(samochody, renault, toyota, sizeof(samochody) / sizeof(char*) / 2);
	printf("\nRenault:\n");
	print_list(renault);
	printf("\nToyota:\n");
	print_list(toyota);

	//Etap 3
	printf("\n*******ETAP 3********");
	printf("\nWyszukiwanie samochodow:\n");
	n = search(toyota, "Corolla");
	if (n) printf("\nZnaleziony samochod: %s", n->data->model);
	else printf("Brak samochodu Corolla na liscie\n");
	n = search(toyota, "Corola");
	if (n) printf("\nZnaleziony samochod: %s", n->data->model);
	else printf("\nBrak samochodu Corolla na liscie\n");
	printf("\nPierwszy kierowca:\n");
	n = search(toyota, "Rav 4");
	o = za_kolko(n, "Marek", "Konieczny");
	if (o) print_list(toyota);
	printf("\nDrugi kierowca:\n");
	n = search(toyota, "Yaris");
	o = za_kolko(n, "Marzena", "Witek");
	if (o) print_list(toyota);
	n = search(toyota, "Yaris");
	o = za_kolko(n, "Gabriela", "Kotek");
	if (o) print_list(toyota);
	else printf("\nKierowca juz jest\n");

	printf("\n");
	system("pause");
	return 0;
}
list* init_list()
{
	list* new_list = (list*)malloc(sizeof(list));
	new_list->head = NULL;
	new_list->tail = NULL;
	return new_list;
}
int push_front(list* L, const char* model)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->data = (samochod*)malloc(sizeof(samochod));
	new_node->data->kierowca = NULL;
	new_node->prev = NULL;
	new_node->data->model = model;
	if (L->head == NULL)
	{
		L->head = new_node;
		L->tail = new_node;
		new_node->next = NULL;
		return 1;
	}
	else {
		L->head->prev = new_node;
		new_node->next = L->head;
		L->head = new_node;
		return 1;
	}
}
void print_list(list* L)
{
	node* tmp = L->head;
	while (tmp != NULL)
	{
		if (tmp->data->kierowca == NULL)
		{
			printf("%s \n", tmp->data->model);
		}
		else
		{
			printf("%s, za kolkiem: %s %s \n", tmp->data->model, tmp->data->kierowca->imie, tmp->data->kierowca->nazwisko);
		}
		tmp = tmp->next;
	}
}
int push_priority(list* L, const char* model)
{
	if (L->head == NULL)
	{
		push_front(L, model);
		return 1;
	}
	node* tmp = L->head;
	while (tmp != NULL)
	{
		if (strcmp(tmp->data->model, model) >= 0)
		{
			if (tmp == L->head)
			{
				push_front(L, model);
				return 1;
			}
			else
			{
				node* new_node = (node*)malloc(sizeof(node));
				new_node->data = (samochod*)malloc(sizeof(samochod));
				new_node->data->kierowca = NULL;
				new_node->data->model = model;
				tmp->prev->next = new_node;
				new_node->prev = tmp->prev;
				tmp->prev = new_node; 
				new_node->next = tmp;
				return 1;
			}
		}
		tmp = tmp->next;
	}
	node* new_node = (node*)malloc(sizeof(node));
	new_node->data = (samochod*)malloc(sizeof(samochod));
	new_node->data->kierowca = NULL;
	new_node->data->model = model;
	new_node->prev = L->tail;
	L->tail->next = new_node;
	new_node->next = NULL;
	L->tail = new_node;
	return 1;
}
void tab2list(const char* T[][2], list* L1, list* L2, int ilosc)
{
	for (int i = 0; i < ilosc; i++)
	{
		if (strcmp(T[i][0], "renault") == 0)
		{
			push_priority(L1, T[i][1]);
		}
		if (strcmp(T[i][0], "toyota") == 0)
		{
			push_priority(L2, T[i][1]);
		}
	}
}
node* search(list* L, const char* model)
{
	node* tmp = L->head;
	while (tmp != NULL)
	{
		if (strcmp(tmp->data->model, model) == 0) return tmp;
		tmp = tmp->next;
	}
	return NULL;
}
osoba* za_kolko(node* s, const char* imie, const char* nazwisko)
{
	if (s->data->kierowca != NULL) return NULL;
	s->data->kierowca = (osoba*)malloc(sizeof(osoba));
	strcpy(s->data->kierowca->imie, imie);
	strcpy(s->data->kierowca->nazwisko, nazwisko);
	return s->data->kierowca;

}