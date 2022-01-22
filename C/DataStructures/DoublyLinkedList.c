#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
typedef long int li;
typedef struct DoublyLLnode * DoublyLL_node_ptr;

struct DoublyLLnode
{
    int key ;
    DoublyLL_node_ptr next;
    DoublyLL_node_ptr previous;
};

int DoublyLL_isEmpty(DoublyLL_node_ptr * list)
{
    return ((*list)==NULL);
}
DoublyLL_node_ptr DoublyLL_create_node(int key)
{
    DoublyLL_node_ptr new_node = (DoublyLL_node_ptr)malloc(sizeof(struct DoublyLLnode));
    new_node->key = key;
    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node;
}
DoublyLL_node_ptr DoublyLL_list_search(DoublyLL_node_ptr * list, int k)
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
        printf("%d\n", ptr->next->key);
        return;
    }
    //checking for the rest of the elements
    while( ptr->next !=NULL)
    {
        if(ptr->next->key == x->key )
        {
            if(ptr->next->next==NULL)printf("NULL\n");        
            else printf("%d ", ptr->next->key);
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
    printf("Not Found\n");
}
void DoublyLL_list_delete_initial(DoublyLL_node_ptr * list)
{
    if(DoublyLL_isEmpty(list))
    {
        printf("Not Found\n");
        return;
    }
    printf("%d\n", (*list)->key);
    (*list)= (*list)->next;
    if((*list)!=NULL) (*list)->previous = NULL;
}
void DoublyLL_list_delete_last(DoublyLL_node_ptr * list)
{
    if(DoublyLL_isEmpty(list))
    {
        printf("Not Found\n");
        return;
    }
    DoublyLL_node_ptr ptr = *list;
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
void DoublyLL_print_reverse(DoublyLL_node_ptr * list, int k )
{
    DoublyLL_node_ptr k_address = DoublyLL_list_search(list, k);
    if(k_address==NULL)
    {
        printf("Not Found\n");
        return;
    }
    while(k_address!=NULL)
    {
        printf("%d ", k_address->key);
        k_address = k_address->previous;
    }
    printf("\n");
}
void DoublyLL_print_list(DoublyLL_node_ptr *list)
{
    DoublyLL_node_ptr ptr = *list;
    while(ptr!=NULL)
    {
        printf("%d ", ptr->key);
        ptr=ptr->next;
    }
    printf("\n");
}
int main() 
{
    int k ,x_key , y_key;
    char in ;
    DoublyLL_node_ptr head = NULL,x,y; // initalizing head to null
    while(1)
    {
        scanf(" %c", &in);
        //repeatedly reads a character `f', `t', `a', `b', `d', `i', `l', `p' or `e'
        switch (in)
        {
            case 'f':

                scanf("%d", &k);
                DoublyLL_node_ptr x = DoublyLLnode_create_node(k);
                DoublyLLnode_list_insert_front(&head,x);
                break;

            case 't':
                scanf("%d", &k);
                x = DoublyLLnode_create_node(k);
                DoublyLLnode_list_insert_tail(&head,x);
                break;
            case 'a':
                scanf("%d", &x_key); scanf("%d", &y_key);
                x = DoublyLLnode_create_node(x_key); y = DoublyLLnode_create_node(y_key);
                DoublyLLnode_list_insert_after(&head,x,y);
                break;
            case 'b':
                scanf("%d", &x_key); scanf("%d", &y_key);
                x = DoublyLLnode_create_node(x_key); y = DoublyLLnode_create_node(y_key);
                list_insert_before(&head,x,y);
                break;

            case 'd':
                scanf("%d", &k);
                x = DoublyLLnode_create_node(k);
                DoublyLLnode_list_delete(&head, x);
                break;
            case 'i':
                DoublyLLnode_list_delete_initial(&head);
                break;
            case 'l':
                DoublyLLnode_list_delete_last(&head);
                break;
            case 'r':
                scanf("%d", &k);
                DoublyLLnode_print_reverse(&head, k);
                break;
            case 'e':
                return 0;
                break;
            // case 'p':
            //     print_list(&head);
            //     break;
            default:
                break;
        }
    }
	return 0;
}
