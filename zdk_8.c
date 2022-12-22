#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME (100)
#define SUCCESS (0)
#define FAIL (1)
#define BOLD "\x1B[1m"
#define RESET "\x1B[0m"
#define P_NULL (2)
#define Brisi_Stablo (3)

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
    if (p->el < q->el)
    {
        p->r = insert(p->r, q);
    }
    else if (p->el > q->el)
    {
        p->l = insert(p->l, q);
    }
    else
    {
        free(q);
    }
    return p;
}

Position stvori_binstablo(Position p)
{
    int n = 0;
    Position q = NULL;
    q = (Position)malloc(sizeof(bin_stablo));
    printf("\nUnesite broj koji zelite unijeti : ");
    scanf("%d", &n);
    q->el = n;
    p = insert(p, q);

    return p;
}

Position findMin(Position p)
{
    if (p == NULL)
    {
        return p;
    }

    else if (p->l == NULL)
    {
        return p;
    }

    return findMin(p->l);
}

Position findMax(Position p)
{
    if (p != NULL)
    {
        while (p->r != NULL)
        {
            p = p->r;
        }
    }

    return p;
}

Position Trazi(Position p, int x)
{

    if (p == NULL)
    {
        printf("\nBroj nije pronaden!\n");
        return p;
    }

    if (x < p->el)
    {
        return Trazi(p->l, x);
    }

    else if (x > p->el)
    {
        return Trazi(p->r, x);
    }

    printf("\nBroj je uspjesno pronaden!\n");
    return p;
}

Position delete(Position p, int br)
{
    if (p == NULL)
    {
        printf("\nBroj nije pronaden!\n");
        return NULL;
    }

    if (p->el < br)
    {
        p->r = delete (p->r, br);
    }
    else if (p->el > br)
    {
        p->l = delete (p->l, br);
    }
    else
    {
        if (p->l)
        {
            Position temp = findMax(p->l);
            p->el = temp->el;
            p->l = delete (p->l, temp->el);
        }
        else if (p->r)
        {
            Position temp = findMin(p->r);
            p->el = temp->el;
            p->r = delete (p->l, temp->el);
        }
        else
        {
            free(p);
            return NULL;
        }
    }
    return p;
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

int print_postfix(Position p)
{
    if (p == NULL)
    {
        return P_NULL;
    }

    print_postfix(p->l);
    print_postfix(p->r);
    printf("%d\t", p->el);

    return SUCCESS;
}

int print_prefix(Position p)
{
    if (p == NULL)
    {
        return P_NULL;
    }

    printf("%d\t", p->el);
    print_prefix(p->l);
    print_prefix(p->r);

    return SUCCESS;
}


int print_trenutne_razine(Position p, int razina)
{

    if (p == NULL)
        return P_NULL;

    if (razina == 1)
        printf("%d\t", p->el);

    else if (razina > 1)
    {
        print_trenutne_razine(p->l, razina - 1);
        print_trenutne_razine(p->r, razina - 1);
    }

    return SUCCESS;
}

int visina(Position p)
{

    if (p == NULL)
        return 0;

    else
    {
        int lvisina = visina(p->l);
        int dvisina = visina(p->r);
        if (lvisina > dvisina)
            return (lvisina + 1);
        else
            return (dvisina + 1);
    }
}

int print_levelorder(Position p)
{

    int h = visina(p);
    int i=0;

    for (i = 1; i <= h; i++)
    {
        print_trenutne_razine(p, i);
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

int main()
{

    Position root = NULL;
    Position temp = root;
    int n = 0;
    int brisi = 0;
    int trazi = 0;

    printf("\n%s**********************************%s\n", BOLD, RESET);
    printf(" %s%c********* ZADATAK 8. *********%c%s\n", BOLD, 92, 47, RESET);
    printf("  %s******************************%s\n", BOLD, RESET);
    printf("   %s%c*********** BSP ***********%c%s\n", BOLD, 92, 47, RESET);
    printf("\n\t%sUpute%s: \n\t '1' - 'dodaj' \n\t '2' - 'brisi'\n\t '3' - 'trazi' \n\t '4' - 'inorder'\n\t '5' - 'preorder'\n\t '6' - 'postorder'\n\t '7' - 'levelorder'\n\t '8' - 'izlaz'\n\t '9' - 'upute'\n\n", BOLD, RESET);
    printf("    %s**************************%s\n", BOLD, RESET);

    while (n != 8)
    {
        printf("Odabir : \n");
        scanf(" %d", &n);
        system("clear");
        switch (n)
        {
        case 1:
            root = stvori_binstablo(root);
            break;

        case 2:
            printf("\nBrisi : ");
            scanf("%d", &brisi);
            root = delete (root, brisi);
            break;

        case 3:
            printf("\nTrazi : ");
            scanf("%d", &trazi);
            temp = Trazi(root, trazi);
            break;

        case 4:
            print_infix(root);
            printf("\nroot = %d\n", root->el);
            break;

        case 5:
            print_prefix(root);
            printf("\nroot = %d\n", root->el);
            break;

        case 6:
            print_postfix(root);
            printf("\nroot = %d\n", root->el);
            break;

        case 7:
            print_levelorder(root);
            printf("\nroot = %d\n", root->el);
            break;

        case 8:
            Brisi_stablo(root);
            break;

        case 9:
            printf("\n%s**********************************%s\n", BOLD, RESET);
            printf(" %s%c********* ZADATAK 8. *********%c%s\n", BOLD, 92, 47, RESET);
            printf("  %s******************************%s\n", BOLD, RESET);
            printf("   %s%c*********** BSP ***********%c%s\n", BOLD, 92, 47, RESET);
            printf("\n\t%sUpute%s: \n\t '1' - 'dodaj' \n\t '2' - 'brisi'\n\t '3' - 'trazi' \n\t '4' - 'inorder'\n\t '5' - 'preorder'\n\t '6' - 'postorder'\n\t '7' - 'levelorder'\n\t '8' - 'izlaz'\n\t '9' - 'upute'\n\n", BOLD, RESET);
            printf("    %s**************************%s\n", BOLD, RESET);
            break;

        default:
            printf("\n%sKrivi unos! Slijedite upute!%s\n", BOLD, RESET);
            printf("\n%s**********************************%s\n", BOLD, RESET);
            printf(" %s%c********* ZADATAK 8. *********%c%s\n", BOLD, 92, 47, RESET);
            printf("  %s******************************%s\n", BOLD, RESET);
            printf("   %s%c*********** BSP ***********%c%s\n", BOLD, 92, 47, RESET);
            printf("\n\t%sUpute%s: \n\t '1' - 'dodaj' \n\t '2' - 'brisi'\n\t '3' - 'trazi' \n\t '4' - 'inorder'\n\t '5' - 'preorder'\n\t '6' - 'postorder'\n\t '7' - 'levelorder'\n\t '8' - 'izlaz'\n\t '9' - 'upute'\n\n", BOLD, RESET);
            printf("    %s**************************%s\n", BOLD, RESET);
        }
    }

    return 0;
}
