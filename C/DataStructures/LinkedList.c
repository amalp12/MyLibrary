#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
typedef long int li;
typedef struct node * node_ptr;

struct node
{
    char key ;
    node_ptr next;
};

int isEmpty(node_ptr * list)
{
    return ((*list)==NULL);
}
node_ptr create_node(char key)
{
    node_ptr new_node = (node_ptr)malloc(sizeof(struct node));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}
node_ptr list_search(node_ptr * list, char k)
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
        char temp = x->key;
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
        printf("%c\n", ptr->next->key);
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
                printf("%c\n", ptr->next->key);
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
    printf("%c\n", (*list)->key);
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
        printf("%c\n", ptr->key);
        *list = NULL;
        return;
    }
    while(ptr->next->next != NULL)
    {
        ptr=ptr->next;
    }
    printf("%c\n", ptr->next->key);
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
        printf("%c ", ptr->key);
        ptr=ptr->next;
    }
    printf("\n");
}
int main() 
{
    char in, k ,x_key , y_key;
    node_ptr head = NULL,x,y; // initalizing head to null
    while(1)
    {
        scanf(" %c", &in);
        //repeatedly reads a character `f', `t', `a', `b', `d', `i', `l', `p' or `e'
        switch (in)
        {
            case 'f':

                scanf(" %c", &k);
                node_ptr x = create_node(k);
                list_insert_front(&head,x);
                break;

            case 't':
                scanf(" %c", &k);
                x = create_node(k);
                list_insert_tail(&head,x);
                break;
            case 'a':
                scanf(" %c", &x_key); scanf(" %c", &y_key);
                x = create_node(x_key); y = create_node(y_key);
                list_insert_after(&head,x,y);
                break;
            case 'b':
                scanf(" %c", &x_key); scanf(" %c", &y_key);
                x = create_node(x_key); y = create_node(y_key);
                list_insert_before(&head,x,y);
                break;

            case 'd':
                scanf(" %c", &k);
                x = create_node(k);
                list_delete(&head, x);
                break;
            case 'i':
                list_delete_first(&head);
                break;
            case 'l':
                list_delete_last(&head);
                break;
            case 'p':
                print_list(&head);
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

