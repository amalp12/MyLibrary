


int get_string_length(char * s)
{
    int length =0;
    char * ptr = s;
    while(*ptr != '\0')
    {
        length++;
        ptr++;
    }
    return length;
}