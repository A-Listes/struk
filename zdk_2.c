#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME (100)
#define SUCCESS (0)
#define FAIL (-1)

typedef struct osoba* Position;
typedef struct osoba
{
    char ime[MAX_IME];
    char prezime[MAX_IME];
    int god;
    Position next;
}osoba;

Position Napravi_osobu (char* ime, char* prezime, int god)
{
    Position nova_osoba = NULL;
    nova_osoba= (Position) malloc(sizeof(osoba));

    if (nova_osoba == NULL)
    {
        printf("Greska!");
        return 0;
    }

    else 
    {
        strcpy(nova_osoba->ime, ime);
        strcpy(nova_osoba->prezime, prezime);
        nova_osoba->god=god;
        nova_osoba->next=NULL;
    }

    return nova_osoba;

}

int Unos_Pocetak(char* ime, char* prezime, int god, Position P)
{
     Position nova_osoba = NULL;
     nova_osoba = Napravi_osobu(ime,prezime,god);

     if (nova_osoba == NULL)
     {
        return FAIL;
     }

     nova_osoba->next=P->next;
     P->next=nova_osoba;
     
   return SUCCESS;
}

int Isprintaj (Position P)
{
    Position Y=P->next;
    
    if (Y==NULL)
    {
        printf("\nLista je prazna.");
    }

    while (Y!=NULL)
    {
        printf("\n Ime : %s, Prezime : %s, Godina rođenja : %d\n", Y->ime, Y->prezime, Y->god);
        Y=Y->next;
    }

    return SUCCESS;
}

Position Trazi_Zadnjeg(Position P)
{
    Position Y=P;
    while(Y->next!=NULL)
    {
        Y=Y->next;
    }

    return Y;
}

int Unos_Kraj(Position P, char* ime, char* prezime, int god)
{
    Position nova_osoba=NULL;
    Position Zadnji;

    nova_osoba=Napravi_osobu(ime, prezime, god);

    if(nova_osoba==NULL)
    {
        printf("\nGreska!");
        return FAIL;
    }

    Zadnji=Trazi_Zadnjeg(P);
    nova_osoba->next=Zadnji->next;
    Zadnji->next=nova_osoba;

    return SUCCESS;
}

Position Trazi (char* prezime, Position P)
{
    while((P!=NULL) && strcmp(prezime, P->prezime))
    {
        P=P->next;
    }

    if(P==NULL)
    {
        printf("\nNema trazene osobe.\n");
    }

    else 
        printf("\nOsoba je u listi.\n");
    
    return SUCCESS;
}

Position Trazi_Prethodnika (Position P,char* ime, char* prezime, int god)
{
    Position Prethodnik;
    Prethodnik=P;
    P=P->next;
    while((P!=NULL)&&((strcmp(ime, P->ime))||strcmp(prezime, P->prezime)||(god!=P->god)))
    {
        Prethodnik=Prethodnik->next;
        P=P->next;
    }
    return Prethodnik;
}

int Brisi(Position P, char* ime, char* prezime , int god)
{
    Position Prethodnik;
    Position Y;

    Prethodnik=Trazi_Prethodnika(P, ime , prezime , god);
    
    if(Prethodnik==NULL)
    {
        printf("\nNema prethodnika.\n");
        return FAIL;
    }

    else
        {
            Y=Prethodnik->next;
            Prethodnik->next=Y->next;
            free(Y);

            return SUCCESS;
        }

        return SUCCESS;

}



int main()
{
    osoba Head = {.next = NULL, .ime = {0}, .prezime = {0}, .god = 0};
    Position P = &Head;
    char ime[MAX_IME];
    char prezime[MAX_IME];
    int godiste;
    int n;

    do
    {
        printf("\nUpisite: \n'1' za unos na pocetak \n'2' za unos na kraj\n'3' za trazenje po prezimenu\n'4' za brisanje elementa\n'0' za ispis\n");
        scanf("%d", &n);
    if (n==1)
    {
        printf("\nUnesite ime, prezime i godiste osobe :");
        scanf(" %s %s %d", ime, prezime, &godiste);
        Unos_Pocetak(ime, prezime, godiste, P);
    }
    
    else  if (n==2)
    {
        printf("\nUnesite ime, prezime i godiste osobe :");
        scanf(" %s %s %d", ime, prezime, &godiste);
        Unos_Kraj(P, ime, prezime, godiste);
    }

    else if (n==3)
    {
        printf("\nIzaberite prezime koje trazite:");
        scanf(" %s", prezime);
        Trazi(prezime,P);

    }

    else if(n==4)
    {
        printf("\nIzaberite osobu koju zelite izbrisati:\n");
        scanf(" %s %s %d", ime, prezime, &godiste);
        Brisi(P,ime, prezime, godiste);
    }

    else if(n==0)
    {
        Isprintaj(P);
    }

    else 
        printf("\nKrivi unos!\n");
    } while (n!=0);
    
      
    return 0;
}