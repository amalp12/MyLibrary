#include <stdio.h>
#include <stdlib.h>

int * take_in_adj_matrix( int n)
{
    int * matrix = (int * ) malloc( n * sizeof(int[n]));
    for(int i = 0; i<n;i++)
    {
        for(int j = 0; j<n; j++)
        {
            scanf("%d",(matrix + i*n + j*sizeof(int)));
        }
    }
    return matrix;
}



void print_adj_matrix( int * matrix,int n)
{
    for(int i = 0; i<n;i++)
    {
        for(int j = 0; j<n; j++)
        {
            printf("%d", *(matrix + i*n + j*sizeof(int)));
        }
        printf("\n");
    }
    
}

void print_adj_list( int * matrix,int n)
{
    for(int i = 0; i<n;i++)
    {
         
        printf("%d ", i);
        for(int j = 0; j<n; j++)
        {
           if(*(matrix + i*n + j*sizeof(int)) )printf("%d ",j );
        }
        printf("\n");
    }
    
}
int main()
{

    // take in n
    int n ;
    scanf("%d", &n);

    int * adj_matrix = take_in_adj_matrix(n);
    print_adj_list(adj_matrix,n);
    



    return 0;
}
