#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647

typedef struct BST_node * BST_node_ptr;
typedef struct stack_linked_node * stack_linked_node_ptr;
// Stacl LL Code Start


struct stack_linked_node
{
    BST_node_ptr key ;
    stack_linked_node_ptr next;
};

int stack_linked_isEmpty(stack_linked_node_ptr * list)
{
    return ((*list)==NULL);
}
stack_linked_node_ptr stack_linked_create_node(BST_node_ptr key)
{
    stack_linked_node_ptr new_node = (stack_linked_node_ptr)malloc(sizeof(struct stack_linked_node));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}
stack_linked_node_ptr stack_linked_list_search(stack_linked_node_ptr * list, BST_node_ptr k)
{
    stack_linked_node_ptr ptr = *list;
    while(ptr!=NULL)
    {
        if(ptr->key==k) return ptr;
        ptr = ptr->next;
    }
    return ptr;
}
void stack_linked_list_insert_front(stack_linked_node_ptr* list, stack_linked_node_ptr x)
{
    if(stack_linked_isEmpty(list))
    {
        *list = x;
    }
    else
    {
        x->next = *list;
        *list = x;
    }
}
void stack_linked_list_insert_tail(stack_linked_node_ptr* list, stack_linked_node_ptr x)
{
    
    if(stack_linked_isEmpty(list))
    {
        *list = x; return;
    }
    stack_linked_node_ptr ptr = *list;
    while(ptr->next!=NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = x;
}
void stack_linked_list_insert_after(stack_linked_node_ptr* list,stack_linked_node_ptr x,stack_linked_node_ptr y)
{
    stack_linked_node_ptr y_adress = stack_linked_list_search(list, y->key);
    if(y_adress!=NULL)
    {
        x->next = y_adress->next;// setting new node's next
        y_adress->next = x; // setting y node's next 

    } 
}

void stack_linked_list_insert_before(stack_linked_node_ptr* list,stack_linked_node_ptr x,stack_linked_node_ptr y)
{
    stack_linked_node_ptr y_adress = stack_linked_list_search(list, y->key);
    if(y_adress!=NULL)
    {
        x->next = y_adress->next;// setting new node's next
        y_adress->next = x; // setting y node's next
        BST_node_ptr temp = x->key;
        x->key = y_adress->key;
        y_adress->key = temp; 

    } 
}
void stack_linked_list_delete(stack_linked_node_ptr* list,stack_linked_node_ptr x)
{
    if(stack_linked_isEmpty(list))
    {
        printf("-1\n");
        return;
    }
    stack_linked_node_ptr ptr = *list;
    // checking if last element 
    if(ptr->next== NULL)
    {
        if(ptr->key ==x->key)
        {
            *list = NULL;
            printf("-2\n");
            return;
        }
    }
    //checking for first element
    if(ptr->key==x->key)
    {
        *list = ptr->next;
        //printf("%d\n", ptr->next->key);
        return;
    }
    //checking for the rest of the elements
    while( ptr->next !=NULL)
    {
        if(ptr->next->key == x->key )
        {
            if (ptr->next->next!=NULL)
            {
                ptr->next = ptr->next->next;
                //printf("%d\n", ptr->next->key);
                return;
            }
            else
            {
                ptr->next = NULL;
                printf("-2\n");
                return;
            }
        }

        ptr=ptr->next;
    }
    printf("-1\n");
}
void stack_linked_list_delete_first(stack_linked_node_ptr * list)
{
    if(stack_linked_isEmpty(list))
    {
        printf("-1\n");
        return;
    }
    //printf("%d\n", (*list)->key);
    (*list)= (*list)->next;
}
void stack_linked_list_delete_last(stack_linked_node_ptr * list)
{
    if(stack_linked_isEmpty(list))
    {
        printf("-1\n");
        return;
    }
    stack_linked_node_ptr ptr = *list;
    if(ptr->next==NULL)
    {
       // printf("%d\n", ptr->key);
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
stack_linked_node_ptr stack_linked_list_last(stack_linked_node_ptr * list)
{
    if(stack_linked_isEmpty(list))
    {
        printf("-1\n");
        return NULL;
    }
    stack_linked_node_ptr ptr = *list;
    if(ptr->next==NULL)
    {
       // printf("%d\n", ptr->key);
      
        return ptr;
    }
    while(ptr->next->next != NULL)
    {
        ptr=ptr->next;
    }
   //printf("%d\n", ptr->next->key);
    return ptr->next ;
}
void stack_linked_print_list(stack_linked_node_ptr *list)
{
    if(stack_linked_isEmpty(list))
    {
        printf("NULL\n");
        return;
    }
    stack_linked_node_ptr ptr = *list;
    while(ptr!=NULL)
    {
        //printf("%d ", ptr->key);
        ptr=ptr->next;
    }
    printf("\n");
}

void stack_linked_StackEmpty(stack_linked_node_ptr *list)
{
    int bool =  stack_linked_isEmpty(list);
    if (bool) bool = -1;
    else bool = 1;
    printf("%d\n", bool);
}
void stack_linked_push(stack_linked_node_ptr* list, stack_linked_node_ptr x)
{
    stack_linked_list_insert_tail( list, x);
}

void stack_linked_pop(stack_linked_node_ptr * list)
{
    stack_linked_list_delete_last(list);
}
// Stack LL Code End


// BST Code Start




struct BST_node
{
    char * firstName ;
    char * lastName ;
    int age;
    
    BST_node_ptr left; // left child less than data
    BST_node_ptr right; // right child greater than data
    BST_node_ptr parent; // parent of node
};



BST_node_ptr BST_create_node(int key, char * firstName , char * lastName)
{
    BST_node_ptr new_node = (BST_node_ptr) malloc(sizeof(struct BST_node));
    new_node->age = key;
    new_node->right = NULL;
    new_node->left = NULL;
    new_node->parent = NULL;
    new_node->firstName = firstName;
    new_node->lastName = lastName;
    return new_node;
}

void BST_insert_node(BST_node_ptr root, BST_node_ptr new_node)
{
    // if tree is empty put the current node as root node
    if (root ==NULL)
    {
        root = new_node;
        return;
    }
    
    // if the new node is less than current node then go left
    if(new_node-> age < root->age)
    {
        //if the left child is empty then insert the new node as left child
        if(root->left == NULL)
        {
            new_node->parent = root;
            root->left = new_node;
            return;
        }
        // if the left child is not empty then recursively call the function insert tree node towards left
        else
        {
            BST_insert_node(root->left, new_node); // pass by memory
        }

    }
    // if new node is greater than the current node then go right
    else if (new_node -> age >root->age)
    {
        //if the right child is empty then insert the new node as right child
        if(root->right == NULL)
        {
            new_node->parent = root;
            root->right = new_node;
            return;
        }
        // if the right child is not empty then recursively call the function insert tree node towards right
        else
        {
            BST_insert_node(root->right, new_node); // pass by memory
        }
    }
    else// if the new node is equal to the current node then do nothing
    {
        return;
    }
}
BST_node_ptr BST_search(BST_node_ptr  root, int key)
{
    // if the root is empty then return NULL
    if(root == NULL)
    {
        return NULL;
    }
    BST_node_ptr ptr = root;
    //if key is equal to the current node then return the current node
    if(ptr->age == key)
    {
        return ptr;
    }
    // if the key is less than the current node then go left
    else if(key < ptr->age)
    {
        return BST_search(ptr->left, key);
    }
    // if the key is greater than the current node then go right
    else if (key > ptr->age)
    {
        return BST_search(ptr->right, key);
    }
    else
    {
        return NULL;
    }

}
BST_node_ptr BST_get_parent( BST_node_ptr root, BST_node_ptr child)
{
    // if the root is empty then return NULL
    if(root == NULL)
    {
        return NULL;
    }
    // if the root is equal to the child then return NULL
    if(root == child)
    {
        return NULL;
    }
    // if the left child is equal to the child then return the root
    if(root->left == child)
    {
        return root;
    }
    // if the right child is equal to the child then return the root
    else if(root->right == child)
    {
        return root;
    }
    // if the left child is not empty then recursively call the function get parent towards left
    if(child->age <root->age )
    {
        return BST_get_parent(root->left, child);
    }
    // if the right child is not empty then recursively call the function get parent towards right
    else if(child->age >root->age)
    {
        return BST_get_parent(root->right, child);
    }
    
}

BST_node_ptr BST_get_sucessor(BST_node_ptr root, int age)
{

    BST_node_ptr search_result = BST_search(root, age);
    if(search_result!=NULL)
    {
        // if right subtree not null then  sucessor will be the leftmost child of hte right subtree or right child itself
        if(search_result->right != NULL)
        {
            BST_node_ptr temp = search_result->right; ;
            while(temp->left != NULL)
            {
                temp = temp->left;
            }
            if (temp->age < search_result->age) return NULL;
            return temp;
        }
        else // if right subtree is null sucessor will be the last left child's parent while searching the current node
        {
            BST_node_ptr sucessor= root;
            BST_node_ptr temp = root;
            while(temp->age != search_result->age)
            {
                if (search_result->age > temp->age)
                {
                    temp = temp->right;
                }
                else
                {
                    sucessor = temp;
                    temp = temp->left;
                }
            }
            if (sucessor->age < search_result->age) return NULL;
            return sucessor;
            
        }
    }
    else
    {
        return NULL;
    }

}



BST_node_ptr BST_get_predecessor(BST_node_ptr root, int age)
{
  


    BST_node_ptr search_result = BST_search(root, age);
    if(search_result!=NULL)
    {
        // if left subtree not null then  sucessor will be the rightmost child of hte left subtree or left child itself
        if(search_result->left != NULL)
        {
            BST_node_ptr temp = search_result->left; 
            while(temp->right != NULL)
            {
                temp = temp->right;
            }
            if (temp->age > search_result->age) return NULL;
            return temp;
        }
        else // if left subtree is null sucessor will be the last right child's parent while searching the current node
        {
            BST_node_ptr predecessor = root;
            BST_node_ptr temp = root;
            while(temp->age != search_result->age)
            {
                if (search_result->age < temp->age)
                {
                    temp = temp->left;
                }
                else
                {
                    predecessor = temp;
                    temp = temp->right;
                }
               
            }
            if (predecessor->age > search_result->age) return NULL;
            return predecessor;
            
        }
    }
    else
    {
        return NULL;
    }

}

void BST_delete_node(BST_node_ptr * root, int key)
{
    
    // if the root is empty then return
    if(*root == NULL)
    {
        return ;
    }
    if((*root)->age == key && (*root)->left == NULL && (*root)->right == NULL)
    {
        *root = NULL;
        return;
    }
    BST_node_ptr search_result = BST_search(*root, key);
    if(search_result != NULL)
    {
        BST_node_ptr parent = BST_get_parent(*root, search_result);

        // if parent is null then that means root node is to be deleted
        if (parent==NULL)
        {
            BST_node_ptr sucessor = BST_get_sucessor(*root, key);
            if(sucessor != NULL)
            {
                int temp = sucessor->age;
                BST_delete_node(root, sucessor->age);
                search_result->age = temp;
            }
            else
            {
                BST_node_ptr predecessor = BST_get_predecessor(*root, key);        
                int temp = predecessor->age;
                BST_delete_node(root, predecessor->age);
                search_result->age = temp;
            }
        }
        // if the node to be deleted has no children aka leaf node
        else if(search_result->left == NULL && search_result->right == NULL)
        {
            
            if(parent->left == search_result)
            {
                parent->left = NULL;
            }
            else if(parent->right == search_result)
            {
                parent->right = NULL;
            }
            else
            {
                printf("error! out of bounds.");
            }
        }
        // if the node to be deleted has one child only
        else if (search_result->left == NULL || search_result->right == NULL)
        {   
            // if the node to be deleted has right child
            if(search_result->left == NULL)
            {
                // if the node to be deleted is the parent's left child
                if(parent->left == search_result)
                {
                    // set the parent's left child to the right child of the node to be deleted
                    parent->left = search_result->right;
                }
                // if the node to be deleted is the parent's right child
                else if(parent->right == search_result)
                {
                    // set the parent's right child to the right child of the node to be deleted
                    parent->right = search_result->right;
                }
                else
                {
                    printf("error! out of bounds.");
                }
            }
            // if the node to be deleted has left child
            else if(search_result->right == NULL)
            {
                // if the node to be deleted is the parent's left child
                if(parent->left == search_result)
                {
                    // set the parent's left child to the left child of the node to be deleted
                    parent->left = search_result->left;
                }
                // if the node to be deleted is the parent's right child
                else if(parent->right == search_result)
                {
                    // set the parent's right child to the left child of the node to be deleted
                    parent->right = search_result->left;
                }
                else
                {
                    printf("error! out of bounds.");
                }
            }
        }
        // if the node to be deleted has two children
        else
        {
            BST_node_ptr successor = BST_get_sucessor( *root, search_result->age );
            int temp_data = successor->age;
            BST_delete_node (root, successor->age);
            // if the node to be deleted is the parent's left child
            if(parent->left == search_result)
            {
                
                parent->left->age =temp_data;
            }
            // if the node to be deleted is the parent's right child
            else if(parent->right == search_result)
            {
        
                parent->right->age =temp_data;
            }
            else
            {
                printf("error! out of bounds.");
            }
        }
    }
    else return ;

    
}

void BST_preorder(BST_node_ptr  current_node)
{
    if(current_node == NULL)
    {
        return;
    }

    printf("%d ", current_node->age);
    BST_preorder(current_node->left);
    BST_preorder(current_node->right);
}

void BST_postorder(BST_node_ptr  current_node)
{
    if(current_node == NULL)
    {
        return;
    }

    BST_postorder((current_node->left));
    BST_postorder((current_node->right));
    printf("%d ", current_node->age);
}


void BST_inorder(BST_node_ptr current_node)
{
    if(current_node == NULL)
    {
        return;
    }

    BST_inorder((current_node->left));
    printf("%d ", current_node->age);
    BST_inorder((current_node->right));
}
void BST_insert(BST_node_ptr * root, int key, char* firstName, char *  lastname)
{
    // if the root is empty then create a new node
    if(*root == NULL)
    {
        (*root) = BST_create_node(key, firstName, lastname);
        return;
    }
    BST_node_ptr new_node = BST_create_node(key, firstName, lastname);
    BST_insert_node(*root, new_node);
}
void BST_sucessor(BST_node_ptr root, int age)
{
    BST_node_ptr sucessor = BST_get_sucessor(root, age);
    if(sucessor!=NULL)
    {
        printf("%d\n", sucessor->age);
    }
    else
    {
        printf("-1\n");
    }
}

void BST_predecessor(BST_node_ptr root, int age)
{
    BST_node_ptr predecessor = BST_get_predecessor(root, age);
    if(predecessor!=NULL)
    {
        printf("%d\n", predecessor->age);
    }
    else
    {
        printf("-1\n");
    }
}

void BST_delete(BST_node_ptr * root, int key)
{
    BST_node_ptr search_result = BST_search(*root, key);
    if (search_result!=NULL)
    {
        BST_delete_node(root, key);
        printf("%d\n", key);
    }
    else
    {
        printf("-1\n");
    }
}
// BST Code End



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
int sumOfAscii(char *str)
{
    int sum = 0;
    while(*str)
    {
        sum += *str;
        str++;
    }
    return sum;
}

int mappingFunction( char * lastName)
{
    int sumAscii = sumOfAscii(lastName);
    int h1 = ((sumAscii)%128) ;
    return h1 ;

}
void set_array_elements(BST_node_ptr *  arr, int arr_size, BST_node_ptr val)
{
    for(int i =0 ; i<arr_size; i++) arr[i] = val;            
}

BST_node_ptr * createHashTable(int m)
{
    BST_node_ptr * hashTable = (BST_node_ptr*)malloc(sizeof(BST_node_ptr)*m);
    // Setting all the elements of the hash table to  a sentinal value
    set_array_elements(hashTable, m, NULL);



    return hashTable; // araay of size m with all elements set to INT_MIN
}
void insertIntoHashTable(BST_node_ptr *  hashTable, int age,  char * firstName, char* lastName )
{
  
    int index = mappingFunction(lastName);
    BST_insert(&hashTable[index], age, firstName, lastName);
  
    //printf("Could not insert %d\n", key);
    
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
BST_node_ptr searchPerson(BST_node_ptr node, char * firstName , char * lastName)
{
    if(node == NULL)
    {
      
        return NULL;
    }
    if(stringsEqual(node->firstName, firstName) == 1 && stringsEqual(node->lastName, lastName) == 1)
    {
        // printf("%s ", node->firstName);
        // printf("%s ", node->lastName);
        // printf("%d\n", node->age);
        return node;
    }
    else
    {
        BST_node_ptr left = searchPerson(node->left, firstName, lastName);
        if(left != NULL)
        {
            return left;
        }
        BST_node_ptr right = searchPerson(node->right, firstName, lastName);
        if(right != NULL)
        {
            return right;
        }
        
    }

}
void PrintRelatives(BST_node_ptr * hashTable, char * lastName, char * firstName)
{
  
    int current_index = mappingFunction( lastName);

    BST_node_ptr search_result  = searchPerson(hashTable[current_index], firstName, lastName);
    if (search_result==NULL) {
        printf("-1\n");
    } 
    else 
    {
        stack_linked_node_ptr stack = NULL;

        BST_node_ptr current = search_result;
        while(current!=NULL)
        {
            stack_linked_node_ptr x = stack_linked_create_node(current);
            stack_linked_push(&stack,x);
            current = current->parent;
        }
        while(stack!=NULL)
        {
            stack_linked_node_ptr x = stack_linked_list_last(&stack);
            printf("%s ", x->key->firstName);
            printf("%s ", x->key->lastName);
            printf("%d\n", x->key->age);
            stack_linked_list_delete_last(&stack);
        }
    }
    
    
}
int main() 
{
    char in ;
    BST_node_ptr * hashTable = createHashTable(128);
    while(scanf("%c", &in) >0)
    {
        if(in == 'i')
        {
            char * firstName = (char*)malloc(sizeof(char)*100);
            char * lastName = (char*)malloc(sizeof(char)*100);
            int age;
            scanf("%s", firstName);
            scanf("%s", lastName);
            scanf("%d", &age);
            insertIntoHashTable(hashTable, age, firstName, lastName);
            
        }
        else if(in == 'p')
        {
            char * firstName = (char*)malloc(sizeof(char)*100);
            char * lastName = (char*)malloc(sizeof(char)*100);
            scanf("%s", firstName);
            scanf("%s", lastName);
            PrintRelatives(hashTable, lastName, firstName);
        }
        
        
    }
	return 0;
}
