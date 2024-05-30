#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FL 18 //liczba elementow w tworzonej liscie, potem ulegnie zmianie!

struct node
{
    int num;                    //dane
    struct node* nextptr;       //nastepny wezel
} *first_list = NULL, * second_list = NULL;
typedef struct node sn;

void nodeInsertatEnd(node **first_list, int los);
void displayList(node *first_list);
void cleanList(node **first_list);
void sortRange(node** first_list, int en);
void sweepList(node **first_list);

int main()
{
    int i, los, en;
    srand((unsigned)time(NULL));
    //ETAP 1
    for (i = 0; i < FL; i++)
    {
        los = rand() % 10; //przykladowy zakres losowanych wartosci
        nodeInsertatEnd(&first_list, los);
    }
    printf("Singly linked list:\n");
    printf("-----------------------------------------------\n");
    displayList(first_list);
    cleanList(&first_list);
    displayList(first_list);

    //// ETAP 2
    printf("Singly linked list (new one):\n");
    printf("-----------------------------------------------\n");
    for (i = 0; i < FL; i++)
    {
        los = rand() % 9;//przykladowy zakres losowanych wartosci do listy
        nodeInsertatEnd(&first_list, los);
    }
    displayList(first_list);
    en = 8;//FL-1//5//0 testowane beda rozne poprawne zakresy
    printf("Singly linked list after sorting on the interval [0,%d]: \n", en);
    sortRange(&first_list, en);
    sortRange(&first_list, en); //celowe powtorzenie
    displayList(first_list);

    //// ETAP 3
    printf("Singly linked list without duplicates: \n");
    printf("-----------------------------------------------\n");
    sweepList(&first_list);
    sweepList(&first_list); //celowe powtorzenie
    displayList(first_list);
    ////sprzatanie
    cleanList(&first_list);
    displayList(first_list);
    cleanList(&second_list);
    displayList(second_list);
    return 0;
}

void nodeInsertatEnd(node** first_list, int los)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->num = los;
    new_node->nextptr = NULL;
    node* tmp = *first_list;
    if (*first_list == NULL)
    {
        *first_list = new_node;
        return;
    }
    while (tmp->nextptr != NULL)
    {
        tmp = tmp->nextptr;
    }
    tmp->nextptr = new_node;
}
void displayList(node* first_list)
{
    node* tmp = first_list;
    while (tmp != NULL)
    {
        printf(" %d --->  ", tmp->num);
        tmp = tmp->nextptr;
    }
    printf("\n");
}
void cleanList(node** first_list)
{
    node* tmp;
    while (*first_list != NULL)
    {
        tmp = *first_list;
        *first_list = (*first_list)->nextptr;
        free(tmp);
    }
}
void sortRange(node** first_list, int en)
{
    node* tmp = *first_list;
    for (int i = 0; i < en; i++)
    {
        node* p = *first_list;
        for (int j = 0; j < en -1; j++)
        {
            if (p->num > p->nextptr->num)
            {
                if (p == *first_list)
                {
                    *first_list = p->nextptr;
                    p->nextptr = p->nextptr->nextptr;
                    (*first_list)->nextptr = p;
                    continue;
                }
                else
                {
                    node* t = *first_list;
                    while (t->nextptr != p)
                    {
                        t = t->nextptr;
                    }
                    t->nextptr = p->nextptr;
                    p->nextptr = p->nextptr->nextptr;
                    t->nextptr->nextptr = p;
                    continue;
                }
            }
            p = p->nextptr;
        }
    }
}
void sweepList(node** first_list)
{
    node* tmp = *first_list;
    while (tmp != NULL)
    {
        node* p = tmp;
        while (p->nextptr != NULL)
        {
            if (p->nextptr->num == tmp->num)
            {
                p->nextptr = p->nextptr->nextptr;
            }
            p = p->nextptr;
            if (p == NULL) break;
        }
        tmp = tmp->nextptr;
    }
}