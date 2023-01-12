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
    int el;
    Position r;
    Position l;
} bin_stablo;

Position insert(Position p, Position q)
{
    if (p == NULL)
    {
        return q;
    }
    if (p->el > q->el)
    {
        p->r = insert(p->r, q);
    }
    else if (p->el < q->el)
    {
        p->l = insert(p->l, q);
    }
    else
    {
        p->l = insert(p->l, q);
    }
    return p;
}

Position stvori_binstablo(Position p, int n)
{
    Position q = NULL;
    q = (Position)malloc(sizeof(bin_stablo));
    q->el = n;
    p = insert(p, q);

    return p;
}

int Zbroji(Position Lokacija)
{
    if (Lokacija)
    {
        return (Lokacija->el + Zbroji(Lokacija->r) + Zbroji(Lokacija->l));
    }
    else
    {
        return 0;
    }
}

int replace(Position t_Lokacija)
{
    int zbroj = 0;
    if (t_Lokacija)
    {
        zbroj = Zbroji(t_Lokacija) - t_Lokacija->el;
        if (t_Lokacija->l)
        {
            t_Lokacija->l->el = replace(t_Lokacija->l);
        }
        if (t_Lokacija->r)
        {
            t_Lokacija->r->el = replace(t_Lokacija->r);
        }
    }

    return zbroj;
}

int file_infix(Position P, FILE* fp ) 
{
   
    if (P == NULL)
    {
        return P_NULL;
    }

    file_infix(P->l, fp);
    fprintf(fp, "%d\t", P->el);
    file_infix(P->r, fp);

    return SUCCESS;

}

int upis_FILE(Position P)
{   
    FILE* fp = NULL;
   
    fp=fopen("inorder.txt", "a");
    if (fp == NULL)
    {
        printf("\nGreska pri otvaranju FILE-a!");
        return FAIL;
    }

    file_infix(P, fp);
    fprintf(fp, "\n\n");

    fclose(fp);
    return SUCCESS;
}

 int print_infix(Position p)
{
    if (p == NULL)
    {
        return P_NULL;
    }

    print_infix(p->l);
    printf("%d\t", p->el);
    print_infix(p->r);

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

int main()
{
    Position root = NULL;
    Position rand_root = NULL;
    int n=0;
    int i=0;
    int niz[NIZ] = {2,5,7,8,11,1,4,2,3,7};

    srand(time(NULL));

    for(i=0;i<10;i++)
    {
        root = stvori_binstablo(root, niz[i]);
    } 

    print_infix(root);
    printf("\nroot = %d\n", root->el);

    
    
    root->el = replace(root);
    print_infix(root);
    printf("\nroot = %d\n", root->el);

    
    
    for(i=0;i<10;i++)
    {
        rand_root = stvori_binstablo(rand_root, ((rand()%(89-11+1))+10));
    }

    print_infix(rand_root);
    printf("\nroot = %d\n", rand_root->el);
    upis_FILE(rand_root);

    rand_root->el = replace(rand_root);
    print_infix(rand_root);
    printf("\nroot = %d\n", rand_root->el);
    upis_FILE(rand_root);

    Brisi_stablo(root);
    Brisi_stablo(rand_root);
    
    return 0;
}