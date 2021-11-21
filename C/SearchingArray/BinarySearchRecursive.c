

int  binary_search_recursive(int array[], int leftmost_index, int rightmost_index, int k)
{
    int mid_index = (leftmost_index+rightmost_index)/2;
    int current_element = array[mid_index];
    if ( leftmost_index>rightmost_index) return -1;
    else if(current_element==k)
    {
        return mid_index;
        
    }
    else if (array[leftmost_index]==k) return leftmost_index;
    else if (array[rightmost_index]==k) return rightmost_index;
    else if ( current_element >k)
    {

        return binary_search_recursive(array,leftmost_index+1, mid_index-1,k);
    }
    else if (current_element < k)
    {

        return binary_search_recursive(array, mid_index+1,rightmost_index-1,k);
    }
    
}