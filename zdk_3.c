#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_IME (100)
#define SUCCESS (0)
#define FAIL (-1)
#define BOLD "\x1B[1m"
#define RESET "\x1B[0m"

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
    Position Zadnji=NULL;

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
    
    return P;
}

Position Trazi_Prethodnika (Position P,char* ime, char* prezime, int god)
{
    Position Prethodnik=NULL;
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
    Position Prethodnik=NULL;
    Position Y=NULL;

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

Position Trazi_Iza (char* prezime, Position P)
{
    while((P!=NULL) && strcmp(prezime, P->prezime))
    {
        P=P->next;
    }

    if(P==NULL)
    {
        printf("\nNema trazene osobe.\n");
    }

    return P;
}

int UnosIza(char* prezime, char* novo_ime, char* novo_prezime, int novo_god, Position P)
{
    Position Y=NULL;
    P=Trazi_Iza(prezime,P);
    
    while((P!=NULL)&&(strcmp(P->prezime, prezime)))
    {
        P=P->next;
    }

    if(P==NULL)
    {
        printf("\nGreska!");
        return 0;
    }

    else
        {
            
            Y=Napravi_osobu(novo_ime, novo_prezime, novo_god);
            Y->next=P->next;
            P->next=Y;
        }

        return SUCCESS;
}

int UnosIspred(char* ime, char* prezime, int god, char* novo_ime, char* novo_prezime, int novo_god, Position P)
{
    Position Y=NULL;
    P=Trazi_Prethodnika(P,ime, prezime, god);
    
    while((P!=NULL)&&(strcmp(P->next->prezime, prezime)))
    {
        P=P->next;
    }

    if(P==NULL)
    {
        printf("\nGreska!");
        return 0;
    }

    else
        {
            Y=Napravi_osobu(novo_ime, novo_prezime, novo_god);
            Y->next=P->next;
            P->next=Y;
        }
        return SUCCESS;
}

int Sortiraj(Position P)
{
    Position Y, preth_Y, temp, end;
    Y=NULL;
    preth_Y=NULL;
    temp=NULL;
    end=NULL;

    while(P->next!=end)
    {
        preth_Y = P;
        Y = P->next;
        while(Y->next!=end)
        {
            if(strncmp(Y->prezime,Y->next->prezime,1)>0)
            {
                temp = Y->next;
                preth_Y->next = temp;
                Y->next = temp->next;
                temp->next = Y;

                Y=temp;
            }
            else if(strncmp(Y->prezime,Y->next->prezime,1)==0)
            {
                if(strncmp(Y->prezime,Y->next->prezime,2)>0)
                {
                temp = Y->next;
                preth_Y->next = temp;
                Y->next = temp->next;
                temp->next = Y;

                Y=temp;
                }
            }

            preth_Y=Y;
            Y=Y->next;
        }
        end=Y;
    }
    return SUCCESS;
}

int Upisi_u_File(char* filename, Position P)
{
    FILE* fp=NULL;
    fp=fopen(filename, "w");
    int n=0;
    char ime[MAX_IME]={0};
    char prezime[MAX_IME]={0};
    int god=0;


    if(fp==NULL)
    {
        printf("\nDoslo je do greske pri otvaranju FILE-a.\n");
        return FAIL;
    }
    
    do
    {
    printf("\n    %s***************************%s\n",BOLD, RESET); 
    printf("\t    %sFILE MENU%s\n", BOLD, RESET);
    printf("\n\t'1' za unos u listu \n\t'2' za unos u FILE \n\t'3' za povratak u pocetni menu\n");
    printf("\n    %s***************************%s\n\n",BOLD, RESET); 
    
    scanf("%d", &n);

    if(n==1)
    {
        printf("\n\tUnesite ime, prezime i godiste osobe : ");
        scanf(" %s %s %d", ime, prezime, &god);
        Unos_Pocetak(ime, prezime, god, P);
        Sortiraj(P);

    }

    else if(n==2)
    {
        Position Y = P->next;

        while(Y!=NULL)
        {
        fprintf(fp, "%s %s %d\n",Y->ime, Y->prezime, Y->god);
        Y=Y->next;
        }
    }

    else if(n==3)
    {
        break;
    }
        
    } while (n!=3);

    fclose(fp);
    return SUCCESS;
    
}

int Citanje_iz_FILE(char* filename, Position P)
{
    FILE* fp;
    fp=fopen(filename,"r");
    char buffer[MAX_IME]={0};
    char ime[MAX_IME]={0};
    char prezime[MAX_IME]={0};
    int god=0;

    
    if(fp==NULL)
    {
        printf("\n\tGreska pri otvaranju FILE-a.");
        return FAIL;
    }

    while(!feof(fp))
    {
         fscanf(fp, " %s %s %d", ime, prezime, &god);
         Unos_Pocetak(ime, prezime, god, P);
         Sortiraj(P); 
        
    }

    fclose(fp);

    return SUCCESS;
}

int Clean(Position P)
{
    Position Y=NULL;

    while(P)
    {
        Y=P->next;
        free(P);
        P=Y;
    }

    return SUCCESS;
}

int main()
{
    osoba Head = {.next = NULL, .ime = {0}, .prezime = {0}, .god = 0};
    Position P = &Head;
    char ime[MAX_IME]={0};
    char prezime[MAX_IME]={0};
    char novo_ime[MAX_IME]={0};
    char novo_prezime[MAX_IME]={0};
    char filename[MAX_IME]={0};
    int novo_god=0;
    int godiste=0;
    int n=0;

    do
    {
        printf("\n%s***********************************%s\n",BOLD, RESET); 
        printf(" %s%c******* ZADATAK 2. I 3. *******%c%s\n",BOLD, 92, 47, RESET);
        printf("  %s*******************************%s\n",BOLD, RESET); 
        printf("   %s%c****** VEZANE  LISTE ******%c%s\n",BOLD, 92, 47, RESET);
        printf("    %s***************************%s\n",BOLD, RESET); 
        printf("\t\t%sMENU%s\n", BOLD, RESET);
        printf("\n\t'1' za unos na pocetak\n\t'2' za unos na kraj");
        printf("\n\t'3' za trazenje po prezimenu\n\t'4' za brisanje elementa\n\t'5' za unos iza\n\t'6' za unos ispred\n\t'7' za sortiranje");
        printf("\n\t'8' za unos u FILE\n\t'9' za citanje iz FILE-a\n\t'10' za ispis\n\t'0' za izlaz\n\n");
        printf("    %s***************************%s\n\n",BOLD, RESET); 
        scanf("%d", &n);
    if (n==1)
    {
        printf("\n\tUnesite ime, prezime i godiste osobe : ");
        scanf(" %s %s %d", ime, prezime, &godiste);
        Unos_Pocetak(ime, prezime, godiste, P);
    }
    
    else  if (n==2)
    {
        printf("\n\tUnesite ime, prezime i godiste osobe : ");
        scanf(" %s %s %d", ime, prezime, &godiste);
        Unos_Kraj(P, ime, prezime, godiste);
    }

    else if (n==3)
    {
        printf("\n\tIzaberite prezime koje trazite : ");
        scanf(" %s", prezime);
        Trazi(prezime,P);

    }

    else if(n==4)
    {
        printf("\n\tIzaberite osobu koju zelite izbrisati : ");
        scanf(" %s %s %d", ime, prezime, &godiste);
        Brisi(P,ime, prezime, godiste);
    }

    

    else if(n==5)
    {
        printf("\n\tNapisite prezime osobe iza koje zelite dodati element : ");
        scanf(" %s", prezime);
        printf("\n\tUnesite podatke nove osobe : ");
        scanf(" %s %s %d", novo_ime, novo_prezime, &novo_god);
        UnosIza(prezime, novo_ime, novo_prezime, novo_god, P);
        
    }

    else if (n==6)
    {
        printf("\n\tNapisite podatke osobe ispred koje zelite dodati element : ");
        scanf(" %s %s %d", ime, prezime, &godiste);
        printf("\n\tUnesite podatke nove osobe : ");
        scanf(" %s %s %d", novo_ime, novo_prezime, &novo_god);
        UnosIspred(ime,prezime, godiste, novo_ime, novo_prezime, novo_god, P);
    
    }

    else if(n==7)
    {
        Sortiraj(P);
    }

    else if(n==8)
    {
        printf("\n\tUnesi ime FILE-a : ");
        scanf(" %s", filename);
        Upisi_u_File(filename, P);
    }

    else if(n==9)
    {
        printf("\n\tUnesi ime FILE-a : ");
        scanf(" %s", filename);
        Citanje_iz_FILE(filename, P);
    }

    else if(n==10)
    {
        Isprintaj(P);
    }

    else if(n==0)
    {
        break;
    }

    else 
        printf("\n\tKrivi unos!\n");
    } while (n!=0);

    Clean(P->next);

    printf("    %s***************************%s",BOLD, RESET); 
    printf("\n    %sUspjesno ste izasli iz programa!%s\n", BOLD, RESET);
    printf("    %s***************************%s\n\n",BOLD, RESET); 

    return 0;
}