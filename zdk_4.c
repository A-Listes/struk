#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (100)
#define MAX_SIZE (50)
#define SUCCESS (0)
#define FAIL (1)
#define BOLD "\x1B[1m"
#define RESET "\x1B[0m"

typedef struct pol *Position;

typedef struct pol
{
    int c;
    int e;
    Position next;

} pol;

int CleanUp(Position Head)
{

    Position P=NULL;

     while (Head->next)
    {
        P = Head->next;
        Head->next = P->next;
        free(P);
    }

    return SUCCESS;
}

int Zbroji_Iste_Eksponente(Position P)
{
    Position Y = NULL;
    Position Z = NULL;
    Position dup = NULL;
    Y = P;

    while (Y != NULL && Y->next != NULL)
    {
        Z = Y;

        while (Z->next != NULL)
        {

            if (Y->e == Z->next->e)
            {

                Y->c = Y->c + Z->next->c;
                dup = Z->next;
                Z->next = Z->next->next;

                free(dup);
            }
            else
                Z = Z->next;
        }
        Y = Y->next;
    }
    return SUCCESS;
}

int Sortiraj(Position P)
{

    Position Y, preth_Y, temp, end, T;
    Y = NULL;
    preth_Y = NULL;
    temp = NULL;
    end = NULL;

    while (P->next != end)
    {
        preth_Y = P;
        Y = P->next;
        while (Y->next != end)
        {

            if (Y->e > Y->next->e)
            {
                temp = Y->next;
                preth_Y->next = temp;
                Y->next = temp->next;
                temp->next = Y;

                Y = temp;
            }

            preth_Y = Y;
            Y = Y->next;
        }
        end = Y;
    }

    Zbroji_Iste_Eksponente(P);

    return SUCCESS;
}

int Zbroji(Position P, Position Y, Position Zbroj)
{

    while (P && Y)
    {
        if (P->e > Y->e)
        {
            Zbroj->e = Y->e;
            Zbroj->c = Y->c;
            Y = Y->next;
        }

        else if (P->e < Y->e)
        {
            Zbroj->e = P->e;
            Zbroj->c = P->c;
            P = P->next;
        }

        else
        {
            Zbroj->e = P->e;
            Zbroj->c = P->c + Y->c;
            P = P->next;
            Y = Y->next;
        }

        Zbroj->next = (Position)malloc(sizeof(pol));
        Zbroj = Zbroj->next;
        Zbroj->next = NULL;
    }

    while (P || Y)
    {
        if (P)
        {
            Zbroj->e = P->e;
            Zbroj->c = P->c;
            P = P->next;
        }

        if (Y)
        {
            Zbroj->e = Y->e;
            Zbroj->c = Y->c;
            Y = Y->next;
        }

        Zbroj->next = (Position)malloc(sizeof(pol));
        Zbroj = Zbroj->next;
        Zbroj->next = NULL;
    }

    return SUCCESS;
}

int Mnozi(Position P, Position Y, Position Z)
{

    Position temp;
    temp = Y;

    P = P->next;

    while (P != NULL)
    {
        while (Y != NULL)
        {
            Z->c = P->c * Y->c;
            Z->e = P->e + Y->e;
            Z->next = (Position)malloc(sizeof(pol));
            Z = Z->next;
            Z->next = NULL;
            Y = Y->next;
        }

        Y = temp;
        P = P->next;
    }

    return SUCCESS;
}

int Printaj(Position P)
{
    Position Z = P->next;

    while (Z != NULL)
    {
        if (Z->c != 0)
            printf("%dx^%d\t", Z->c, Z->e);
        Z = Z->next;
    }
    printf("\n");
    return SUCCESS;
}

int Unos(Position P, char *filename, char *p)
{

    int c = 0;
    int e = 0;
    int n = 0;
    FILE *fp = fopen(filename, "r");
    Position Z = NULL;

    if (fp == NULL)
    {
        printf("\nGreska pri otvaranju FILE-a!");
        return FAIL;
    }

    while (strlen(p) > 0)
    {

        sscanf(p, " %d %d %n", &c, &e, &n);

        if (c != 0)
        {
            Z = malloc(sizeof(pol));
            Z->c = c;
            Z->e = e;
            Z->next = P->next;
            P->next = Z;
        }
        p += n;
    }

    Sortiraj(P);
    return SUCCESS;
}

int main()
{

    pol Head1 = {.e = 0, .c = 0, .next = NULL};
    pol Head2 = {.e = 0, .c = 0, .next = NULL};
    pol Head3 = {.e = 0, .c = 0, .next = NULL};
    pol Head4 = {.e = 0, .c = 0, .next = NULL};
    Position P1 = &Head1;
    Position P2 = &Head2;
    Position P3 = &Head3;
    Position P4 = &Head4;
    char filename[MAX_NAME] = {0};
    char buffer[MAX_NAME] = {0};
    int n = 0;

    printf("\n\tUpisite ime file-a.\n");
    scanf(" %s", filename);
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("\nGreska pri otvaranju FILE-a!");
        return FAIL;
    }

    fgets(buffer, MAX_NAME, fp);
    Unos(P1, filename, buffer);

    fgets(buffer, MAX_NAME, fp);
    Unos(P2, filename, buffer);

    do
    {
        printf("\n%s**********************************%s\n", BOLD, RESET);
        printf(" %s%c********* ZADATAK 4. *********%c%s\n", BOLD, 92, 47, RESET);
        printf("  %s******************************%s\n", BOLD, RESET);
        printf("   %s%c******** POLINOMI ********%c%s\n", BOLD, 92, 47, RESET);
        printf("    %s**************************%s\n", BOLD, RESET);
        printf("\t       %sMENU%s\n", BOLD, RESET);

        printf("\n\tUnesite : \n   '1' - ispis prvog polinoma\n   '2' - ispis drugog polinoma");
        printf("\n   '3' - zbrajanje polinoma\n   '4' - mnozenje polinoma\n   '0' - izlaz\n\n");
        printf("    %s***************************%s\n\n", BOLD, RESET);
        scanf("%d", &n);

        if (n == 1)
        {
            printf("\n%d. polinom : ", n);
            Printaj(P1);
        }

        if (n == 2)
        {
            printf("\n%d. polinom : ", n);
            Printaj(P2);
        }

        if (n == 3)
        {
            printf("\nZbroj polinoma : ");
            Zbroji(P1, P2, P3);
            Printaj(P3);
        }

        if (n == 4)
        {
            printf("\nUmnozak polinoma : ");
            Mnozi(P1, P2, P4);
            Sortiraj(P4);
            Printaj(P4);
        }

        if (n == 0)
        {
            printf("\nDovidenja. \n");
            break;
        }
    } while (n != 0);

    CleanUp(P1);
    CleanUp(P2);
    CleanUp(P3);
    CleanUp(P4);
    fclose(fp);

    return 0;
}
