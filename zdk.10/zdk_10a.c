#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_NAME (100)
#define SUCCESS (0)
#define FAIL (1)
#define BOLD "\x1B[1m"
#define RESET "\x1B[0m"
#define P_NULL (2)
#define Brisi_Stablo (3)
#define NIZ (10)

typedef struct bin_stablo *Position;
typedef struct bin_stablo
{
    int brst;
    char grad[MAX_NAME];
    Position r;
    Position l;
} bin_stablo;

typedef struct lista *Node;
typedef struct lista
{
    char drzava[MAX_NAME];
    Node next;
    Position root;
}lista;

int Sortirani_Unos(Node Y, Node Head)
{
    Node P = Head;
    while(P->next!=NULL && (strcmp(P->next->drzava, Y->drzava) < 0 ))
    {
        P=P->next;
    }

    Y->next=P->next;
    P->next=Y;

    return SUCCESS;
}

int CityCmp(Position p, Position q)
{
    int result = 0;

    result = p->brst - q->brst;
    if(result == 0)
    {
        result = strcmp(p->grad, q->grad);
    }

    return result;
}

Position insert(Position p, Position q)
{

    if (p == NULL)
    {
        return q;
    }

    int result = 0;
    result = CityCmp(p,q);

    if (result < 0)
    {
        p->r = insert(p->r, q);
    }
    else if (result > 0)
    {
        p->l = insert(p->l, q);
    }
    return p;
}

Position stvori_binstablo(Position p, char* grad, int brst)
{
    Position q = NULL;
    q = (Position)malloc(sizeof(bin_stablo));
    strcpy(q->grad, grad);
    q->brst = brst;
    p = insert(p, q);

    return p;
}

int Ucitaj_Stablo(char* filename, Node Y)
{
    FILE* fp = NULL;
    fp=fopen(filename, "r");
    char grad[MAX_NAME] = {0};
    int brst = 0;

    if (fp == NULL)
    {
        printf("\nGreska pri otvaranju FILE-a! aaa");
        return FAIL;
    }

    while(!feof(fp))
    {
        fscanf(fp, "%s %d", grad, &brst);
        Y->root = stvori_binstablo(Y->root, grad, brst);
    }

    return SUCCESS;
}

int Citaj_FILE(FILE* fp, Node P)
{
    Node Y=NULL;
    char filename[MAX_NAME] = {0};

    while(!feof(fp))
    {
        Y=(Node)malloc(sizeof(lista));
        Y->next=NULL;
        Y->root=NULL;
        fscanf(fp, "%s %s", Y->drzava, filename);
        Sortirani_Unos(Y, P);
        Ucitaj_Stablo(filename, Y);

    }
    
    return SUCCESS;
}

Node Trazi_Drzavu(char *drzava, Node P)
{
    while ((P != NULL) && strcmp(drzava, P->drzava))
    {
        P = P->next;
    }

    if (P == NULL)
    {
        printf("\nNema trazene drzave!\n");
    }

    return P;
}

int Ispis_Gradova_MIN(Position Lokacija, int min_brst)
{
    if (Lokacija)
    {
        if(Lokacija->brst <= min_brst)
        {
            Ispis_Gradova_MIN(Lokacija->r, min_brst);
        }

        else
        {
            Ispis_Gradova_MIN(Lokacija->l, min_brst);
            printf("\n%s -> broj stanovnika: %d", Lokacija->grad, Lokacija->brst);
            Ispis_Gradova_MIN(Lokacija->r, min_brst);
        }
    }

    return SUCCESS;
}

int Ispis_Gradova(Position P)
{
    if (P == NULL)
    {
        return P_NULL;
    }

    Ispis_Gradova(P->l);
    printf("Grad: %s, Broj stanovnika: %d\n", P->grad, P->brst);
    Ispis_Gradova(P->r);

    return SUCCESS;
}

int Ispis_Drzava(Node Head)
{
    Node p = Head->next;

    while(p!=NULL)
    {
        printf("%s\n", p->drzava);
        Ispis_Gradova(p->root);
        printf("\n");
        p=p->next;
    }

    return SUCCESS;
}

