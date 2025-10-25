#pragma once
#include <stdlib.h>
#include "paket.h"
#define MAX_DESCR_LENGTH 150

typedef struct cvor
{
    PAKET info;
    struct cvor* next;
} CVOR;

//Novi cvor prioritetnog reda
CVOR* noviCvor(PAKET paket)
{
    CVOR* novi=(CVOR*)malloc(sizeof(CVOR));
    if(novi==NULL) return 0;
    novi->info=paket;
    novi->next=NULL;
    return novi;
}

//Dodavanje u prioritetni red
int dodaj(CVOR **pq, PAKET paket)
{
    if(*pq==NULL)
    {
        *pq=noviCvor(paket);
        //ispisPaketa((*pq)->info);
        return *pq!=NULL;
    }

    CVOR* novi=noviCvor(paket);
    if(novi==NULL)
        return 0;

    CVOR *tmp=*pq;
    CVOR *p=NULL;

    while(tmp && tmp->info.prioritet >= paket.prioritet)
    {
        p=tmp;
        tmp=tmp->next;
    }

    if(p==NULL)  // Ako je novi čvor s najvećim prioritetom
    {
        novi->next=*pq;
        *pq=novi;
        //ispisPaketa((*pq)->info);
    }
    else
    {
        p->next=novi;
        novi->next=tmp;
        //ispisPaketa((*p->next).info);
    }
    
    return 1;
}

//Uzimanje iz prioritetnog reda
PAKET* get(CVOR** pq)
{
    if(*pq==NULL)
        return NULL;
    PAKET* paket=(PAKET*)malloc(sizeof(PAKET));
    if(paket==NULL)
        return NULL;
    
    CVOR* tmp=*pq;
    *paket=tmp->info;
    *pq=tmp->next;
    return paket;
}

//Ispis paketa u prioritetnom redu
void ispisReda(CVOR* pq, int* br)
{
    while(pq!=NULL)
    {
        (*br)++;
        ispisPaketa(pq->info, (*br));
        pq=pq->next;
    }
}

int dodajUVozilo(CVOR **vzl, PAKET paket) //nova f-ja
{
    if(*vzl==NULL)
    {
        *vzl=noviCvor(paket);
        //ispisPaketa((*vzl)->info);
        return *vzl!=NULL;
    }

    CVOR* novi=noviCvor(paket);
    if(novi==NULL)
        return 0;

    CVOR *tmp=*vzl;
    CVOR *p=NULL;

    while(tmp && tmp->info.prioritet >= paket.prioritet)//!!!
    {
        p=tmp;
        tmp=tmp->next;
    }

    if(p==NULL)  // Ako je novi čvor s najvećim prioritetom
    {
        novi->next=*vzl;
        *vzl=novi;
        //ispisPaketa((*vzl)->info);
    }
    else
    {
        p->next=novi;
        novi->next=tmp;
        //ispisPaketa((*p->next).info);
    }
    
    return 1;
}