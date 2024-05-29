#include <stdio.h>
#include <stdlib.h>
#define BINS 10
#define YEARS 20
#define MONTHS 12
#define TEMPMAX 29.05
#define TEMPMIN 17.74

enum month { Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };

void make_histogram(float tab[YEARS][MONTHS], int his[BINS]);
void show_histogram_raw(int his[BINS]);
void show_histogram(int his[BINS]);

void make_histogram_col(float tab[YEARS][MONTHS], int his[MONTHS][BINS]);
void show_histogram_raw_col(int his[MONTHS][BINS]);
void show_histogram_month(int his[MONTHS][BINS], enum month choose_month);

float get_monthly_average(float tab[YEARS][MONTHS], enum month choosem);
void print_monthly_averages(float tab[YEARS][MONTHS], enum month choosem[]);


int main(void)
{
    int hist[BINS] = { 0 };
    int hiscol[MONTHS][BINS] = { 0 };
    enum month keyT_vals[] = { Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };
    float tem_Melb[YEARS][MONTHS] = {
        {0.89,    0.89,    0.77,    0.61,    0.34,    0.13,    0.07,    0.18,    0.36,    0.54,    0.61,    0.76},
        {0.92,    0.92,    0.83,    0.63,    0.38,    0.15,    0.10,    0.19,    0.42,    0.56,    0.67,    0.81},
        {0.92,    0.93,    0.84,    0.66,    0.41,    0.17,    0.10,    0.20,    0.44,    0.57,    0.68,    0.84},
        {0.93,    0.95,    0.82,    0.67,    0.40,    0.17,    0.10,    0.26,    0.42,    0.61,    0.68,    0.85},
        {0.87,    0.86,    0.74,    0.55,    0.32,    0.08,    0.00,    0.17,    0.42,    0.57,    0.66,    0.78},
        {0.93,    0.90,    0.78,    0.57,    0.34,    0.10,    0.03,    0.20,    0.40,    0.57,    0.63,    0.81},
        {0.89,    0.92,    0.76,    0.54 ,   0.32,    0.09,    0.03,    0.19,    0.40,    0.63,    0.64,    0.83},
        {0.95,    0.90,    0.77,    0.61,    0.34,    0.13,    0.04,    0.18,    0.43,    0.61,    0.67,    0.84},
        {0.94,    0.85,    0.74,    0.62,    0.35,    0.12,    0.05,    0.22,    0.47,    0.61,    0.69,    0.81},
        {0.97,    0.96,    0.85,    0.68,    0.39,    0.18,    0.13,    0.23,    0.51,    0.63,    0.73,    0.83},
        {1.00,    0.94,    0.82,    0.63,    0.36,    0.17,    0.11,    0.24,    0.44,    0.62,    0.74,    0.89},
        {1.00,    0.94,    0.82,    0.67,    0.38,    0.18,    0.13,    0.24,    0.44,    0.60,    0.73,    0.87},
        {0.87,    0.89,    0.73,    0.64,    0.31,    0.14,    0.05,    0.17,    0.42,    0.57,    0.62,    0.74},
        {0.92,    0.88,    0.76,    0.62,    0.33,    0.13,    0.03,    0.19,    0.39,    0.59,    0.59,    0.80},
        {0.93,    0.87,    0.75,    0.59,    0.34,    0.11,    0.04,    0.20,    0.39,    0.60,    0.62,    0.82},
        {0.95,    0.95,    0.77,    0.64,    0.34,    0.13,    0.04,    0.16,    0.40,    0.64,    0.64,    0.83},
        {0.90,    0.91,    0.81,    0.62,    0.36,    0.14,    0.05,    0.16,    0.39,    0.56,    0.63,    0.80},
        {0.92,    0.91,    0.81,    0.62,    0.37,    0.16,    0.09,    0.21,    0.44,    0.60,    0.69,    0.85},
        {0.92,    0.92,    0.81,    0.64,    0.37,    0.15,    0.08,    0.17,    0.44,    0.60,    0.65,    0.83},
        {0.90,    0.92,    0.82,    0.61,    0.38,    0.16,    0.06,    0.19,    0.44,    0.60,    0.67,    0.86} };
    /*Etap 1 -- 2 pkt*/
    make_histogram(tem_Melb, hist);
    show_histogram_raw(hist);
    show_histogram(hist);
    ///*Etap 2 -- 3 pkt*/
    make_histogram_col(tem_Melb, hiscol);
    show_histogram_raw_col(hiscol);
    show_histogram_month(hiscol, Mar);
    ///*Etap 3 -- 2 pkt*/
    print_monthly_averages(tem_Melb, keyT_vals);
    return 0;
}
void make_histogram(float tab[YEARS][MONTHS], int his[BINS])
{
    int t =0;
    float k = 0;
    for (int p = 0; p < BINS; p++)
    {
        for (int i = 0; i < YEARS; i++)
        {
            for (int j = 0; j < MONTHS; j++)
                if (tab[i][j] >= k && tab[i][j] < (k + 1.00/BINS)) t++;
        }
        k += 1.00/BINS;
        his[p] = t;
        t = 0;
    }
}
void show_histogram_raw(int his[BINS])
{
    for (int i = 0; i < BINS; i++)
        printf("%d ", his[i]);
    printf("\n");
}
void show_histogram(int his[BINS])
{
    float skok = 1.00/BINS;
    float p = 0;
    for (int i = 0; i < BINS; i++)
    {
        printf("%.2f - %.2f |", p, p + skok);
        for (int j = 0; j < his[i]; j++)
        {
            printf("*");
        }
        printf("\n");
        p += skok;
    }
}
void make_histogram_col(float tab[YEARS][MONTHS], int his[MONTHS][BINS])
{
    for (int i = 0; i < MONTHS; i++)
    {
        int licznik = 0;
        float skok = 1.00 / BINS;
        float p = 0;
        for (int t = 0; t < BINS; t++)
        {
            for (int k = 0; k < YEARS; k++)
                if (tab[k][i] >= p && tab[k][i] < (p + 1.00 / BINS)) licznik++;
            p += skok;
            his[i][t] = licznik;
            licznik = 0;
        }
    }
}
void show_histogram_raw_col(int his[MONTHS][BINS])
{
    for (int i = 0; i < MONTHS; i++)
    {
        for (int j = 0; j < BINS; j++)
            printf("%d ", his[i][j]);
        printf("\n");
    }
}
void show_histogram_month(int his[MONTHS][BINS], enum month choose_month)
{
    show_histogram(his[choose_month -1]);
}
float get_monthly_average(float tab[YEARS][MONTHS], enum month choosem)
{
    float srednia = 0; 
    for (int i = 0; i < YEARS; i++)
    {
        srednia += tab[i][choosem - 1] * (TEMPMAX - TEMPMIN) + TEMPMIN;
    }
    printf("%.2f", srednia / YEARS);
}
void print_monthly_averages(float tab[YEARS][MONTHS], enum month choosem[])
{
    for (int i = 0; i < MONTHS; i++)
    {
        printf("average temperature for month %d was: ", i+1);
        get_monthly_average(tab, choosem[i]);
        printf("\n");
    }
}
