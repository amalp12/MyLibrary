#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
#define node_container_ptr struct node_container *
#define node_ptr struct node *
//Queue using linked list start
#define queue_linked_node_ptr struct queue_linked_node * 


struct queue_linked_node
{
    node_ptr key ;
    queue_linked_node_ptr next;
};

int queue_linked_isEmpty(queue_linked_node_ptr * list)
{
    return ((*list)==NULL);
}
queue_linked_node_ptr queue_linked_create_node(node_ptr key)
{
    queue_linked_node_ptr new_node = (queue_linked_node_ptr)malloc(sizeof(struct queue_linked_node));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}
queue_linked_node_ptr queue_linked_list_search(queue_linked_node_ptr * list, node_ptr k)
{
    queue_linked_node_ptr ptr = *list;
    while(ptr!=NULL)
    {
        if(ptr->key==k) return ptr;
        ptr = ptr->next;
    }
    return ptr;
}
void queue_linked_list_insert_front(queue_linked_node_ptr* list, queue_linked_node_ptr x)
{
    if(queue_linked_isEmpty(list))
    {
        *list = x;
    }
    else
    {
        x->next = *list;
        *list = x;
    }
}
void queue_linked_list_insert_tail(queue_linked_node_ptr* list, queue_linked_node_ptr x)
{
    
    if(queue_linked_isEmpty(list))
    {
        *list = x; return;
    }
    queue_linked_node_ptr ptr = *list;
    while(ptr->next!=NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = x;
}
void queue_linked_list_insert_after(queue_linked_node_ptr* list,queue_linked_node_ptr x,queue_linked_node_ptr y)
{
    queue_linked_node_ptr y_adress = queue_linked_list_search(list, y->key);
    if(y_adress!=NULL)
    {
        x->next = y_adress->next;// setting new node's next
        y_adress->next = x; // setting y node's next 

    } 
}

void queue_linked_list_insert_before(queue_linked_node_ptr* list,queue_linked_node_ptr x,queue_linked_node_ptr y)
{
    queue_linked_node_ptr y_adress = queue_linked_list_search(list, y->key);
    if(y_adress!=NULL)
    {
        x->next = y_adress->next;// setting new node's next
        y_adress->next = x; // setting y node's next
        node_ptr temp = x->key;
        x->key = y_adress->key;
        y_adress->key = temp; 

    } 
}
void queue_linked_list_delete(queue_linked_node_ptr* list,queue_linked_node_ptr x)
{
    if(queue_linked_isEmpty(list))
    {
        printf("-1\n");
        return;
    }
    queue_linked_node_ptr ptr = *list;
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
void queue_linked_list_delete_first(queue_linked_node_ptr * list)
{
    if(queue_linked_isEmpty(list))
    {
        printf("-1\n");
        return;
    }
    //printf("%d\n", (*list)->key);
    (*list)= (*list)->next;
}
void queue_linked_list_delete_last(queue_linked_node_ptr * list)
{
    if(queue_linked_isEmpty(list))
    {
        printf("-1\n");
        return;
    }
    queue_linked_node_ptr ptr = *list;
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
/*
void queue_linked_print_list(queue_linked_node_ptr *list)
{
    if(queue_linked_isEmpty(list))
    {
        printf("NULL\n");
        return;
    }
    queue_linked_node_ptr ptr = *list;
    while(ptr!=NULL)
    {
        printf("%d ", ptr->key);
        ptr=ptr->next;
    }
    printf("\n");
}*/

void queue_linked_QueueEmpty(queue_linked_node_ptr *list)
{
    int boo =  queue_linked_isEmpty(list);
    if (boo) boo = -1;
    else boo = 1;
    printf("%d\n", boo);
}
void queue_linked_Enqueue(queue_linked_node_ptr * list, queue_linked_node_ptr x)
{
    queue_linked_list_insert_tail( list, x);
}

queue_linked_node_ptr queue_linked_Dequeue(queue_linked_node_ptr * list)
{
    if(queue_linked_isEmpty(list))
    {
        printf("-1\n");
        return NULL;
    }
    //printf("%d\n", (*list)->key);
    queue_linked_node_ptr ptr = *list;
    (*list)= (*list)->next;
    return ptr;
}
//Queue using linked list end
struct  node
{
    int key;
    int satellite_data;
    node_ptr parent;
    node_ptr left;
    node_ptr right ;
};
struct node_container
{
    node_ptr node;
    int level;
};

node_ptr create_node(int key)
{
    node_ptr new_node = (node_ptr)malloc(sizeof(struct node));
    new_node->key = key;
    new_node->satellite_data = 0;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node; 
}
void insert(node_ptr * root, int key)
{
    // creating a new node
    node_ptr new_node = create_node(key);
   
    // if the tree is empty
    if  (*root==NULL)
    {
        *root = new_node;
        return;
    }

    // if the tree is not empty
    // creating a queue
    queue_linked_node_ptr queue = NULL;
    int condtition = 1;
    
    queue_linked_Enqueue(&queue, queue_linked_create_node(*root));
    queue_linked_node_ptr current = NULL;
    while(condtition)
    {
        
        current = queue_linked_Dequeue(&queue);
        if(current->key ==NULL) break;
        if(current->key->left == NULL)
        {
            current->key->left = new_node;
            new_node->parent = current->key;
            condtition = 0;
        }
        else if(current->key->right == NULL)
        {
            current->key->right = new_node;
            new_node->parent = current->key;
            condtition = 0;
        }
        else
        {
            queue_linked_Enqueue(&queue, queue_linked_create_node(current->key->left));
            queue_linked_Enqueue(&queue, queue_linked_create_node(current->key->right));
        }

    }

}
void parenthesisNotation(node_ptr root)
{
    if(root==NULL)
    {
        printf("( )");
        return;
    }


    printf("( ");
    printf("%d ", root->key);
    int flag = 0;
    if(root->left!=NULL)
    {
        parenthesisNotation(root->left);
    }
    else
    {
        printf("( ) ");
        flag=1;
    }
    if(root->right!=NULL)
    {
        parenthesisNotation(root->right);
    }
    else
    {
        printf("( ) ");
    }
    printf(") ");
    
}
int main()
{
    node_ptr root = NULL;
    int k;
    char in;

    while(1)
    {
        scanf(" %c", &in);
        
        switch (in)
        {
            case 'i':

                scanf(" %d", &k);
                insert(&root, k);
                break;
            
            case 'p':
                parenthesisNotation(root);
                printf("\n");
                break;


            case 'e':
                return 0;
                break;
            default:
                break;
        }
    }
	return 0;
}
