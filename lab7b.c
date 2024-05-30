#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
* element listy
*/
struct ll_node
{
	char* str;
	struct ll_node* prev;
	struct ll_node* next;
};

/*
* zarządca listy
*/
struct ll_node_manager
{
	struct ll_node* head;
	struct ll_node* tail;
};

/*
* prototypy funkcji
*/
struct ll_node_manager* init(void);//E1
void print_head(struct ll_node_manager* ptr);//E1
void print_tail(struct ll_node_manager* ptr);//E1
void insert_head(struct ll_node_manager* ptr, char* str);//E1
void insert_tail(struct ll_node_manager* ptr, char* str);//E1
void check_if_contains(struct ll_node_manager* ptr, char* str);//E2
void sort(struct ll_node_manager* ptr);//E2
void remove_node(struct ll_node_manager* ptr, char* str);//E3
void clear_list(struct ll_node_manager* ptr);//E3


int main(int argc, char** argv) {
	char* szukana1 = "O Wawelskim Smoku";
	char* szukana2 = "Na nic placze, na nic krzyki, koniec przygod";
	char* szukana3 = "Awantura o Basie";
	char* szukana4 = "Wyprawa pod psem";

	//Etap 1: 2 pkt
	struct ll_node_manager* biblioteka = init();
	print_head(biblioteka);
	printf("\n");
	insert_tail(biblioteka, "Szatan z siódmej klasy");
	insert_tail(biblioteka, "Panna z mokrą głową");
	insert_tail(biblioteka, "Awantury i wybryki małej małpki Fiki-Miki");
	insert_tail(biblioteka, "Przygody Koziołka Matołka");
	//dodaj na koniec poniższe tytuły (dodaj wywołania funkcji)
	//Szatan z siódmej klasy
	//Panna z mokrą głową
	//Awantury i wybryki małej małpki Fiki-Miki
	//Przygody Koziołka Matołka

	insert_head(biblioteka, "Awantura o Basię");
	insert_head(biblioteka, "Szaleństwa panny Ewy");
	insert_head(biblioteka, "O Wawelskim Smoku");
	insert_head(biblioteka, "Wanda leży w naszej ziemi");
	insert_head(biblioteka, "O dwóch takich co ukradli księżyc");
	insert_head(biblioteka, "Wyprawa pod psem");
	insert_head(biblioteka, "Przyjaciel wesołego diabła");
	//dodaj na początek poniższe tytuły (dodaj wywołania funkcji)
	//Awantura o Basię
	//Szaleństwa panny Ewy
	//O Wawelskim Smoku
	//Wanda leży w naszej ziemi
	//O dwóch takich co ukradli księżyc
	//Wyprawa pod psem
	//Przyjaciel wesołego diabła

	//wypisz listę
	print_head(biblioteka);
	printf("\n\n");
	print_tail(biblioteka);



	//Etap 2: 3 pkt
	printf("Etap 2\n");
	//poszukiwanie książek (1 pkt)
	check_if_contains(biblioteka, szukana1);
	check_if_contains(biblioteka, szukana2);

	////sortowanie książek (2 pkt)
	//ll_sort(biblioteka);
	sort(biblioteka);
	////wypisz listę
	printf("\n\nSortowana ");
	print_head(biblioteka);
	printf("\n\nSortowana ");
	print_tail(biblioteka);



	////Etap 3: 2 pkt
	////usuń wybraną książkę (1 pkt)
	printf("\n\n");
	printf("Etap 3\n");
	remove_node(biblioteka, szukana1);
	remove_node(biblioteka, szukana2);
	remove_node(biblioteka, szukana3);
	remove_node(biblioteka, szukana4);
	////wypisz listę
	printf("\n\nUsunięta ");
	print_head(biblioteka);
	printf("\n\nUsunięta ");
	print_tail(biblioteka);
	////likwidacja biblioteki
	clear_list(biblioteka);
	////wypisz listę
	printf("\n\nUsuwanie biblioteki\n");
	print_tail(biblioteka);
	system("PAUSE");
	//return 0;
}
struct ll_node_manager* init(void)
{
	struct ll_node_manager* new_list = (struct ll_node_manager*)malloc(sizeof(struct ll_node_manager));
	new_list->head = NULL;
	new_list->tail = NULL;
	return new_list;
}
void insert_head(struct ll_node_manager* ptr, char* str)
{
	struct ll_node* new_el = (struct ll_node*)malloc(sizeof(struct ll_node));
	new_el->str = str;
	new_el->prev = NULL;
	if (ptr->head == NULL)
	{
		new_el->next = NULL;
		ptr->head = new_el;
		ptr->tail = new_el;
		return;
	}
	new_el->next = ptr->head;
	ptr->head->prev = new_el;
	ptr->head = new_el;
}
void insert_tail(struct ll_node_manager* ptr, char* str)
{
	struct ll_node* new_el = (struct ll_node*)malloc(sizeof(struct ll_node));
	new_el->str = str;
	new_el->next = NULL;
	if (ptr->head == NULL)
	{
		new_el->prev = NULL;
		ptr->head = new_el;
		ptr->tail = new_el;
		return;
	}
	new_el->prev = ptr->tail;
	ptr->tail->next = new_el;
	ptr->tail = new_el;
}
void print_head(struct ll_node_manager* ptr)
{
	struct ll_node* tmp = ptr->head;
	if (ptr->head == NULL)
	{
		printf("Biblioteka pusta\n");
		return;
	}
	printf("Lista dostepnych ksiazek(head):\n");
	while (tmp != NULL)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}