int Brisi_stablo(Position p)
{

    if (p == NULL)
        return Brisi_Stablo;

    Brisi_stablo(p->l);
    Brisi_stablo(p->r);

    free(p);

    return Brisi_Stablo;
}

int CleanUp(Node Head)
{

    Node P = NULL;

    while (Head->next)
    {
        P = Head->next;
        Head->next = P->next;
        Brisi_stablo(P->root);
        free(P);
    }

    return SUCCESS;
}

int main()
{

    FILE* fp = NULL;
    fp = fopen("Drzave.txt", "r");
    lista Head = {.drzava = '\0', .next = NULL, .root = NULL};
    Node temp = NULL;
    char drzava[MAX_NAME] = {0};
    int min_brst = 0;
    int n=0;
    
    if (fp == NULL)
    {
        printf("\nGreska pri otvaranju FILE-a!");
        return FAIL;
    }

    Citaj_FILE(fp, &Head);
    Ispis_Drzava(&Head);

    printf("\n%s**********************************%s\n", BOLD, RESET);
    printf(" %s%c********* ZADATAK 10. *********%c%s\n", BOLD, 92, 47, RESET);
    printf("  %s******************************%s\n", BOLD, RESET);
    printf("   %s%c*********** DIG ***********%c%s\n", BOLD, 92, 47, RESET);
    printf("\n\t%sUpute%s: \n\t '1' - 'Trazi po drzavi' \n\t '2' - 'izlaz' \n\t '3' - 'ispis drzava' \n\t '4' - 'upute'\n\n", BOLD, RESET);
    printf("    %s**************************%s\n", BOLD, RESET);

    while(n!=2)
    {
        printf("\n\nOdabir : \n");
        scanf(" %d", &n);
        
        switch(n)
        {
            case 1:
                printf("\nPretrazite drzavu :");
                scanf(" %s", drzava);
                temp=Trazi_Drzavu(drzava, &Head);
                if(temp!=NULL)
                {
                    printf("\n%s->", temp->drzava);
                    printf("\nUnesite broj: ");
                    scanf("%d", &min_brst);
                    Ispis_Gradova_MIN(temp->root, min_brst);
                }
                break;

            case 2:
                CleanUp(&Head);
                break;


            case 3:
                Citaj_FILE(fp, &Head);
                Ispis_Drzava(&Head);
                break;

            case 4:
                printf("\n%s**********************************%s\n", BOLD, RESET);
                printf(" %s%c********* ZADATAK 10. *********%c%s\n", BOLD, 92, 47, RESET);
                printf("  %s******************************%s\n", BOLD, RESET);
                printf("   %s%c*********** DIG ***********%c%s\n", BOLD, 92, 47, RESET);
                printf("\n\t%sUpute%s: \n\t '1' - 'Trazi po drzavi' \n\t '2' - 'izlaz' \n\t '3' - 'ispis drzava' \n\t '4' - 'upute'\n\n", BOLD, RESET);
                printf("    %s**************************%s\n", BOLD, RESET);
                break;

            default:
                printf("\n%sKrivi unos! Slijedite upute!%s\n", BOLD, RESET);
                printf("\n%s**********************************%s\n", BOLD, RESET);
                printf(" %s%c********* ZADATAK 10. *********%c%s\n", BOLD, 92, 47, RESET);
                printf("  %s******************************%s\n", BOLD, RESET);
                printf("   %s%c*********** DIG ***********%c%s\n", BOLD, 92, 47, RESET);
                printf("\n\t%sUpute%s: \n\t '1' - 'Trazi po drzavi' \n\t '2' - 'izlaz' \n\t '3' - 'ispis drzava' \n\t '4' - 'upute'\n\n", BOLD, RESET);
                printf("    %s**************************%s\n", BOLD, RESET);
        }
    }

    printf("\n");
    fclose(fp);
    return 0;
}
