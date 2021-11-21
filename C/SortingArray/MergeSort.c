
void merge(int array[], int left, int mid , int right)
{
    int template_array[right-left+1];
    int k = 0,i = left, j =mid+1;
    for(; i<=mid && j<=right; )
    {
  
        if(array[i]<array[j])
        {
            template_array[k] = array[i];
            i++,k++;
        }
        else
        {
            template_array[k] = array[j];
            j++,k++;
            
        }
    }
    
   while(i<=mid)
   {
        template_array[k] = array[i];
        i++,k++;
       
   }
   while(j<=right)
   {
        template_array[k] = array[j];
        j++,k++;
            
   }
   for(i = left, j=0; j<right-left+1;i++,j++)
   {
       array[i] =template_array[j];
   }
}

void  mergeSort(int arr[], int leftmost, int rightmost )
{
    int length = rightmost+leftmost+1, middle;
    if( leftmost < rightmost)
    {
        
        middle = (length-1)/2;
        mergeSort(arr,leftmost,middle);
        mergeSort(arr, middle+1, rightmost);
        merge(arr, leftmost, middle, rightmost);
        
    }
}