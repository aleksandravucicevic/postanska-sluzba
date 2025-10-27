#pragma once
#include <stdio.h>
#include "red.h"
#define MAX_PAKETA 50

typedef struct
{
    double maxTezina;
    PAKET* niz;
} VOZILO;

void punjenjeVozila(CVOR** pq, VOZILO* v, int* brUspjesno, int* brNeuspjesno)
{
    FILE *txt3;
    PAKET* tmp;
    if(txt3=fopen("visak_paketa.txt","w"))
    {
        v->niz=(PAKET*)malloc(sizeof(PAKET)*MAX_PAKETA);
        double masaPaketa=0;
        int i=0;
        *brUspjesno=0, *brNeuspjesno=0;
        int br=0;
        while(tmp=get(pq))
        {
            if(masaPaketa+tmp->masa<=v->maxTezina)
            {
                v->niz[i]=*tmp;
                masaPaketa+=tmp->masa;
                (*brUspjesno)++;
                ispisPaketa(v->niz[i], *brUspjesno);
            }
            else
            {
                if(fprintf(txt3,"%d.) %s, %s (masa: %.2lf) - na adresu %d sa prioritetom %d\n", ++br ,tmp->naziv, tmp->opis, tmp->masa, tmp->adresa, tmp->prioritet))
                    (*brNeuspjesno)++;
            }
            free(tmp);
            i++;
        }
        fclose(txt3);
    }
}