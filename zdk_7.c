#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME (100)
#define SUCCESS (0)
#define FAIL (1)
#define BOLD "\x1B[1m"
#define RESET "\x1B[0m"

typedef struct stablo *St_Pos; 
typedef struct stablo
{
  St_Pos child;
  St_Pos sibbling;
  char name[MAX_NAME];

} stablo;

typedef struct stog *Position; 
typedef struct stog
{
  Position next;
  St_Pos address;

} stog;

St_Pos stvori_root()
{
  St_Pos root = (stablo *)calloc(1, sizeof(stablo));

  if (NULL == root)
  {
    return root; 
  }
  strcpy(root->name, "C");

  return root;
}


Position stvori_stog()
{
  Position head = (stog *)calloc(1, sizeof(stog));

  if (NULL == head)
  {
    return head; 
  }

  return head;
}

St_Pos insert(St_Pos current, St_Pos new_dir)
{
  if (NULL == current)
  {
    return new_dir;
  }

  if (strcmp(current->name, new_dir->name) > 0)
  {
    new_dir->sibbling = current;
    return new_dir;
  }

  current->sibbling = insert(current->sibbling, new_dir);

  return current;
}


int md(St_Pos current)
{
  St_Pos new_dir = NULL;
  char name[MAX_NAME] = {'\0'};
  new_dir = (stablo *)calloc(1, sizeof(stablo));
  new_dir->sibbling = NULL;

  if (NULL == new_dir)
  {
    return FAIL;
  }

  printf("md ");
  scanf(" %s", name);

  strcpy(new_dir->name, name);

  if (current->child == NULL)
  {
    current->child = new_dir;
    return SUCCESS;
  }

  current->child = insert(current->child, new_dir);

  return SUCCESS;
}


int pop(Position head)
{
  if (NULL == head->next)
  {
    printf("\nStog je prazan.!");
    return SUCCESS;
  }

  Position temp = head->next;

  head->next = (head->next)->next;
  temp->next = NULL;
  free(temp);

  return SUCCESS;
}

int push(Position head, St_Pos *current)
{
  Position new_member = (stog *)calloc(1, sizeof(stog));
  if (NULL == new_member)
  {
    return FAIL;
  }

  new_member->address = *(current);
  new_member->next = head->next;
  head->next = new_member;

  return SUCCESS;
}

int change_directory(Position head, St_Pos *current)
{
  char name[MAX_NAME] = {'\0'};
  printf("cd ");
  scanf(" %s", name);
  St_Pos temp = (*current)->child;

  do
  {
    if (strcmp(temp->name, name) == 0)
    {
      push(head, current);
      (*current) = temp;
      return SUCCESS;
    }
    temp = temp->sibbling;

  } while (temp != NULL);

  return FAIL;
}

int Change_directory_back(Position head, St_Pos *current)
{
 
    printf("cd..");
  
    (*current) = head->next->address;
    pop(head);
    return SUCCESS;


  return SUCCESS;
}

int print(St_Pos current)
{
  St_Pos temp = current->child;

 
  printf("%s>\n", current->name);
  do
  {
    printf("  %s\n", temp->name);
    temp = temp->sibbling;

  } while (temp != NULL);

  return SUCCESS;
}

St_Pos delete_stablo(St_Pos current)
{
  if (current == NULL)
  {
    return NULL;
  }

  current->child = delete_stablo(current->child);
  current->sibbling = delete_stablo(current->sibbling);

  free(current);
  return NULL;
}

int delete_stog(Position head)
{
  Position temp = NULL;

  if (NULL == head->next)
  {
    free(head);
    return SUCCESS;
  }

  do
  {
    temp = head->next;
    head->next = head->next->next;
    temp->next = NULL;
    free(temp);

  } while (head->next != NULL);
  free(head);

  return SUCCESS;
}



int main()
{
  int n = 0;
  St_Pos root = stvori_root();  
  Position head = stvori_stog(); 
  St_Pos current = root;
    printf("\n%s**********************************%s\n", BOLD, RESET);
    printf(" %s%c********* ZADATAK 7. *********%c%s\n", BOLD, 92, 47, RESET);
    printf("  %s******************************%s\n", BOLD, RESET);
    printf("   %s%c*********** CMD ***********%c%s\n", BOLD, 92, 47, RESET);
    printf("\n\t%sUpute%s: \n\t '1' - 'md' \n\t '2' - 'cd dir'\n\t '3' - 'cd..' \n\t '4' - 'dir'\n\t '5' - 'izlaz'\n", BOLD, RESET);
    printf("    %s**************************%s\n", BOLD, RESET);

    while(n!=5)
    {
   
    scanf("%d", &n);

    switch (n)
    {
    case 1:
       md(current);
      break;

    case 2:
      change_directory(head, &current);
     
      break;

    case 3:
        Change_directory_back(head, &current);
        break;


    case 4:
      print(current);
      break;

    case 5:
    delete_stablo(root);
    delete_stog(head);
    
      break;

    default:
      break;
    }

    printf("\n");
    }

  return SUCCESS;
}
