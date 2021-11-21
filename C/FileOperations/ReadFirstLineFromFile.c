#include   <stdio.h>

int main()
{
    char line[30];
    FILE * fptr;
    fptr = fopen("test.txt", "r");
    //fgets(line, 30, fptr);
    fscanf(fptr, "%[^\n]", line);
    printf("First line of the file :\n%s", line);
    fclose(fptr);


    return 0;
}