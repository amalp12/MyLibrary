#include <stdio.h>
#include <stdlib.h>
#define INT_MAX  2147483647



// Max Heap Sort Start
void swap(int * a, int * b)
{
    int  temp  = *a;
    *a = *b;
    *b = temp;
}
void min_heapify( int * arr, int length , int current_root)
{
    int smallest ;
    int left = 2*current_root+1, right = 2*current_root+2;

    if(left< length &&  arr[left] <arr[current_root] ) smallest = left;
    else smallest = current_root;

    if(right< length &&  arr[right] <arr[smallest] ) smallest = right;
  
    if(current_root != smallest)
    {
        swap(&arr[current_root], &arr[smallest]);
        min_heapify(arr, length, smallest);
    } 

}
void heapsort(int * arr, int length)
{
    for(int i =length/2-1;i>=0;i--) min_heapify(arr, length,i);

    for(int i =length-1;i>=1;i--)
    {
        swap(&arr[i],&arr[0]); 
        min_heapify(arr, i,0);
    }

}

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
    printf("\n");
    
}
void delete_from_heap(int * arr,int n)
{   if(n<=0) return;
    swap(&arr[n-1],&arr[0]); 
    min_heapify(arr, n-1 ,0);
}
void insert_patient(int * arr, int value, int * len )
{
    
    arr[*len] = value;
    int i = *len, parent;
    (*len)++;
    while(i>0)
    {
        parent = i/2;
        if (arr[parent] > arr[i])
        {
            swap(&arr[parent], &arr[i]); i = parent;
        }
        else return;
        
    }
}

void extract_next_patient(int *q, int * len)
{
    if(*len==0)
    {
        printf("-1\n"); return;
    }
    printf("%d\n", q[0]);
    delete_from_heap(q,*len);
    (*len)--;
    
}
void get_next_patient(int *q, int n)
{
    if(n==0)
    {
        printf("-1\n"); return;
    }
    printf("%d\n", q[0]);
}
void change_token_number(int *q, int k,int x, int n)
{
    for(int i = 0 ; i<n ; i++)
    {
        if(q[i]==k)
        {
            q[i] = x;
            min_heapify(q,n,0);
            return;
        }
    }
}
void display_queue(int *q, int n)
{
    int temp[n];
    for(int i = 0; i<n; i++) temp[i] = q[i];
    heapsort(temp, n);
    for(int i = n-1; i>=0 ;i--)
    {
        printf("%d ", temp[i]);
    }
    printf("\n");
}
int main() 
{   
    int UPPERBOUND = 2000;
    int s=1, length = 0, k,x;
    char in;
    int * Q = (int *) malloc(sizeof(int )*UPPERBOUND);
    while(s)
    {
        
        scanf("%c", &in);
        switch (in)
        {
            case 'i':                
                
                scanf("%d", &k);
                insert_patient(Q, k, &length );
                //print_array_elements(Q,length);
                
                
                break;
            case 'e':
                extract_next_patient(Q,&length);
                
                break;
            case 'm':
                get_next_patient(Q, length);                
                break;
            case 'c':
                scanf("%d", &k);scanf("%d", &x);
                change_token_number(Q,k,x,length);
                break;
            case 'd':
                display_queue(Q,length);
                break;
            case 's':
                s=0;
                return 0;
                break;
            default:
                break;
        }
    }
    
	return 0;
}

