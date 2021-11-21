
// Quick Sort

void swap(int * a, int *b)
{
    int  temp  = *a;
    *a = *b;
    *b = temp;
}
int get_partition_index(int * arr, int start, int end)
{
    int * pivot = &arr[end];
    int pivot_index=start,j=start;
    for(;j<end; )
    {
        if(*pivot>=arr[j])
        {
            swap(&arr[pivot_index],&arr[j]);
            pivot_index++;
        }
        j++;
    }
    swap(&arr[pivot_index], pivot);
    return pivot_index;
}

void quickSortRecursive(int *arr, int start, int end)
{
    
    if(start<end)
    {
        int pivot_index = get_partition_index(arr,start, end);
        //printf("\n%d\n", pivot_index);
        quickSortRecursive(arr,start, pivot_index-1);
        quickSortRecursive(arr,pivot_index+1, end);
    }
}
// quick sort end