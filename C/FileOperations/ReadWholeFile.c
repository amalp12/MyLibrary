#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *fptr;
    fptr = fopen("test.txt", "r");
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    char c;
    c = fgetc(fptr);
    while(c != EOF)
    {
        printf("%c", c);
        c = fgetc(fptr);
    }

    return 0;
}