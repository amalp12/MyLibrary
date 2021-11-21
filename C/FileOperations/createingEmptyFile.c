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
    FILE *fptr;
    fptr = fopen("test.txt", "w");
    if(fptr == NULL)
    {
        perror("Error!");
        return 1;
    }

    fclose(fptr);
    
    return 0;
}