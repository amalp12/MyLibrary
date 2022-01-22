int stingsEqual(char * s1, char * s2, int l1, int l2)
{
    int length1 = l1;
    int length2 = l2;
    if(length1!=length2) return 0;
    for(int i =0; i<length1; i++)
    {
        if(s1[i]!=s2[i]) return 0;
    }
    return 1;
}
char * removeDuplicateWords(char * str)
{
    int len =  get_string_length(str) ;
    char delimiter = ' ';
    int num_words = get_number_of_words(str, delimiter);
    int * word_lengths = get_word_lengths(str, num_words);
    char ** words = string_split(str, num_words, word_lengths);
    
    for(int i =0; i<num_words; i++)
    {
        for(int j =i+1; j<num_words; j++)
        {

            if(words[i]!=NULL && words[j]!=NULL)
            {
                //printf("%s %s\n", words[i], words[j]);
                if(stingsEqual(words[i], words[j], word_lengths[i], word_lengths[j])==1)
                {
                    words[j] = NULL;
                    word_lengths[j] = 0; 
                }

            }
            
        }
    }
    int new_len = 0;
    for(int i=0;i<num_words;i++) new_len+=word_lengths[i];

    char * new_str = (char*)malloc(sizeof(char)*(new_len+2));
    int new_str_index = 0;

    for(int i=0;i<num_words;i++)
    {
        if(words[i]!=NULL)
        {
            for(int j=0;j<word_lengths[i];j++)
            {
                new_str[new_str_index] = words[i][j];
                new_str_index++;
            }
            new_str[new_str_index] = ' ';
            new_str_index++;
        }
    }
    if (new_str[new_str_index-1]==' ' || new_str[new_str_index-1]=='\n'){
        new_str[new_str_index-1] = '\0';
    }
    else {
        new_str[new_str_index] = '\0';
    }
    return new_str;
    


}
