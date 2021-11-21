#include <stdio.h>
#include <stdlib.h>



int main()
{
    FILE * fptr;
    fptr = fopen("test.txt", "w");

    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    char name[50], c ;
    int marks, i , num;
    printf("Enter the number of students: "); 
    scanf("%d", &num);

    for(int i =0; i<num; i++)
    {
        printf("For student%d\nEnter the name: ", i+1);
        scanf("%s", name);
        printf("Enter marks: ");
        scanf("%d", &marks);
        fprintf(fptr, "\n Name: %s \n Marks : %d\n", name, marks);

    }

    fclose(fptr);

    fptr = fopen("test.txt", "r");

    char letter ;
    letter= fgetc(fptr);
    while(letter!=EOF)
    {
        printf("%c", letter);
        letter = fgetc(fptr);
    }   
}