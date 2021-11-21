#include<stdlib.h>
#include<stdio.h>

int main(){
    char name[50],c; int marks, i, num=2;
    FILE *fp_read, *fp_write;
    fp_write = fopen("student4.txt", "w");
    fp_read = fopen("student3.txt", "r");
    if(fp_write == NULL || fp_read == NULL)
    {
        perror("Error in opening!");
        return 1;
    }
    fscanf(fp_read,"%d", &num);
    
    for(i = 0; i < num; ++i)
    {
        fscanf(fp_read, "%s", name);
        fscanf(fp_read, "%d", &marks);
        fprintf(fp_write,"Name: %s \t", name);
        fprintf(fp_write,"Marks = %d\n",marks);
    }
    fclose(fp_write);
    fclose(fp_read);
}