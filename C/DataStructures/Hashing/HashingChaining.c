#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
#define INT_MIN  -2147483647
// Doubly Linked List Start

typedef struct DoublyLLnode * DoublyLL_node_ptr;

struct DoublyLLnode
{
    char * key ;
    DoublyLL_node_ptr next;
    DoublyLL_node_ptr previous;
};

int DoublyLL_isEmpty(DoublyLL_node_ptr * list)
{
    return ((*list)==NULL);
}
DoublyLL_node_ptr DoublyLL_create_node(char * key)
{
    DoublyLL_node_ptr new_node = (DoublyLL_node_ptr)malloc(sizeof(struct DoublyLLnode));
    new_node->key = key;
    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node;
}
DoublyLL_node_ptr DoublyLL_list_search(DoublyLL_node_ptr * list, char * k)
{
    DoublyLL_node_ptr ptr = *list;
    while(ptr!=NULL)
    {
        if(ptr->key==k) return ptr;
        ptr = ptr->next;
    }
    return ptr;
}
void DoublyLL_list_insert_front(DoublyLL_node_ptr* list, DoublyLL_node_ptr x)
{
    if(DoublyLL_isEmpty(list))
    {
        *list = x;
    }
    else
    {
        x->next = *list;
        (*list) -> previous = x;
        *list = x;
    }
}
void DoublyLL_list_insert_tail(DoublyLL_node_ptr* list, DoublyLL_node_ptr x)
{
    
    if(DoublyLL_isEmpty(list))
    {
        *list = x; return;
    }
    DoublyLL_node_ptr ptr = *list;
    while(ptr->next!=NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = x;
    x->previous = ptr;
}
void DoublyLL_list_insert_after(DoublyLL_node_ptr* list,DoublyLL_node_ptr x,DoublyLL_node_ptr y)
{
    DoublyLL_node_ptr y_address = DoublyLL_list_search(list, y->key);
    if(y_address!=NULL)
    {
        x->next = y_address->next;// setting new node's next
        if(y_address->next!=NULL)y_address->next->previous = x;
        y_address->next = x; // setting y node's next 
        x->previous = y_address; // setting y node's previous
    } 
}

void DoublyLL_list_insert_before(DoublyLL_node_ptr* list,DoublyLL_node_ptr x,DoublyLL_node_ptr y)
{
    DoublyLL_node_ptr y_address = DoublyLL_list_search(list, y->key);
    if(y_address!=NULL)
    {
        x->previous = y_address->previous;
        if(y_address->previous!=NULL)y_address->previous->next = x;
        y_address->previous = x;
        x->next= y_address;
        if (y_address==*list)//it y was head set new head
        {
            (*list) = x;
        }
        

    } 
}
void DoublyLL_list_delete(DoublyLL_node_ptr* list,DoublyLL_node_ptr x)
{
    if(x==NULL) return;
    if(DoublyLL_isEmpty(list))
    {
        printf("Not Found\n");
        return;
    }
    DoublyLL_node_ptr ptr = *list;
    // checking if last element 
    if(ptr->next== NULL)
    {
        if(ptr->key ==x->key)
        {
            *list = NULL;
            printf("NULL\n");
            return;
        }
    }
    //checking for first element
    if(ptr->key==x->key)
    {
        *list = ptr->next;
        (*list) ->previous = NULL;
        //printf("%d\n", ptr->next->key);
        return;
    }
    //checking for the rest of the elements
    while( ptr->next !=NULL)
    {
        if(ptr->next->key == x->key )
        {
            if(ptr->next->next==NULL)printf("NULL\n");        
            //else printf("%d ", ptr->next->key);
            if(ptr->next->next!=NULL) 
            {
                ptr->next->next->previous = ptr;
                ptr->next = ptr->next->next;
            }
            else ptr->next = NULL;
            return;
        }

        ptr=ptr->next;
    }
    //printf("Not Found\n");
}
void DoublyLL_list_delete_initial(DoublyLL_node_ptr * list)
{
    if(DoublyLL_isEmpty(list))
    {
        printf("Not Found\n");
        return;
    }
    //printf("%d\n", (*list)->key);
    (*list)= (*list)->next;
    if((*list)!=NULL) (*list)->previous = NULL;
}
void DoublyLL_list_delete_last(DoublyLL_node_ptr * list)
{
    if(DoublyLL_isEmpty(list))
    {
        //printf("Not Found\n");
        return;
    }
    DoublyLL_node_ptr ptr = *list;
    if(ptr->next==NULL)
    {
        //printf("%d\n", ptr->key);
        *list = NULL;
        return;
    }
    while(ptr->next->next != NULL)
    {
        ptr=ptr->next;
    }
    //printf("%d\n", ptr->next->key);
    ptr->next = NULL;
}
void DoublyLL_print_reverse(DoublyLL_node_ptr * list, char * k )
{
    DoublyLL_node_ptr k_address = DoublyLL_list_search(list, k);
    if(k_address==NULL)
    {
        //printf("Not Found\n");
        return;
    }
    while(k_address!=NULL)
    {
        //printf("%d ", k_address->key);
        k_address = k_address->previous;
    }
    printf("\n");
}
void DoublyLL_print_list(DoublyLL_node_ptr *list)
{
    DoublyLL_node_ptr ptr = *list;
    while(ptr!=NULL)
    {
        //printf("%d ", ptr->key);
        ptr=ptr->next;
    }
    printf("\n");
}



// Doubly Linked List End



















// funtion to get input int to an array using scanf
void get_array_elements(int  arr[], int arr_size )
{
    for(int i =0 ; i<arr_size; i++)
    {
        scanf("%d", &arr[i]);
        
    }
    
}

// funtion to get input int to a malloc array using scanf
int * get_integers_in_array( int arr_size )
{
    int *arr = (int*)malloc(sizeof(int)*arr_size);
    for(int i =0 ; i<arr_size; i++)
    {
        scanf("%d", &arr[i]);
        
    }
    return arr;
}
// Debugging funtion to print all the elements of the array
void print_array_elements(int  arr[], int arr_size)
{
    printf("Elements in the array are : ");
    for(int i =0 ; i<arr_size; i++)
    {
        printf("%d ", arr[i]);
        
    }
    
}


void set_array_elements(DoublyLL_node_ptr *  arr, int arr_size, DoublyLL_node_ptr val)
{
    for(int i =0 ; i<arr_size; i++) arr[i] = val;            
}

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

int get_number_of_words(char *str, char delimiter)
{
    int count = 0;
    int string_length = get_string_length(str);
    for(int i = 0; i<string_length;i++)
    {
        if(str[i]==delimiter) count++;

    }
    if(str[string_length-1]!=delimiter) count++;
    return count;
}
int * get_word_lengths(char * str, int num_of_words)
{
    int * arr = (int *) malloc( num_of_words * sizeof(int) );

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
            if(str[i]!='\n')
                letters++;
             
        }
        i++;
        if(arr_index>=num_of_words) 
        {
            printf("Error : Number of words in the string is greater than the number of words in the array\n");
        }
    }
    
    if(str[i]=='\0'&& str[i-1]!=' ' )
    {
        arr[arr_index] = letters;
    }


    return arr;
}

