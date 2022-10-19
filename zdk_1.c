#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256) 

int countStudentsFromFile(char* filename)
{
    FILE* fp = NULL;
    int count = 0;
    char buffer[MAX_LINE] = {0};

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Dear customer, the file %s didn't open!\r\n",filename);
        return FILE_DIDNT_OPEN_ERROR;
    }

    while (!feof(fp)) 
    {
        fgets(buffer,MAX_LINE,fp);
        if(strcmp("\n", buffer) != 0)
        {
            count++;
        }
    }

    fclose(fp);
    return count;
}
void memoryalloc (char* filename, stud* studenti, int number_of_students)
{
    FILE* fp = NULL;
    fp = fopen(filename, "r");
    int i=0;

    if (fp == NULL)
    {
        printf("Dear customer, the file %s didn't open!\r\n",filename);
    }
    
    studenti=malloc(countStudentsFromFile(filename)*sizeof(stud)); 
    
    while(!feof(fp))
    {
    
            fscanf (fp, " %s %s %d", studenti[i].name, studenti[i].surname, &studenti[i].points);
            i++;
    }
    Printing(studenti,countStudentsFromFile(filename));
    fclose(fp);
    free(studenti);

}
int main(void)
{
    char filename[MAX_FILE_NAME] = {0};
    stud* studenti=NULL;
    int number_of_students=0;
    
    printf("Insert filename > ");
    scanf(" %s", filename);

   
    number_of_students=countStudentsFromFile(filename);

    printf("Broj studenata u datoteci %s je %d", filename, countStudentsFromFile(filename));
    memoryalloc(filename, studenti, number_of_students);
    
    return 0;
}


