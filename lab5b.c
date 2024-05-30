#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print(char* input, int count);
char* remove_spec(char src[]);//E1
int get_word_count(char* str);//E2
char** words_tab(char* input, int hmny);//E2
void sort_words_tab(char* words[], int count);//E2
int check_anagram(char* str1, char* str2);//E3
//void print_highest_frequency(char* str);//E3

int main(void)
{
    char* ogden_nash = "You get a wife, you get a house, eventually you get a mouse. You get some words regarding mice, you get a kitty in a trice. By two am or thereabouts, the mouse is in, the cat is out. It dawns upon you, in your cot, the mouse is silent, the cat is not. Instead of kitty, says your spouse, you should have got another mouse.";
    char* ogden_nash_clean = NULL;
    char* word1 = "vacation time";// do testowania etapu 3
    char* word2 = "i am not active";// do testowania etapu 3
    // char *word3 = "active time"; // do testowania etapu 3
    int counter, i;
    char** table_words;
    printf("Wejscie do programu: \n%s\n", ogden_nash);

    //Etap 1
    ogden_nash_clean = remove_spec(ogden_nash);
    printf("\n%s", ogden_nash_clean);
    printf("\n");

    //Etap 2
    printf("Po posortowaniu:\n");
    counter = get_word_count(ogden_nash_clean);
    printf("%d \n", counter);
    table_words = words_tab(ogden_nash_clean, counter);
    sort_words_tab(table_words, counter);
    for (i = 0; i < counter; i++)
        printf("%s ", table_words[i]);
    printf("\n");

    //Etap 3
    printf("\nCzy anagram?\n");
    if (check_anagram(word1, word2)) printf("Tak, slowa tworza anagram.\n");
    else printf("Nie.\n");
    printf("\n");
    //print_highest_frequency(ogden_nash_clean);
    //system("PAUSE");
    //return 0;
}
char* remove_spec(char src[])
{
    int ilosc = 0;
    for (int i = 0; i < strlen(src); i++)
    {
        if (src[i] == 44 || src[i] == 46) continue;
        ilosc += 1;
    }
    char* wynik = (char*)malloc(ilosc * sizeof(char));
    int k = 0;
    for (int i = 0; i < strlen(src); i++)
    {
        if (src[i] == 44 || src[i] == 46) continue;
        if (src[i] >= 65 && src[i] <= 90)
        {
            wynik[k] = src[i] + 32;
            k++;
        }
        else {
            wynik[k] = src[i];
            k++;
        }
    }
    wynik[ilosc] = '\0';
    return wynik;
}
int get_word_count(char* str)
{
    int k = 1;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ') k++;
    }
    return k;
}
char** words_tab(char* input, int hmny)
{
    char** nowa = (char**)malloc(hmny * sizeof(char*));
    char* seps = (char*)malloc(1);
    seps[0] = 32;
    char* token;
    int i = 0;
    token = strtok(input, seps);
    while (token != NULL)
    {
        nowa[i] = (char*)malloc(strlen(token) + 1);
        nowa[i] = strcpy(nowa[i], token);
        //nowa[i][strlen(token)] = '\0';
        token = strtok(NULL, seps);
        i++;
    }
    return nowa;
}
void print(char** input, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s \n", input[i]);
    }
}
void sort_words_tab(char* words[], int count)
{
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(words[j], words[j + 1]) < 0)
            {
                char tmp[100];
                strcpy(tmp, words[j]);
                strcpy(words[j],words[j + 1]);
                strcpy(words[j + 1],tmp);
            }
        }
}
int check_anagram(char* str1, char* str2)
{
    char* tab1 = malloc(strlen(str1));
    char* tab2 = malloc(strlen(str2));
    strcpy(tab1, str1);
    strcpy(tab2, str2);
    for (int i = 0; i < strlen(str1) - 1; i++)
        for (int j = 0; j < strlen(str1) - i - 1; j++)
        {
            if (tab1[j] < tab1[j + 1])
            {
                char tmp;
                tmp = tab1[j];
                tab1[j] = tab1[j + 1];
                tab1[j + 1] = tmp;
            }
        }
    for (int i = 0; i < strlen(str2) - 1; i++)
        for (int j = 0; j < strlen(str2) - i - 1; j++)
        {
            if (tab2[j] < tab2[j + 1])
            {
                char tmp;
                tmp = tab2[j];
                tab2[j] = tab2[j + 1];
                tab2[j + 1] = tmp;
            }
        }
    int n = strlen(str1) < strlen(str2) ? strlen(str1) : strlen(str2);
    int i = strlen(str1) - 1;
    int j = strlen(str2) - 1;
    while (tab1[i] == ' ')
    {
        tab1[i] = '\0';
        i--;
    }
    while (tab2[j] == ' ')
    {
        tab2[j] = '\0';
        j--;
    }
    return strcmp(tab1, tab2) == 0;
}
/*void print_highest_frequency(char* str)
{
    int count[256] = { 0 }; 
    int maxCount = 0;     
    char maxChar = '\0'; 

    for (int i = 0; i < strlen(str); i++) 
    {
        char ch = str[i];
        if (ch == ' ') continue;
        count[(unsigned char)ch]++;
        if (count[(unsigned char)ch] > maxCount) 
        {
            maxCount = count[(unsigned char)ch];
            maxChar = ch;
        }
    }
    printf("Znak '%c' zostal powtorzony %d razy.\n", maxChar, maxCount);
}*/
