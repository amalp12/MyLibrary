
// Max Heap Sort Start
void swap(int * a, int *b)
{
    int  temp  = *a;
    *a = *b;
    *b = temp;
}
void max_heapify( int * arr, int length , int current_root)
{
    int largest = current_root;
    int left = 2*largest+1, right = 2*largest+2;

    if(left< length &&  arr[left]>arr[largest] ) largest = left;
    if(right< length &&  arr[right]>arr[largest] ) largest = right;
    if(current_root != largest)
    {
        swap(&arr[current_root], &arr[largest]);
        max_heapify(arr, length, largest);
    } 

}
void heapsort(int * arr, int length)
{
    for(int i =length/2-1;i>=0;i--) max_heapify(arr, length,i);
    for(int i =length-1;i>=0;i--)
    {
        swap(&arr[i],&arr[0]);
        max_heapify(arr, i,0);
    }

}
// Max Heap Sort End