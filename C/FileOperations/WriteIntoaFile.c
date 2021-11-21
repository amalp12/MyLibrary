#include <stdio.h>
/*
           ## Operations on files##
    • Open a file using fopen
    • Read from a file using fscanf, fgetc or fread
    • Write into a file using fprintf or fwrite
    • Close a file using fclose
    • Move the file position indicator using fseek
*/
int main()
{
    // file handling
    FILE *fptr;
    fptr = fopen("test.txt", "w");
    if(fptr == NULL)
    {
        perror("Error!");
        return 1;
    }
    char exercise[50];
    int reps, num;


    printf("Enter the number of the exercises: \n");
    scanf("%d", &num);

    for(int i = 0; i < num; i++)
    {
        printf("Enter the name of the exercise: \n");
        scanf("%s", exercise);

        printf("Enter the number of reps: \n");
        scanf("%d", &reps);

        fprintf(fptr, "Exercise: %s Reps: %d\n", exercise, reps);
        
    }

    fclose(fptr);
    
    return 0;
}