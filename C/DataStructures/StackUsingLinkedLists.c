#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
typedef long int li;
typedef struct node * node_ptr;

struct node
{
    int key ;
    node_ptr next;
};

int isEmpty(node_ptr * list)
{
    return ((*list)==NULL);
}
node_ptr create_node(int key)
{
    node_ptr new_node = (node_ptr)malloc(sizeof(struct node));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}
node_ptr list_search(node_ptr * list, int k)
{
    node_ptr ptr = *list;
    while(ptr!=NULL)
    {
        if(ptr->key==k) return ptr;
        ptr = ptr->next;
    }
    return ptr;
}
void list_insert_front(node_ptr* list, node_ptr x)
{
    if(isEmpty(list))
    {
        *list = x;
    }
    else
    {
        x->next = *list;
        *list = x;
    }
}
void list_insert_tail(node_ptr* list, node_ptr x)
{
    
    if(isEmpty(list))
    {
        *list = x; return;
    }
    node_ptr ptr = *list;
    while(ptr->next!=NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = x;
}
void list_insert_after(node_ptr* list,node_ptr x,node_ptr y)
{
    node_ptr y_adress = list_search(list, y->key);
    if(y_adress!=NULL)
    {
        x->next = y_adress->next;// setting new node's next
        y_adress->next = x; // setting y node's next 

    } 
}

void list_insert_before(node_ptr* list,node_ptr x,node_ptr y)
{
    node_ptr y_adress = list_search(list, y->key);
    if(y_adress!=NULL)
    {
        x->next = y_adress->next;// setting new node's next
        y_adress->next = x; // setting y node's next
        int temp = x->key;
        x->key = y_adress->key;
        y_adress->key = temp; 

    } 
}
void list_delete(node_ptr* list,node_ptr x)
{
    if(isEmpty(list))
    {
        printf("-1\n");
        return;
    }
    node_ptr ptr = *list;
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
void list_delete_first(node_ptr * list)
{
    if(isEmpty(list))
    {
        printf("-1\n");
        return;
    }
    printf("%d\n", (*list)->key);
    (*list)= (*list)->next;
}
void list_delete_last(node_ptr * list)
{
    if(isEmpty(list))
    {
        printf("-1\n");
        return;
    }
    node_ptr ptr = *list;
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
void print_list(node_ptr *list)
{
    if(isEmpty(list))
    {
        printf("NULL\n");
        return;
    }
    node_ptr ptr = *list;
    while(ptr!=NULL)
    {
        printf("%d ", ptr->key);
        ptr=ptr->next;
    }
    printf("\n");
}

void StackEmpty(node_ptr *list)
{
    int bool =  isEmpty(list);
    if (bool) bool = -1;
    else bool = 1;
    printf("%d\n", bool);
}
void push(node_ptr* list, node_ptr x)
{
    list_insert_tail( list, x);
}

void pop(node_ptr * list)
{
    list_delete_last(list);
}
int main() 
{
    char in; int k ,x_key , y_key;
    node_ptr head = NULL,x,y; // initalizing head to null
    while(1)
    {
        scanf(" %c", &in);
        
        switch (in)
        {
            case 'i':

                scanf(" %d", &k);
                node_ptr x = create_node(k);
                push(&head,x);
                break;
            
            case 'd':
                pop(&head);
                break;

            case 'e':
                StackEmpty  (&head);
                
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

