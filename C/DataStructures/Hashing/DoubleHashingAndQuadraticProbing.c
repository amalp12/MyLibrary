#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
#define INT_MIN  -2147483647
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
void print_hashtable_elements(int  arr[], int arr_size)
{
    
    for(int i =0 ; i<arr_size; i++)
    {
        if(arr[i]==INT_MIN)
        {
            printf("%d ()\n", i);
        }
        else
        {
            printf("%d (%d)\n", i, arr[i]);
        }
       
        
    }
    
}

void set_array_elements(int  arr[], int arr_size, int val)
{
    for(int i =0 ; i<arr_size; i++) arr[i] = val;            
}

int * createHashTable(int m)
{
    int * hashTable = (int*)malloc(sizeof(int)*m);
    // Setting all the elements of the hash table to  a sentinal value
    set_array_elements(hashTable, m, INT_MIN);

    return hashTable; // araay of size m with all elements set to INT_MIN
}

int mappingFunctionA( int m, int c1, int c2, int key, int i)
{
    int h1 = (key%m) , h2 = c1*i + c2*i*i;
    return (  h1 +h2 ) %m;

}

int mappingFunctionB( int m, int r, int key, int i)
{
    int h1 = (key%m) , h2 = r-(key%r);
    return (  h1 + i * h2 ) %m;

}

void insertIntoHashTableA(int * hashTable, int m, int c1, int c2,  int key)
{
  
    int current_index =mappingFunctionA(m, c1, c2, key, 0);

    for(int i=1 ; i<m ; i++ )
    {
        if(hashTable[current_index] == INT_MIN)
        {
            hashTable[current_index] = key;
            //printf("Inserted %d at index %d\n", key, current_index);
            return;
        }
        else
        {
            current_index = mappingFunctionA(m, c1, c2, key, i);
        }
    }
    //printf("Could not insert %d\n", key);
    
}
void insertIntoHashTableB(int * hashTable, int m, int r, int key)
{
  
    int current_index =  mappingFunctionB(m, r, key, 0);

    for(int i=1 ; i<m ; i++ )
    {
        if(hashTable[current_index] == INT_MIN)
        {
            hashTable[current_index] = key;
            //printf("Inserted %d at index %d\n", key, current_index);
            return;
        }
        else
        {
            current_index = mappingFunctionB(m, r, key, i);
        }
    }
    //printf("Could not insert %d\n", key);
    
}

int searchIndexA(int * hashTable, int m, int c1, int c2, int key)
{
  
    int current_index = mappingFunctionA(m, c1, c2,  key , 0);

    for(int i=1 ; i<m ; i++ )
    {
        if(hashTable[current_index] == key)
        {
            //printf("Found %d at index %d\n", key, current_index);
            return current_index;
        }
        else
        {
            current_index = mappingFunctionA(m, c1, c2,  key , i);
        }
    }
    //printf("EOA! Could not find %d\n", key);
    return -1;
    
}

int searchIndexB(int * hashTable, int m, int r, int key)
{
  
    int current_index = mappingFunctionB(m, r,  key ,0);

    for(int i=1 ; i<m ; i++ )
    {
        if(hashTable[current_index] == key)
        {
            //printf("Found %d at index %d\n", key, current_index);
            return current_index;
        }
        else
        {
            current_index = mappingFunctionB(m, r,  key , i);
        }
    }
    //printf("EOA! Could not find %d\n", key);
    return -1;
    
}


void deleteA(int * hashTable, int m, int c1, int c2, int key)
{
    int index = searchIndexA(hashTable, m, c1, c2, key);
    if(index != -1)
    {
        hashTable[index] = INT_MIN;
        //printf("Deleted %d at index %d\n", key, index);
    }
}

void deleteB(int * hashTable, int m, int r, int key)
{
    int index = searchIndexB(hashTable, m, r, key);
    if(index != -1)
    {
        hashTable[index] = INT_MIN;
        //printf("Deleted %d at index %d\n", key, index);
    }
}


int isPrime(int num )
{
    // if the number is less than 2 return false
    if(num<2) return 0;
    // 2 is the only even prime number
    if(num==2) return 1;
    // all other even numbers are not prime
    if(num%2==0) return 0;
    // now we know that num is odd and greater than 2 so we need to check only till sqrt(num)
    for(int i = 3; i<=sqrt(num); i+=2) if(num%i==0) return 0;
    return 1;
}

int largestPrime(int num )
{
    int curr = num-1;
    while(!isPrime(curr) && curr>0) curr--;
    return curr;
}

int main() 
{

    char in, mode; int m, val, condition = 1, c1, c2, r;
	
    scanf("%c", &mode);//{ ‘a’, ‘b’ }:
    scanf("%d", &m);
    scanf("%c", &in);

    if(mode=='a')
    {
        scanf("%d", &c1);scanf("%d", &c2);
    }
    else if (mode=='b')
    {
        r = largestPrime(m);
        //printf("r : %d\n", r);
    }
 
    int* hashTable = createHashTable(m);

    while (condition)
    {
        scanf("%c", &in); //{ ‘i’, ‘s’, ‘d’, ‘p’, ‘t’ }
        switch (in)
        {
            case 'i':
                scanf("%d", &val);
                if(mode=='a')
                {
                    insertIntoHashTableA(hashTable, m, c1, c2, val);
                }
                else if (mode=='b')
                {
                    insertIntoHashTableB(hashTable, m, r, val);
                }
                
                break;
            case 's':
                scanf("%d", &val);
                if (mode=='a')
                {
                    val = searchIndexA(hashTable, m, c1, c2, val);
                }
                else if (mode=='b')
                {
                    val = searchIndexB(hashTable, m, r, val);
                }
                
                if (val == -1)
                {
                    printf("-1\n");
                }
                else
                {
                    printf("1\n");
                }
                break;
            case 'd':
                scanf("%d", &val);
                if(mode=='a')
                {
                    deleteA(hashTable, m, c1, c2, val);
                }
                else if (mode=='b')
                {
                    deleteB(hashTable, m, r, val);
                }
                
                break;
            case 'p':
                print_hashtable_elements(hashTable, m);
                break;
            case 't':
                condition = 0;
                //return 0;
                break;
            default:
                break;
        }
    }
    

	return 0;
}
