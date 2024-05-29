#include <stdio.h>
#include <stdlib.h>		
#include <time.h>		

#define N 20	

void print(int[], int);
void random(int[], int, int, int);

void move(int[], int, int, int);

int min_nieobecna(int[], int, int, int);

int lider(int[], int);

int pasmo(int[], int, int*);

int sklej(int [], int);


//-----------------------------------------------------------
int main()
{

	int a[N], b[N], c[N];
	int p1 = 1, p2 = 10;

	srand(42);	//najmniejsza_nieobecna=8 / lider=2 / pasmo:start=7 dl=4
	//srand(102);   //najmniejsza_nieobecna=10 / lider=0 / pasmo:start=0 dl=3
	//srand(118);	//najmniejsza_nieobecna=5 / lider=3 / pasmo:start=0 dl=3
	//srand((unsigned)time(0));


	printf("\n-----   ETAP 1 (1pkt)   --------------------------\n");
	random(a, N, p1, p2);	//wartości całkowite z [1,10]

	printf("\nWYLOSOWANE\n");
	print(a, N);

	printf("\n-----   ETAP 2 (1pkt)   --------------------------\n");
	printf("\nMOVE i=3 k=5\n");
	move(a, N, 3, 5);
	print(a, N);
	
	printf("\nMOVE i=5 k=3\n");
	move(a, N, 5, 3);
	print(a, N);

	printf("\n-----   ETAP 3 (1pkt)   --------------------------\n");

	printf("\nMinimalna nieobecna to nn=%d\n", min_nieobecna(a, N, p1, p2));

	printf("\n-----   ETAP 4 (1pkt)   --------------------------\n");
	printf("\nWYLOSOWANE do lidera\n");
	random(b, N, 1, 3);	//wartości całkowite z [1,3]
	print(b, N);

	printf("\nLIDER to L=%d\n", lider(b, N));

	printf("\n-----   ETAP 5 (1,5 pkt)   ------------------------\n");
	{
		int d, start;
		printf("\nPASMO\n");
		print(a, N);
		d = pasmo(a, N, &start);

		printf("\nPierwsze maksymalne pasmo start=%d dl=%d:\n",start,d);
		print(a + start, d);
	}

	printf("\n-----   ETAP 6 (1,5 pkt)   ------------------------\n");
	{
		int d;
		printf("\nSKLEJANIE\n");
		random(c, N, p1, p2);
		print(c, N);
		printf("\n");
		d=sklej(c, N);
		print(c, d);
	}

	printf("\n-----   KONIEC   ----------------------------------\n");
	return 0;
}

void random(int tab[], int n, int p1, int p2)
{
	int i; 
	for (i = 0; i < n; i++)
		tab[i] = p1 + rand() % (p2 - p1 + 1);
}

void print(int tab[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", tab[i]);
}
void move(int tab[], int n, int i, int k)
{
	int tmp;
	if (i < k) {
		for (; i < k; i++)
		{
			tmp = tab[i + 1];
			tab[i + 1] = tab[i];
			tab[i] = tmp;
		}
	}
	else {
		for (; k < i; k++)
		{
			tmp = tab[k + 1];
			tab[k + 1] = tab[k];
			tab[k] = tmp;
		}
	}
}
int min_nieobecna(int tab[], int n, int p1, int p2)
{
	int i, j;
	for (i = p1; i <= p2; i++)
		for (j = 0; j < n; j++)
		{
			if (i == tab[j]) break;
			else if (j == n - 1) return i;
		}
	return 0;
}
int lider(int tab[], int n)
{
	int i, j, licznik;
	for (i = 0; i < n-1; i++)
	{
		licznik = 1;
		for (j = i + 1; j < n; j++)
		{
			if (tab[i] == tab[j]) licznik++;
			if (licznik > n / 2) return tab[i];
		}
	}
	return 0;
}
int pasmo(int tab[], int n, int* start)
{
	int i, a = 1, starter, k = 0;
	starter = 0;
	for (i = 0; i < n-1; i++)
	{
		if (tab[i] <= tab[i + 1]) a++;
		else {
			if (a > k)
			{
				k = a;
				*start = starter;
			}
			starter = i + 1;
			a = 1;
		}
	}
	return k;
}
int sklej(int tab[], int n)
{
	int i, j, k = n, a =1;
	for (i = 1; i < n-1; i++)
	{
		if (tab[i] == tab[i -1]) a++;
		else if (a != 1)
		{
			k = n - a;
			tab[i - a] *= a;
			for (j = i - a+1; j < n; j++)
				tab[j] = tab[j+a-1];
			a = 1;
		}
		
	}
	return k;
}