void print_tail(struct ll_node_manager* ptr)
{
	printf("Lista dostepnych ksiazek(tail):\n");
	if (ptr->head == NULL)
	{
		printf("Biblioteka pusta\n");
		return;
	}
	struct ll_node* tmp = ptr->tail;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->prev;
	}
}
void check_if_contains(struct ll_node_manager* ptr, char* str)
{
	struct ll_node* tmp = ptr->head;
	while (tmp != NULL)
	{
		if (strcmp(tmp->str, str) == 0)
		{
			printf("Książka dostępna w bibliotece!\n");
			return;
		}
		tmp = tmp->next;
	}
	printf("Niestety nie mamy takiej pozycji w naszym zbiorze.\n");
}
void sort(struct ll_node_manager* ptr)
{
	struct ll_node* ptr1;
	struct ll_node* _ptr = NULL;
	int swapped;
	do
	{
		swapped = 0;
		ptr1 = ptr->head;
		while (ptr1->next != _ptr)
		{
			if (strcmp(ptr1->str, ptr1->next->str) > 0)
			{
				char* tmp = ptr1->str;
				ptr1->str = ptr1->next->str;
				ptr1->next->str = tmp;
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		_ptr = ptr1;
	} while (swapped);
}
void remove_node(struct ll_node_manager* ptr, char* str)
{
	struct ll_node* tmp = ptr->head;
	while (tmp != NULL)
	{
		if (strcmp(tmp->str, str) == 0)
		{
			printf("Usawam %s\n", tmp->str);
			if (tmp == ptr->head)
			{
				ptr->head->next->prev = NULL;
				ptr->head = ptr->head->next;
				free(tmp);
				return;
			}
			if (tmp == ptr->tail)
			{
				ptr->tail->prev->next = NULL;
				ptr->tail = ptr->tail->prev;
				free(tmp);
				return;
			}
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			free(tmp);
			return;
		}
		tmp = tmp->next;
	}
}
void clear_list(struct ll_node_manager* ptr)
{
	struct ll_node* tmp;
	while (ptr->head != NULL)
	{
		tmp = ptr->head;
		ptr->head = ptr->head->next;
		free(tmp);
	}
	ptr->tail = NULL;
	ptr->head = NULL;
}