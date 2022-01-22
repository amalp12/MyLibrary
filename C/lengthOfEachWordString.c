
int get_number_of_words(char *str, char delimiter)
{
    int count = 0;
    int i = 0;
    while(str[i]!='\0')
    {
        if(str[i]==delimiter) count++;
        i++;
    }
    return count+1;
}
int * get_word_lengths(char * str, int num_of_words)
{
    int * arr = (int*)malloc(sizeof(int)*num_of_words);
    int i = 0;
    int letters = 0;
    int arr_index = 0;
    while(str[i]!='\0')
    {
        
        if(str[i]==' ')
        {
            arr[arr_index] =  letters;
            letters = 0;
            arr_index++;        
        }
        else
        {
            letters++;
        }
        i++;
        
    }
    arr[arr_index] = letters;
    return arr;
}
