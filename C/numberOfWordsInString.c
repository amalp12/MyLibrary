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
