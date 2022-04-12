#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647

// funtion to get input int to an array using scanf
void get_array_elements(int  arr[], int arr_size )
{
    for(int i =0 ; i<arr_size; i++)
    {
        scanf("%d", &arr[i]);
        
    }
    
}

// funtion to get input int to a malloc array using scanf
int * get_integers_in_array( int arr_size )
{
    int *arr = (int*)malloc(sizeof(int)*arr_size);
    for(int i =0 ; i<arr_size; i++)
    {
        scanf("%d", &arr[i]);
        
    }
    return arr;
}
// Debugging funtion to print all the elements of the array
void print_array_elements(int  arr[], int arr_size)
{
    printf("Elements in the array are : ");
    for(int i =0 ; i<arr_size; i++)
    {
        printf("%d ", arr[i]);
        
    }
    
}
void replace(char S[1000][100], int len, char * w1, char * w2)
{
	for(int i = 0; i <len;i++)
	{
		if(strcmp(S[i],w1)== 0)
		{
			strcpy(S[i],w2);
		}
	}

}


int main() 
{
    
    char S[1000][100] ;
    int i=0,j=0;


    char in;
	while(1)
	{
		scanf("%c",&in);
		if (in == ' ')
		{
			S[i][j] = '\0';
			i++;
			j=0;
		}
		else if(in == '\n')
		{
			i++;
			break;

		}
		else {
			S[i][j] = in;
			j++;
		}


	}
    char w1[100];
    char w2[100];
    scanf("%s", w1);
    scanf("%s", w2);

    replace(S,i,w1,w2);

    for(int k = 0; k <i;k++)
    {
    	if(k==i-1)printf("%s",S[k] );
    	else printf("%s ",S[k] );

    }
    printf("\n");



    
}

