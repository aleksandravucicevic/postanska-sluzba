#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define MAX 15

typedef struct
{
    int n;
    int lokacija[MAX];
    int ms[MAX][MAX];
} GRAF;

typedef struct
{
    int startCvor;
    int ciljniCvor;
    int tezina;
    int putanja[MAX];
    int duzinaPutanje;
} NajkracaPutanjaInfo;

void inicijalizacijaMreze(GRAF* grad)
{
    for(int i=0;i<grad->n;i++)
        grad->lokacija[i]=0;
    for(int i=0;i<grad->n;i++)
        for(int j=0;j<grad->n;j++)
            grad->ms[i][j]=0;
}

void initD(GRAF* g, int d[][MAX])
{
    for(int i=0;i<g->n;i++)
        for(int j=0;j<g->n;j++)
            d[i][j] = i==j? 0 : (g->ms[i][j] != 0? g->ms[i][j]:INFINITY); //INFINITY=2147483647
}

void initT(GRAF *g, int t[][MAX])
{
  for(int i=0;i<g->n;i++)
    for(int j=0;j<g->n;j++)
    {
        if(i==j || g->ms[i][j]==0)
            t[i][j]=-1;
        else
            t[i][j]=i;
    }
}

void ispisMatrice(int n, int m[][MAX])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            printf("%5d ", m[i][j]);
        printf("\n");
    }
}

void floyd(GRAF *g, int d[][MAX], int t[][MAX])
{
    int i, j, k;
    for(k=0;k<g->n;k++)
        for(i=0;i<g->n;i++)
        for(j=0;j<g->n;j++)
            if(d[i][j]>d[i][k]+d[k][j])
            {
                d[i][j]=d[i][k]+d[k][j];
                t[i][j]=t[k][j];
            }
}

void putanja(int i, int j, GRAF *g, int t[][MAX], int dest)
{
    if(i==j)
        printf("%d -> ", g->lokacija[i]);
    else if(t[i][j]==-1)
        printf("Nema putanje!");
    else
    {
        putanja(i, t[i][j], g, t, dest);
        printf("%d", g->lokacija[j]);
        dest != j ? printf(" -> ") : printf("");
    }
}

//Pronalaženje najkrace putanje od startCvora do krajnjegCvora
NajkracaPutanjaInfo pronadjiNajkracuPutanju(GRAF *g, int najkracaRastojanja[][MAX], int startCvor, int krajnjiCvor)
{
    NajkracaPutanjaInfo minPut;
    minPut.startCvor = startCvor;
    minPut.ciljniCvor = krajnjiCvor;
    minPut.tezina = najkracaRastojanja[startCvor][krajnjiCvor];

    // Inicijalizacija putanje
    int trenutniCvor = krajnjiCvor;
    int duzinaPutanje = 0;

    // Alociranje prostora za putanju
    minPut.duzinaPutanje = duzinaPutanje;
    minPut.putanja[duzinaPutanje] = krajnjiCvor;

    // Popunjavanje putanje unazad
    while (trenutniCvor != startCvor)
    {
        trenutniCvor = startCvor;
        duzinaPutanje++;
        minPut.putanja[duzinaPutanje] = trenutniCvor;
    }

    return minPut;
}

//Pronalaženje najkrace putanje od nekog cvora do neposjecenog cvora
NajkracaPutanjaInfo najkracaOdSvihPutanja(GRAF *g, int najkracaRastojanja[][MAX], int startCvor, int posjeceniCvorovi[MAX])
{
    NajkracaPutanjaInfo najkracaPutanja;
    int prvaIteracija=1;
    int posljednjiPosjeceniCvor=-1;

    for(int ciljniCvor=0;ciljniCvor<g->n;ciljniCvor++)
    {
        if(ciljniCvor!=startCvor && !posjeceniCvorovi[ciljniCvor])
        {
            NajkracaPutanjaInfo trenutnaPutanja=pronadjiNajkracuPutanju(g, najkracaRastojanja, startCvor, ciljniCvor);

            if (prvaIteracija || trenutnaPutanja.tezina<najkracaPutanja.tezina)
            {
                najkracaPutanja=trenutnaPutanja;
                prvaIteracija=0;
            }
        }
        posljednjiPosjeceniCvor=najkracaPutanja.ciljniCvor;
        posjeceniCvorovi[posljednjiPosjeceniCvor]=1;
    }

    return najkracaPutanja;
}

void detaljiPutanje(NajkracaPutanjaInfo np)
{
    printf("Pocetni cvor: %d\n", np.startCvor+1);
    printf(" Ciljni cvor: %d\n", np.ciljniCvor+1);
    printf(" Tezina putanje: %d", np.tezina);
}