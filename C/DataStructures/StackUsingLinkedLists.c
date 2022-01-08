#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
typedef long int li;
typedef struct stack_linked_node * stack_linked_node_ptr;

struct stack_linked_node
{
    int key ;
    stack_linked_node_ptr next;
};

int stack_linked_isEmpty(stack_linked_node_ptr * list)
{
    return ((*list)==NULL);
}
stack_linked_node_ptr stack_linked_create_node(int key)
{
    stack_linked_node_ptr new_node = (stack_linked_node_ptr)malloc(sizeof(struct stack_linked_node));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}
stack_linked_node_ptr stack_linked_list_search(stack_linked_node_ptr * list, int k)
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
        int temp = x->key;
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
void stack_linked_list_delete_first(stack_linked_node_ptr * list)
{
    if(stack_linked_isEmpty(list))
    {
        printf("-1\n");
        return;
    }
    printf("%d\n", (*list)->key);
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
        printf("%d ", ptr->key);
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
int main() 
{
    char in; int k ,x_key , y_key;
    stack_linked_node_ptr head = NULL,x,y; // initalizing head to null
    while(1)
    {
        scanf(" %c", &in);
        
        switch (in)
        {
            case 'i':

                scanf(" %d", &k);
                stack_linked_node_ptr x = stack_linked_create_node(k);
                stack_linked_push(&head,x);
                break;
            
            case 'd':
                stack_linked_pop(&head);
                break;

            case 'e':
                stack_linked_StackEmpty(&head);
                
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
