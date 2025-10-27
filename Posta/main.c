#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#include "graf.h"
#include "paket.h"
#include "red.h"
#include "dostavnoVozilo.h"
#define MIN_PAKETA 5
#define MAX_LINE_LENGTH 220
#define MAX_NAME_LENGTH 50
#define MAX_DESCR_LENGTH 150
#define MAX_ADRESS_LENGTH 6
#define MAX_MASS_LENGTH 6
#define MAX_PRIORITY_LENGTH 4
#define MAX_PATH_LENGTH 20

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

    //Ucitavanje mreze grada   
    GRAF grad;
    FILE *txt1;
    if(txt1=fopen("grad1.txt","r"))
    {
        char* c=(char*)malloc(10*sizeof(char));
        fgets(c,6,txt1);
        grad.n=atoi(c);

        inicijalizacijaMreze(&grad);

        for(int i=0;i<grad.n;i++)
        {
            fgets(c,6,txt1);
            grad.lokacija[i]=atoi(c);
        }

        for(int i=0;i<grad.n;i++)
            for(int j=0;j<grad.n;j++)
            {
                fgets(c,6,txt1);
                grad.ms[i][j]=atoi(c);
            }
            
        free(c);
        fclose(txt1);
    }

    printf("\nBroj mjesta u gradu na koje treba dostaviti paket: %d\n", grad.n-1);
    printf("Lokacije: ");
    for(int i=1;i<grad.n;i++)
        printf("%d ", grad.lokacija[i]);
    printf("\nUdaljenosti:\n");
    ispisMatrice(grad.n,grad.ms);
    printf("-------------------------------------------\n");

    int najkracaRastojanja[MAX][MAX];
    initD(&grad,najkracaRastojanja);
    int prethodnici[MAX][MAX];
    initT(&grad,prethodnici);
    
    floyd(&grad,najkracaRastojanja,prethodnici);
    printf("NAJKRACA RASTOJANJA(FLOYD):\n");
    ispisMatrice(grad.n,najkracaRastojanja);
    printf("-------------------------------------------\n");

    //Formiranje prioritetnog reda sa paketima iz CSV fajla
    CVOR** pq=(CVOR**)malloc(sizeof(CVOR*));
    *pq=NULL;

    PAKET tmp;
    FILE* txt2;
    if(txt2=fopen("posta1.csv","r"))
    {
        char* line=(char*)malloc(sizeof(char)*MAX_LINE_LENGTH);
        while(fgets(line,MAX_LINE_LENGTH,txt2)!=NULL)
        {
            int len=strlen(line);
            if (len>0 && line[len-1]=='\n')
                line[len-1]='\0';
            
            char* token=strtok(line, ",");
            tmp.naziv=strdup(token);
        
            token=strtok(NULL,",");
            tmp.opis=strdup(token);

            token=strtok(NULL, ",");
            tmp.adresa=atoi(token);

            token=strtok(NULL, ",");
            tmp.masa=atof(token);

            token=strtok(NULL, ",");
            tmp.prioritet=atoi(token);

            //Dodavanje u prioritetni red
            dodaj(pq, tmp);
        }
        //free(tmp.naziv);
        //free(tmp.opis);
        free(line);
        fclose(txt2);
    }
    int brPaketa=0;
    printf("\nU posti sljedeci paketi cekaju na isporuku:\n");
    ispisReda(*pq, &brPaketa);

    VOZILO v;
    v.maxTezina=250;
    int uspjesno=0, neuspjesno=0;
    printf("\nU vozilo su ubačeni sljedeći paketi:\n");
    punjenjeVozila(pq,&v,&uspjesno,&neuspjesno);

    int startCvor;
    NajkracaPutanjaInfo najPutanje[MAX];
    int posjeceniCvorovi[MAX]={1};
    for(int i=0;i<grad.n-1;i++) //od 0 do grad.n-1 jer toliko grana nam treba da bismo obisli svih n cvorova grafa grad
    {
        startCvor=i;
        najPutanje[i]=najkracaOdSvihPutanja(&grad,najkracaRastojanja,startCvor,posjeceniCvorovi);
        posjeceniCvorovi[najPutanje[i].ciljniCvor]=1;
    }

    int b=0;
    printf("\nKretanje vozila:\n");
    printf("----------------\n");
    for(int i=0;i<grad.n-1;i++)
    {
        printf("%d.)", ++b);
        detaljiPutanje(najPutanje[i]);
        int vp=0;
        printf("\nIz vozila se istovaraju sljedeci paketi:\n");
        for(int j=0;j<uspjesno;j++)
        {
            if(najPutanje[i].ciljniCvor+1==v.niz[j].adresa)
            {
                vp++;
                ispisNazivaPaketa(v.niz[j],vp);
            }
        }
        if(vp==0)
            printf("~NEMA PAKETA ZA ISPORUKU NA OVOJ ADRESI!\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }

    //Cijela putanja vozila
    int start;
    int cijeliPut[MAX]={1};
    NajkracaPutanjaInfo pom;
    int tmpPosjeceni[MAX]={1};
    for(int i=0;i<grad.n-1;i++)
    {
        start=i;
        pom=najkracaOdSvihPutanja(&grad,najkracaRastojanja,start,tmpPosjeceni);
        int j=0;
        while(j<=pom.duzinaPutanje)
        {
            cijeliPut[i]=pom.putanja[j];
            j++;
        }
    }
    printf("\n=>Putanja kretanja vozila: ");
    for(int i=0;i<grad.n-2;i++)
    {
        printf("%d->", cijeliPut[i]);
    }
    printf("%d", cijeliPut[grad.n-2]);
    printf("\n\n");

    //Statistika
    printf("\nUkupan broj paketa koji su se nalazili u posti: %d\n", brPaketa);
    printf("Broj uspjesno dostavljenih paketa: %d\n", uspjesno);
    printf("Broj neisporucenih paketa: %d\n", neuspjesno);
    double procenat=(double)uspjesno/brPaketa;
    printf("\n=>Procenat dostavljenih paketa: %.2lf[%%]\n\n", procenat*100);

    free(v.niz);

    return 0;
}