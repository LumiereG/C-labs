#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30

//-------------------------------------------------
typedef struct driver {
	char firstName[N];
	char secondName[N];
}driver;

//-------------------------------------------------
typedef struct car {
	char model[N];
	driver* who;
}car;

//-------------------------------------------------
typedef struct node {
	struct node* next;
	car* c;
} node;

//-------------------------------------------------
typedef struct list {
	node* head;
} list;


//ETAP 1 (2p)
void init_list(list** L); //0.5p
int push_back(list* L, char* model); //1p
void print_list(list* L); //0.5p

//ETAP 2 (2.5p)
int push_priority(list* L, char* model); //1.5p
void tab2list(char* T[][2], list* renault, list* toyota, int liczba); //1p
//
////ETAP 3 (1.5p)
node* search(list* L, char* model); //0.5p
driver* driver_to_car(node* s, char* firstName, char* secondName); //1p
//
////ETAP 4 (1p)
void robbing_2(list* L);

//-----------------------------------------------------------
int main(void)
{
	list* renault = NULL, * toyota = NULL;
	int ok;
	node* n;
	driver* o;

	char* cars[][2] = { {"renault", "Megane"},{"renault", "Talisman"},{"toyota", "Yaris"},
						{"renault", "Scenic"},{"peugeot","206"}, {"toyota", "Rav 4"},{"renault", "Laguna 1"},
						{"renault", "Clio 2"},{"toyota", "Corolla"},{"toyota", "Avensis"},{"toyota", "Corolla"} };


	//Etap 1
	printf("\n*******ETAP 1********\n");
	init_list(&renault);
	if (!renault) { printf("\nNiepowodzenie init_list...\n");  return 0; }

	ok = push_back(renault, "Clio 1");
	if (!ok)  printf("\nNIE dodano ...\n");

	ok = push_back(renault, "Laguna 1");
	if (!ok)  printf("\nNIE dodano ...\n");

	printf("\n\nLista RENAULT:\n");
	print_list(renault);


	//Etap 2
	printf("\n*******ETAP 2********\n");

	char* model1[] = { "Corolla" ,"Avensis" ,"Rav 4" ,"Corolla" };

	init_list(&toyota);
	if (!toyota) { printf("\nNiepowodzenie init_list...\n");  return 0; }

	for (int i = 0; i < 4; i++)
	{
		ok = push_priority(toyota, model1[i]);
		if (!ok)  printf("\nNIE dodano ...\n");
	}

	printf("\nAlfabetyczna lista TOYOTA:\n");
	print_list(toyota);


	printf("\nDodanie wszystkich samochodow z tablicy:\n");
	tab2list(cars, renault, toyota, sizeof(cars) / sizeof(char*) / 2);
	printf("\nsamochody RENAULT:\n");
	print_list(renault);
	printf("\nsamochody TOYOTA:\n");
	print_list(toyota);

	////Etap 3
	printf("\n*******ETAP 3********");
	printf("\nWyszukiwanie modelu bez kierowcy:\n");
	n = search(toyota, "Corolla");
	if (n) printf("\nZnaleziony car: %s", n->c->model);
	else printf("Brak modelu Corolla na liscie\n");

	n = search(toyota, "Corola");
	if (n) printf("\nZnaleziony car: %s", n->c->model);
	else printf("\nBrak modelu Corola na liscie\n");

	char* model2[] = { "Avensis","Corolla","Yaris" ,"Yaris" };
	char* driver[][2] = { {"Marek", "Konieczny"},{"Mateusz", "Niekonieczny"},{"Marzena", "Witek"},{"Gabrinodea", "Kotek"} };

	for (int i = 0; i < 4; i++)
	{
		printf("\n%d driver:\n", i + 1);
		n = search(toyota, model2[i]);
		o = driver_to_car(n, driver[i][0], driver[i][1]);
		if (o) print_list(toyota);
		else printf("driver juz jest; brak wolnego modelu %s\n", model2[i]);
	}

	////Etap 4
	printf("\n*******ETAP 4********");
	printf("\nKradziez co 2-go samochodu (start od pierwszego- head):\n");
	robbing_2(renault);
	robbing_2(toyota);

	printf("\nsamochody RENAULT:\n");
	print_list(renault);
	printf("\nsamochody TOYOTA:\n");
	print_list(toyota);

	printf("\nWIELOKROTNA kradziez co 2-go samochodu (start od pierwszego- head):\n");
	while (renault->head) 	robbing_2(renault);
	while (toyota->head) 	robbing_2(toyota);

	printf("\nsamochody RENAULT:\n");
	print_list(renault);
	printf("\nsamochody TOYOTA:\n");
	print_list(toyota);

	printf("\n");
	system("pause");
	return 0;
}
void init_list(list** L)
{
	* L = (list*)malloc(sizeof(list));
	(*L)->head = NULL;
}
int push_back(list* L, char* model)
{
	node* new_el = (node*)malloc(sizeof(node));
	car* c1 = (car*)malloc(sizeof(car));
	new_el->next = NULL;
	new_el->c = c1;
	strncpy(new_el->c->model, model, strlen(model) + 1);
	new_el->c->who = NULL;
	if (L->head == NULL)
	{
		L->head = new_el;
	}
	else
	{
		node* tmp = L->head;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new_el;
	}
}
void print_list(list* L)
{
	node* tmp = L->head;
	while (tmp != NULL)
	{
		if (tmp->c->who == NULL) printf("%s \n", tmp->c->model);
		else printf("%s, kierownica: %s %s \n", tmp->c->model, tmp->c->who->firstName, tmp->c->who->secondName);
		tmp = tmp->next;
	}

}
int push_priority(list* L, char* model)
{
	node* new_el = (node*)malloc(sizeof(node));
	car* c1 = (car*)malloc(sizeof(car));
	new_el->c = c1;
	strncpy(new_el->c->model, model, strlen(model) + 1);
	new_el->c->who = NULL;
	node* tmp = L->head;
	if (L->head == NULL)
	{
		L->head = new_el;
		new_el->next = NULL;
		return 1;
	}
	if (strcmp(new_el->c->model, L->head->c->model) < 0)
	{
		new_el->next = tmp;
		L->head = new_el;
		return 1;
	}
	while (tmp->next != NULL)
	{
		if (strcmp(new_el->c->model, tmp->next->c->model) < 0)
		{
			new_el->next = tmp->next;
			tmp->next = new_el;
			return 1;
		}
		tmp = tmp->next;
	}
	tmp->next = new_el;
	new_el->next = NULL;
	
}
void tab2list(char* T[][2], list* renault, list* toyota, int liczba)
{
	for (int i = 0; i < liczba; i++)
	{
		if (strcmp(T[i][0], "renault") == 0)
		{
			push_priority(renault, T[i][1]);
		}
		if (strcmp(T[i][0], "toyota") == 0)
		{
			push_priority(toyota, T[i][1]);
		}
	}
}
node* search(list* L, char* model)
{
	node* tmp = L->head;
	while (tmp != NULL)
	{
		if (strcmp(tmp->c->model, model) == 0) return tmp;
		tmp = tmp->next;
	}
	return NULL;
}
driver* driver_to_car(node* s, char* firstName, char* secondName)
{
	if (s->c->who != NULL) return NULL;
	driver* kier = (driver*)malloc(sizeof(driver));
	if (kier == NULL) return NULL;
	strncpy(kier->firstName, firstName, strlen(firstName) + 1);
	strncpy(kier->secondName, secondName, strlen(secondName) + 1);
	s->c->who = kier;
}
void robbing_2(list* L)
{
	int i = 0;
	node* tmp = L->head;
	while (tmp != NULL)
	{
		if (i % 2 == 0)
		{
			if (tmp == L->head)
			{
				L->head = tmp->next;
				i++;
				if(tmp->c->who != NULL) free(tmp->c->who);
				free(tmp->c);
				free(tmp);
				tmp = L->head;
				continue;
			}
			node* t = L->head;
			while (t->next != tmp)
			{
				t = t->next;
			}
			t->next = tmp->next;
			if (tmp->c->who != NULL) free(tmp->c->who);
			free(tmp->c);
			free(tmp);
			tmp = t;
			if (tmp == NULL) return;
		}
		i++;
		tmp = tmp->next;
	}
}
