#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
typedef long int li;
typedef struct queue_linked_node * queue_linked_node_ptr;

struct queue_linked_node
{
    int key ;
    queue_linked_node_ptr next;
};

int queue_linked_isEmpty(queue_linked_node_ptr * list)
{
    return ((*list)==NULL);
}
queue_linked_node_ptr queue_linked_create_node(int key)
{
    queue_linked_node_ptr new_node = (queue_linked_node_ptr)malloc(sizeof(struct queue_linked_node));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}
queue_linked_node_ptr queue_linked_list_search(queue_linked_node_ptr * list, int k)
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
        int temp = x->key;
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
        printf("%d\n", ptr->next->key);
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
                printf("%d\n", ptr->next->key);
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
    printf("%d\n", (*list)->key);
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
        printf("%d\n", ptr->key);
        *list = NULL;
        return;
    }
    while(ptr->next->next != NULL)
    {
        ptr=ptr->next;
    }
    printf("%d\n", ptr->next->key);
    ptr->next = NULL;
}
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
}

void queue_linked_QueueEmpty(queue_linked_node_ptr *list)
{
    int bool =  queue_linked_isEmpty(list);
    if (bool) bool = -1;
    else bool = 1;
    printf("%d\n", bool);
}
void queue_linked_Enqueue(queue_linked_node_ptr* list, queue_linked_node_ptr x)
{
    queue_linked_list_insert_tail( list, x);
}

void queue_linked_Dequeue(queue_linked_node_ptr * list)
{
    queue_linked_list_delete_first(list);
}
int main() 
{
    char in; int k ,x_key , y_key, bool;
    queue_linked_node_ptr head = NULL,x,y; // initalizing head to null
    while(1)
    {
        scanf(" %c", &in);
        
        switch (in)
        {
            case 'i':

                scanf(" %d", &k);
                queue_linked_node_ptr x = queue_linked_create_node(k);
                queue_linked_Enqueue(&head,x);
                break;
            
            case 'd':
                queue_linked_Dequeue(&head);
                break;

            case 'e':
                queue_linked_QueueEmpty(&head);
                
                break;
           
            case 't':
                return 0;
                break;
            default:
                break;
        }
    }
	return 0;
}
