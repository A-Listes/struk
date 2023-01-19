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

typedef struct lista* Node;
typedef struct lista
{
    char grad[MAX_NAME];
    int brst;
    Node next;
} lista;

typedef struct bin_stablo* Position;
typedef struct bin_stablo
{
    char drzava[MAX_NAME];
    char filename[MAX_NAME];
    Position l;
    Position r;
    Node Head;
} bin_stablo;


Position insert(Position P, Position Q)
{

    if (!P)
    {
        return Q;
    }
    if (strcmp(P->drzava, Q->drzava) < 0)
    {
        P->r = insert(P->r, Q);

        return P;
    }
    else if (strcmp(P->drzava, Q->drzava) > 0)
    {
        P->l = insert(P->l, Q);

        return P;
    }
    else
    {
        free(Q);

        return P;
    }
}

Position stvori_binstablo()
{
    Position q = NULL;
    q = (Position)malloc(sizeof(bin_stablo));

    if(!q)
    {
        printf("\nPogreska pri alokaciji memorije bin stabla!");
        return NULL;
    }

    q->l=NULL;
    q->r=NULL;
    q->Head=NULL;
    
    return q;
}

Position Citaj_FILE(Position root)
{   
    FILE* fp=NULL;
    fp=fopen("Drzave.txt", "r");

    if (fp == NULL)
    {
        printf("\nGreska pri otvaranju FILE-a!");
    }

    while(!feof(fp))
    {
        Position P = NULL;
        P=stvori_binstablo();
        fscanf(fp, " %s %s", P->drzava, P->filename);
        root = insert(root, P); 
    }
    fclose(fp);
    return root;
}

Node Sortirani_Unos(Node Lokacija, Node P)
{
    if (!Lokacija)
    {
        return P;
    }

    if (Lokacija->brst < P->brst)
    {
        Lokacija->next = Sortirani_Unos(Lokacija->next, P);

        return Lokacija;
    }
    else if (Lokacija->brst > P->brst)
    {
        P->next = Lokacija;

        return P;
    }
    else
    {
        if (strcmp(Lokacija->grad, P->grad) < 0)
        {
            Lokacija->next = Sortirani_Unos(Lokacija->next, P);

            return Lokacija;
        }
        else if (strcmp(Lokacija->grad, P->grad) > 0)
        {
            P->next = Lokacija;

            return P;
        }
        else
        {
            free(P);
            return Lokacija;
        }
    }
}

Position Ucitaj_Gradove(Position temp)
{
    FILE* fp = NULL;
    fp = fopen(temp->filename, "r");

    if (fp == NULL)
    {
        printf("\nGreska pri otvaranju FILE-a!");
    }

    while(!feof(fp))
    {
        Node P = NULL;
        P = (Node)malloc(sizeof(lista));
        P->next=NULL;
        fscanf(fp, " %s %d", P->grad, &P->brst);
        temp->Head = Sortirani_Unos(temp->Head, P);
    }

    fclose(fp);
    return temp;

}

int Inorder_Drzave(Position root)
{
    Position temp = root;

    if(temp)
    {
        Inorder_Drzave(temp->l);
        temp = Ucitaj_Gradove(temp);
        Inorder_Drzave(temp->r);
    }

    return SUCCESS;
}

int Ispis_Gradova(Node Head)
{
    Node P = Head;

    while(P!=NULL)
    {
        printf("Grad: %s, Broj stanovnika: %d\n", P->grad, P->brst);
        P=P->next;
    }
    return SUCCESS;
}

int Ispis_Drzava(Position P)
{
    Position temp = P;
    if(temp)
    {
        Ispis_Drzava(temp->l);
        printf("\n%s\n", temp->drzava);
        Ispis_Gradova(temp->Head);
        Ispis_Drzava(temp->r);
    }
    return SUCCESS;
}

int Ispis_Gradova_MIN(Node Head)
{
    Node temp = Head;
    int min_brst=0;

    printf("\nUnesite broj: ");
    scanf("%d", &min_brst);
    while(temp)
    {
        if(temp->brst > min_brst)
        {
            printf("\n%s -> broj stanovnika: %d", temp->grad, temp->brst);
        }
        temp = temp->next;
    }

    return SUCCESS;
}

int Trazi_Drzavu(Position root, char* drzava)
{
    if(!root)
    {
        printf("\n%s nije u stablu!\n", drzava);
        return FAIL;
    }

   if(strcmp(root->drzava, drzava) == 0)
   {
        Ispis_Gradova_MIN(root->Head);
        printf("\n%s\n", root->drzava);
   }

   else if (strcmp(root->drzava, drzava) < 0)
   {
        Trazi_Drzavu(root->r, drzava);
   }

   else 
        Trazi_Drzavu(root->l, drzava);

    
    return SUCCESS;
}

int CleanUp(Node Head)
{

    Node P = NULL;

    while (Head->next)
    {
        P = Head->next;
        Head->next = P->next;
        free(P);
    }

    return SUCCESS;
}

int Brisi_stablo(Position p)
{

    if (p == NULL)
        return Brisi_Stablo;

    Brisi_stablo(p->l);
    Brisi_stablo(p->r);
    CleanUp(p->Head);

    free(p);

    return Brisi_Stablo;
}

int main()
{
    Position root = NULL;
    char drzava[MAX_NAME] = {0};
    int n=0;
   
    root=Citaj_FILE(root);
    Inorder_Drzave(root);
    Ispis_Drzava(root);

    printf("\n%s**********************************%s\n", BOLD, RESET);
    printf(" %s%c********* ZADATAK 10. *********%c%s\n", BOLD, 92, 47, RESET);
    printf("  %s******************************%s\n", BOLD, RESET);
    printf("   %s%c*********** DIG ***********%c%s\n", BOLD, 92, 47, RESET);
    printf("\n\t%sUpute%s: \n\t '1' - 'Trazi po drzavi' \n\t '2' - 'izlaz' \n\t '3' - 'ispis drzava' \n\t '4' - 'upute'\n\n", BOLD, RESET);
    printf("    %s**************************%s\n", BOLD, RESET);

    while(n!=2)
    {
        printf("\nOdabir : \n");
        scanf(" %d", &n);

        switch(n)
        {
            case 1:
                printf("\nPretrazite drzavu :");
                scanf(" %s", drzava);
                Trazi_Drzavu(root, drzava);
                break;
            
            case 2:
                Brisi_stablo(root);
                break;

            case 3:
                root=Citaj_FILE(root);
                Inorder_Drzave(root);
                Ispis_Drzava(root);
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
    
  
    printf("\n\n");
    return 0;
}