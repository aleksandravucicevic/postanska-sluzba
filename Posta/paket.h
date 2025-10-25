#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *naziv;
    char *opis;
    int adresa;
    double masa;
    int prioritet;
} PAKET;

void ispisPaketa(PAKET p, int br)
{
    printf("%d.) %s [%s] (masa: %.2lf) - na adresu %d, sa prioritetom %d\n", br,p.naziv, p.opis, p.masa, p.adresa, p.prioritet);
}

void ispisNazivaPaketa(PAKET p, int br)
{
    printf("%d.) %s (masa: %.2lf, prioritet: %d)\n", br, p.naziv, p.masa, p.prioritet);
}