#include <stdio.h>
#include <stdlib.h>
#define INT_MAX  2147483647
#define pnl printf("\n")
#define debug printf("DEBUG\n")

void print_array_elements(int  arr[], int arr_size)
{
    //printf("Elements in the array are : ");
    //printf("\n");
    for(int i =0 ; i<arr_size; i++)
    {
        printf("%d ", arr[i]);
        
    }
    printf("\n");
}

// Max Heap Sort Start
void swap(int * a, int *b)
{
    int  temp  = *a;
    *a = *b;
    *b = temp;
}
void max_heapify( int * arr, int length , int current_root, int * count)
{
    int largest ;
    int left = 2*current_root+1, right = 2*current_root+2;

    if(left< length &&  arr[left]>arr[current_root] ) largest = left, (*count)+=1;
    else 
    { 
        largest = current_root;
        if (left< length )(*count)+=1;
    }
    if(right< length &&  arr[right]>arr[largest] ) largest = right, (*count)+=1;
    else 
    { 
        
        if (right< length )(*count)+=1;
    }
    if(current_root != largest)
    {
        swap(&arr[current_root], &arr[largest]);
        max_heapify(arr, length, largest, count);
    } 

}
void buildheap(int * arr, int length, int * count)
{
    for(int i =(length/2)-1;i>=0;i--) max_heapify(arr, length,i, count );

    
}
// Max Heap Sort End

void insert_to_heap(int  * arr,int n,  int  value )
{
    arr[n] = value;
    int i = n, parent ;
    while(i>0)
    {
        parent =i/2;
        if (arr[parent] <= arr[i])
        {
            swap(&arr[parent], &arr[i]); i = parent;
        }
        else return;
    }
}

// funtion to get input int to a malloc array using scanf
int * get_integers_in_array( int arr_size )
{
    int *arr = (int*)malloc(sizeof(int)*arr_size);
    for(int i =0 ; i<arr_size; i++)
    {
        int temp;
        scanf("%d", &temp);
        insert_to_heap(arr,i,temp);
        
    }
    return arr;
}



int main() 
{
    int n , m, max =0, count = 0;
	scanf("%d", &n); scanf("%d", &m);
	int * array = get_integers_in_array(n);
    //print_array_elements(array,n);
    //for(int i = 0 ; i<n ; i++)max_heapify(array, n,i );
    buildheap(array,n, &count);
    //print_array_elements(array,n); 
    //print_array_elements(array,n);
    for(int i = 0 ; i <m ; i++ )
    {
        int temp = array[0];
        max += temp;
        print_array_elements(array,n);
    
        if(temp%2==0) array[0] = temp/2;
        else array[0]= (temp-1)/2;
        buildheap(array,n, &count);
        
    }

    printf("%d\n", max);
    return 0;
}