char ** string_split(char * str, int num_words, int * word_lengths)
{
    
    char ** words = (char**)malloc(sizeof(char*)*num_words);
    
    int temp_length , str_index = 0;
    for(int i =0; i<num_words; i++)
    {
        char *word = (char*)malloc(sizeof(char)*(word_lengths[i]+2));
        temp_length = word_lengths[i];
        for(int j =0; j<temp_length; j++)
        {
            word[j] = str[str_index];
            str_index++;
        }
        word[temp_length] = '\0';
        str_index++;
        words[i] = word;

    }
    return words;

}
int upperCase(char c)
{
    if(c>='A'&& c<='Z') return 1;
    return 0;
}
int lowerCase(char c)
{
    if(c>='a'&& c<='z') return 1;
    return 0;
}

int GetPosOfLetter(char c)
{
    if(c>='a'&& c<='z') return c-'a'+1;
    return c-'A'+1;
}

int mappingFunction( char * name,int n )
{
    int index = 0;
    int iter = 1;
    int len = get_string_length(name);
    for (int i = 0; i < len; i++)
    {
        index += GetPosOfLetter(name[i])*iter;
        iter*=3;
    }
    return index%n;


}

void insertIntoHashTable(DoublyLL_node_ptr *  hashTable,  char * value, int m)
{
  
    int index = mappingFunction(value , m);
   
   DoublyLL_list_insert_tail(&hashTable[index], DoublyLL_create_node(value));
    //printf("Could not insert %d\n", key);
    
}
int stringsEqual(char * s1, char * s2)
{
    int length1 = get_string_length(s1);
    int length2 = get_string_length(s2);
    if(length1!=length2) return 0;
    for(int i =0; i<length1; i++)
    {
        if(s1[i]!=s2[i]) return 0;
    }
    return 1;
}


