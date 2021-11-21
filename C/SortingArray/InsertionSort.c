void swap(int * a, int *b)
{
    int  temp  = *a;
    *a = *b;
    *b = temp;
}
void insertionSort(int arr[], int n)
{
    for(int i = 1 ; i<n; i++)
    {
        int   temp = arr[i]; // now arr[i] is a hole
        // To sort in inreasing order
        int j =  i-1;
        while(temp<arr[j] && j>=0)
        {
            swap(&arr[j+1],&arr[j]);
            j--;
            
        }
        j++;
        swap(&temp,&arr[j]);
        
    }
}
