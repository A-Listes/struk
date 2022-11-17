#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_NAME (100)
#define MAX_SIZE (50)
#define SUCCESS (0)
#define FAIL (1)
#define BOLD "\x1B[1m"
#define RESET "\x1B[0m"

typedef struct fix* Position;

typedef struct fix
{

    float broj;
    Position next;

}fix;

int Isprintaj(Position P)
{
    Position Z = P->next;

    while (Z != NULL)
    {
        printf("%f\n", Z->broj);
        Z = Z->next;
    }
    printf("\n");

    return SUCCESS;
}

int Brisi(Position P)
{

    Position Y=NULL;
    Y=P->next;
    P->next=Y->next;
    free(Y);

    return SUCCESS;
}

int Operator(char z, Position P, int* count)
{
    float rezultat=0;
    Position Y=P->next;

    switch (z)
    {
        case '+':
            if((*count)>=2)
            {   
                rezultat=Y->next->broj+P->next->broj;
                Brisi(P);
                P->next->broj=rezultat;
                (*count)--;
                Isprintaj(P);
            }
            
            else 
                printf("\nNema dovoljno elemenata u stogu za zbrajanje.\n");
            
            break;

        case '*':
            if((*count)>=2)
            {
                rezultat=Y->next->broj*P->next->broj;
                Brisi(P);
                P->next->broj=rezultat;
                (*count)--;
                Isprintaj(P);
            }

            else
                printf("\nNema dovoljno elemenata u stogu za mnozenje.\n");

            break;

        case '-':
            if((*count)>=2)
                {
                    rezultat=Y->next->broj-P->next->broj;
                    Brisi(P);
                    P->next->broj=rezultat;
                    (*count)--;
                    Isprintaj(P);
                }
            
            else
                printf("\nNema dovoljno elemenata u stogu za oduzimanje.\n");
            
            break;

        case '/':
            if((*count)>=2)
                {
                    rezultat=Y->next->broj/P->next->broj;
                    Brisi(P);
                    P->next->broj=rezultat;
                    (*count)--;
                    Isprintaj(P);
                }
            
            else
                printf("\nNema dovoljno elemenata u stogu za djeljenje.\n");
            
            break;

        default:
            printf("\nNezadovoljiv znak.\n");

    }

    return SUCCESS;

}



int Unos(Position P, char* p)
{
    int n=0;
    float f=0;
    char c='\0';
    Position Y=NULL;
    int count=0;
  

   while(strlen(p)>0)
    {
        if(sscanf(p, " %f %n", &f, &n) == 1)
        {
            Y=(Position)malloc(sizeof(fix));
            Y->broj=f;
            Y->next=P->next;
            P->next=Y;
            count++;
            Isprintaj(P);
        }

        else 
        {
            sscanf(p, "%c %d", &c, &n);
            Operator(c, P, &count);
        }
    p+=2;
    }

    if(count!=1)
    {
        printf("\nNije zadovoljen uvjet da ostane jedan element u stogu.\n");
    }

    return SUCCESS;
}



int main()
{
    fix Head = {.broj=0, .next = NULL};
    Position P = &Head;
    FILE* fp=NULL;
    char filename[MAX_NAME]= {0};
    char buffer[MAX_SIZE]={0};
    char* p=NULL;

    printf("\n\tUpisite ime file-a.\n");

    scanf(" %s", filename);
    fp=fopen(filename, "r");

     if (fp == NULL)
    {
        printf("\nGreska pri otvaranju FILE-a!");
        return FAIL;
    }

    fgets(buffer, MAX_SIZE, fp );
    p=buffer;
    Unos(P,p);

    return 0;
}