void Delete(DoublyLL_node_ptr *  hashTable,  char * value, int m)
{
  
    int index = mappingFunction(value , m);
    DoublyLL_node_ptr ptr = hashTable[index];
    while(ptr!=NULL)
    {
        if(stringsEqual(ptr->key, value)==1)
        {
            if(ptr->previous==NULL)
            {
                hashTable[index] = ptr->next;
                if(ptr->next!=NULL)
                {
                    ptr->next->previous = NULL;
                }
            }
            else if(ptr->next==NULL)
            {
                ptr->previous->next = NULL;
            }
            else
            {
                ptr->previous->next = ptr->next;
                ptr->next->previous = ptr->previous;
            }
           
        }
        ptr = ptr->next;
    }
    

    //printf("Could not insert %d\n", key);
    
}
DoublyLL_node_ptr * createHashTable(int m)
{
    DoublyLL_node_ptr * hashTable = (DoublyLL_node_ptr*)malloc(sizeof(DoublyLL_node_ptr)*m);
    // Setting all the elements of the hash table to  a sentinal value
    set_array_elements(hashTable, m, NULL);



    return hashTable; // araay of size m with all elements set to INT_MIN
}

void print_hash_table( DoublyLL_node_ptr *  hashTable, int m)
{
    for(int i =0; i<m; i++)
    {
        int flag = 0;
        printf("%d:", i);
        DoublyLL_node_ptr ptr = hashTable[i];
        while(ptr!=NULL)
        {
            printf("%s", ptr->key);
            ptr=ptr->next;
            if (ptr!=NULL) printf("-");
            flag = 1;
            
        }
        if(flag==0) printf("null");
        printf("\n");
    }
}




char * removeDuplicateWords(char * str)
{
    int len =  get_string_length(str) ;
    char delimiter = ' ';
    int num_words = 0;

    int len_temp;
    char substr[100][100];
    for(int i = 0 ; i < 100; i++)
    {
        for(int j = 0 ; j < 100; j++)substr[i][j] = '\0';
    }

    int sub_string_index = 0 ,j;
    for(int i =0; i<len;)
    {
        j = 0;
        while (str[i]!=delimiter && str[i]!='\n'&& str[i]!='\0')
        {
            substr[sub_string_index][j] = str[i];

 
            j++;
            i++;
        }
        substr[i][j] = '\0';
        sub_string_index++;
        num_words++;
        i++;
        
    }
    for(int i =0; i<len;i++)
    {
        for(int j =i+1; j<num_words; j++)
        {

            if(substr[i][0]!='\0' && substr[j][0]!='\0')
            {
                //printf("%s %s\n", words[i], words[j]);
                if(stringsEqual(substr[i], substr[j])==1)
                {

                    
                    
                    substr[j][0] = '\0';
                    
  
                }
                

            }

            
        }
        
    }
    char * new_str = (char*)malloc(sizeof(char)*(len+1));
    int new_str_index = 0;
    for(int i =0; i<100; i++)
    {
        if(substr[i][0]!='\0')
        {
            int sub_str_len = get_string_length(substr[i]);
            for(j=0;j<sub_str_len;j++)
            {
                new_str[new_str_index] = substr[i][j];
                new_str_index++;
            }
            new_str[new_str_index] = ' ';
            new_str_index++;
        }
    }
    new_str[new_str_index-1] = '\0';
    return new_str;
    


}

int checkOneOne(DoublyLL_node_ptr *  hashTable,   int m)
{
    for (int index = 0 ; index<m; index++)
    {
        DoublyLL_node_ptr ptr = hashTable[index];
        if(ptr!=NULL)
        {
            if(ptr->next!=NULL)
            {
                return -1;
            }
        }
    }
    return 1;

    
}
int main() 
{

    int n;
    scanf("%d\n", &n);
    char in ;
    int oneone;
    DoublyLL_node_ptr * hashTable = createHashTable(n);

    while(scanf("%c", &in) >0)
    {
        if(in == 'i')
        {
            
            char * name = (char*)malloc(sizeof(char)*100);
            scanf("%s", name);
            insertIntoHashTable(hashTable,  name, n);
            //print_hash_table(hashTable, n);
            
        }
        else if(in == 'p')
        {
            
            oneone = checkOneOne(hashTable,  n);
            printf("%d\n", oneone);
            // print_hash_table(hashTable, n);
        }
        else if(in == 'd')
        {
            char * name = (char*)malloc(sizeof(char)*100);
            scanf("%s", name);
            Delete(hashTable, name,n);
            // print_hash_table(hashTable, n);
        }
        else if(in == 't')
        {
            return 0;
        }
        
    }



    return 0;
}
