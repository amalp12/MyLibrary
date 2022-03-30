/*

In a binomial heap H, two nodes are cousins of each other if they are in the same binomial tree
T of H but have different parents such that their parents are siblings.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
#define INT_MIN  -2147483647

typedef long int li;
typedef struct node * node_ptr;
/*
queue linked list start
*/


typedef struct queue_linked_node * queue_linked_node_ptr;

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
        //printf("-1\n");
        return;
    }
    queue_linked_node_ptr ptr = *list;
    // checking if last element 
    if(ptr->next== NULL)
    {
        if(ptr->key ==x->key)
        {
            *list = NULL;
            //printf("-2\n");
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
    //printf("-1\n");
}
void queue_linked_list_delete_first(queue_linked_node_ptr * list)
{
    if(queue_linked_isEmpty(list))
    {
        //printf("-1\n");
        return;
    }
    //printf("%d\n", (*list)->key);
    (*list)= (*list)->next;
}
void queue_linked_list_delete_last(queue_linked_node_ptr * list)
{
    if(queue_linked_isEmpty(list))
    {
        //printf("-1\n");
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
        //printf("%d ", ptr->key);
        ptr=ptr->next;
    }
    printf("\n");
}

void queue_linked_QueueEmpty(queue_linked_node_ptr *list)
{
    int bool =  queue_linked_isEmpty(list);
    if (bool) bool = -1;
    else bool = 1;
    //printf("%d\n", bool);
}
void queue_linked_Enqueue(queue_linked_node_ptr* list, queue_linked_node_ptr x)
{
    queue_linked_list_insert_tail( list, x);
}

void queue_linked_Dequeue(queue_linked_node_ptr * list)
{
    queue_linked_list_delete_first(list);
}
/*
queue linked list end
*/

struct node
{
    int value ;
    node_ptr next;
    node_ptr child;
    node_ptr parent;
    int degree;
};

int isEmpty(node_ptr * list)
{
    return ((*list)==NULL);
}
node_ptr create_node(int value)
{
    node_ptr new_node = (node_ptr)malloc(sizeof(struct node));
    new_node->value = value;
    new_node->next = NULL;
    new_node-> parent = NULL;
    new_node->child = NULL;
    new_node->degree = 0;
    return new_node;
}
node_ptr list_search(node_ptr * list, int k)
{
    node_ptr ptr = *list;
    while(ptr!=NULL)
    {
        if(ptr->value==k) return ptr;
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
    node_ptr y_adress = list_search(list, y->value);
    if(y_adress!=NULL)
    {
        x->next = y_adress->next;// setting new node's next
        y_adress->next = x; // setting y node's next 

    } 
}

void list_insert_before(node_ptr* list,node_ptr x,node_ptr y)
{
    node_ptr y_adress = list_search(list, y->value);
    if(y_adress!=NULL)
    {
        x->next = y_adress->next;// setting new node's next
        y_adress->next = x; // setting y node's next
        int temp = x->value;
        x->value = y_adress->value;
        y_adress->value = temp; 

    } 
}
void list_delete(node_ptr* list,node_ptr x)
{
    if(isEmpty(list))
    {
        //printf("-1\n");
        return;
    }
    node_ptr ptr = *list;
    // checking if last element 
    if(ptr->next== NULL)
    {
        if(ptr->value ==x->value)
        {
            *list = NULL;
            //printf("-2\n");
            return;
        }
    }
    //checking for first element
    if(ptr->value==x->value)
    {
        *list = ptr->next;
        printf("%c\n", ptr->next->value);
        return;
    }
    //checking for the rest of the elements
    while( ptr->next !=NULL)
    {
        if(ptr->next->value == x->value )
        {
            if (ptr->next->next!=NULL)
            {
                ptr->next = ptr->next->next;
                //printf("%c\n", ptr->next->value);
                return;
            }
            else
            {
                ptr->next = NULL;
                //printf("-2\n");
                return;
            }
        }

        ptr=ptr->next;
    }
    //printf("-1\n");
}
void list_delete_first(node_ptr * list)
{
    if(isEmpty(list))
    {
       //printf("-1\n");
        return;
    }
    printf("%c\n", (*list)->value);
    (*list)= (*list)->next;
}
void list_delete_last(node_ptr * list)
{
    if(isEmpty(list))
    {
        //printf("-1\n");
        return;
    }
    node_ptr ptr = *list;
    if(ptr->next==NULL)
    {
        //printf("%c\n", ptr->value);
        *list = NULL;
        return;
    }
    while(ptr->next->next != NULL)
    {
        ptr=ptr->next;
    }
    //printf("%c\n", ptr->next->value);
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
        printf("%c ", ptr->value);
        ptr=ptr->next;
    }
    printf("\n");
}
node_ptr minimum(node_ptr head)
{
    int min = INT_MAX;
    node_ptr temp = head;
    while(temp-> next!=NULL)
    {
        if (temp -> value < min) min = temp->value ;
        temp = temp->next;

    }
    return temp;

}
node_ptr make_heap()
{
    node_ptr head = NULL;
    
    return head;
    
 }


//h1 is parent of h2
void binomial_link(node_ptr parent, node_ptr child)
{

    if (parent != NULL && child !=NULL)
    {
        
       
    
        child->parent = parent;
        child->next = parent->child;
        parent->child = child;
        (parent->degree )++;
            

        
    }
}

void merge_two_binomial_trees( node_ptr h1 , node_ptr h2)
{
    if (h1 != NULL && h2 !=NULL)
    {
        // h1 is smaller hence the parent
        if(h1-> value < h2->value)
        {
          binomial_link(h1, h2);
            

        }

        // h2 is smaller hence the parent
        if(h2-> value < h1->value)
        {
           binomial_link(h2,h1);
            

        }

        
    }

}
void insert_into_sorted_list(node_ptr * list, node_ptr x)
{
    // if list is empty 
    if((*list)==NULL)
    {
        (*list) = x;
        return;
    }
  
    node_ptr temp = *list;
    node_ptr prev = NULL;
    // if the element is to be inserted at the front
    if ( x-> degree <= temp->degree)
    {
        x-> next = temp ;
        *list = x;
        return ;
    }
    // while temp' value is smaller than x's value got to next, also set prev
    while(temp!=NULL && x->degree >temp->degree)
    {
        prev = temp;
        temp = temp->next;


        
    }
    // if temp is null then x is the last element
    if (temp ==NULL)
    {
        x->next = NULL;
        prev->next = x;
    }
    // if temp is not null then x is the middle
    else{
        x-> next = prev->next;
        prev->next = x;
    }

}
node_ptr heap_merge_degree_monotonically_increasing(node_ptr h1, node_ptr h2)
{
    if(h2==NULL) return h1;
    else if (h1==NULL     ) return h2;
    // h1 is taken as main heap and each element if h2 is insterted into h2
    node_ptr temp = h2;
    node_ptr temp_next ;
    while(temp!= NULL)
    {
        temp_next = temp->next;
        insert_into_sorted_list(&h1, temp);
        temp = temp_next;


    }
    return h1;
}
node_ptr Union( node_ptr h1, node_ptr h2)
{
    // partial merge heaaps in monotomically increasing order of degrees
    node_ptr new_head = heap_merge_degree_monotonically_increasing(h1, h2);
    if(new_head == NULL) return new_head; // if both heaps are empty
    
    /*
        iterate through the list and merge the root list and merge nodes with the same degree


        case 1 :
            if the degree of the current node is not not same as the degree of the next node then move the pointer forward

        case 2 :
            if the degree of the current node is same as the degreee of current->next and also current -> next -> next then also  move the pointer forward

        case 3 :
            if the degree of the current node is same as the degreee of current->next  but not current -> next -> next 
            and  current-> value < current-> next -> value then
                binomial_link(current, curent->next) and move the pointer forward

        case 4 :
            if the degree of the current node is same as the degreee of current->next  but not current -> next -> next 
            and  current-> value > current-> next -> value then
                reset head
                binomial_link(current-> next, next) and move the pointer forward

    */
    node_ptr current = new_head;
    node_ptr prev_current = NULL;
    node_ptr next_current = current->next;

    while( next_current!=NULL)
    {
        if((current->degree!= next_current->degree) || (next_current->next != NULL && next_current ->next-> degree == current-> degree )) // (case 1 or case 2)
        {
            prev_current = current;
            current = next_current;
        }

        else // (case 3 and  4) Note: its already checked for case 1 or 2 which returned false, which means degrees of current = current ->next != current -> next -> next 
        {
            if (current-> value <= next_current -> value ) // (case 3) 
            {
                current-> next = next_current->next;
                binomial_link(current , next_current);
                
            }
            else  //(current-> value > next_current -> value ) // (case 4)
            {
                if(prev_current == NULL) // if is head node
                {
                    new_head = next_current;

                   
                }
                else 
                {
                    prev_current->next = next_current;
                }
                binomial_link(next_current, current);
                current=next_current;
            }
        }
        next_current = current->next;
       
    }
    return new_head;
}


void print(node_ptr root)
{
    if (root != NULL)
    {
        // print root
        //printf("%d ", root->value);
        
        // create queue
        queue_linked_node_ptr head = NULL;
        // enqueue temp
        node_ptr temp = root; 
        if(temp==NULL) return ;

        do
        {
            queue_linked_Dequeue(&head);

            while(temp!=NULL)
            {
                // print temp
                printf("%d ", temp->value);
                // enqueue temp if temp has left child
                if(temp->child != NULL)
                {
                    queue_linked_node_ptr y = queue_linked_create_node(temp->child);
                    queue_linked_Enqueue(&head,y);
                }
                temp = temp->next;
            }
            // dequeue temp's left child
            if(head !=NULL) temp = head->key;
            if(temp!=NULL && queue_linked_isEmpty((&head))==1)
            {                   
                printf("%d ", temp->value);
            }               
        }while(queue_linked_isEmpty((&head))==0);
        
        printf("\n");
    }
    
}


int print_binomial_tree(node_ptr root)
{
    if (root != NULL)
    {
        // print root
        printf("%d ", root->value);
        
        // create queue
        queue_linked_node_ptr head = NULL;
        // enqueue temp
        node_ptr temp = root->child; 
        if(temp==NULL) return 1;

        do
        {
            while(temp!=NULL)
            {
                // print temp
                printf("%d ", temp->value);
                // enqueue temp if temp has left child
                if(temp->child != NULL)
                {
                    queue_linked_node_ptr y = queue_linked_create_node(temp->child);
                    queue_linked_Enqueue(&head,y);
                }
                temp = temp->next;
            }
            // dequeue temp's left child
           if(head !=NULL) temp = head->key;
            queue_linked_Dequeue(&head);
            if(temp!=NULL && queue_linked_isEmpty((&head))==1)
            {
                printf("%d ", temp->value);
            }
        }while(queue_linked_isEmpty((&head))==0);
        
        return 1;
    }
    else return 0;
}
void print2(node_ptr head)
{
    node_ptr temp = head;
    int flag = 0;
    while (temp!=NULL)
    {
        flag += print_binomial_tree(temp);
        temp = temp->next;
    }
    if(flag)printf("\n");
}
void insert (node_ptr * head, int val)
{
    node_ptr new_node = create_node(val);
    (*head )=  Union(*head, new_node);



}

node_ptr new_heap_from_min(node_ptr min)
{
    node_ptr new_heap = make_heap();
    node_ptr temp = min ->child;
    node_ptr ptr = NULL;
    while(temp!=NULL)
    {
        ptr = temp;
        temp = temp->next;
        ptr->next = NULL;
        new_heap = Union(new_heap, ptr);
    }
    return new_heap;
}
node_ptr extractMin( node_ptr * head)
{
    node_ptr min = *head;
    node_ptr temp = *head;
    node_ptr prev = NULL;
    node_ptr prev_temp;
    while(temp!=NULL)
    {
        if(temp->value < min->value)
        {
            min = temp;
            prev = prev_temp;
        }
        prev_temp = temp;
        temp = temp->next;
    }
    if(prev == NULL)
    {
        *head = min->next;
    }
    else
    {
        prev->next = min->next;
    }
    node_ptr min_heap = new_heap_from_min(min);
    (*head) = Union(*head, min_heap);

    return min;
}

node_ptr searchBinomialTree(node_ptr root, int val)
{
    // if noot is null return null
    if(root == NULL) return NULL;

    if(root->value == val) return root;
    node_ptr temp = root->child;
    while(temp!=NULL)
    {
        node_ptr temp_search = searchBinomialTree(temp, val);
        if(temp_search != NULL) return temp_search;
        temp = temp->next;
    }
    return NULL;
}

node_ptr searchBinomialHeap( node_ptr head , int val)
{
    node_ptr temp = head;
    while(temp!=NULL)
    {
        node_ptr temp_search = searchBinomialTree(temp, val);
        if(temp_search != NULL) return temp_search;
        temp = temp->next;
    }
    return NULL;
}
void decrease_key(node_ptr * head,  int key, int val)
{
    if (*head == NULL) return;
    if(val >key)
    {
        printf("-1\n");
        return;
    }
      


    node_ptr search_result = searchBinomialHeap(* head, key);
    if(search_result != NULL)
    {
        int temp;
        search_result->value -= val;
        printf("%d\n", search_result->value);
        while( search_result->parent!=NULL && search_result->value < search_result -> parent -> value)
        {
            // while the value of the node is less than its parent value
            // swap the values
            temp = search_result->value;
            search_result->value = search_result->parent->value;
            search_result->parent->value = temp;
            search_result = search_result->parent;
        }
        return;
    }
    else
    {
        printf("-1\n");
    }



}
void delete( node_ptr* head, int val)
{
    node_ptr search_result = searchBinomialHeap(*head, val);
    if (search_result != NULL)
    {
        printf("%d\n", search_result->value);
        search_result->value = INT_MIN;
        decrease_key(head, val, INT_MIN);
        (*head) = extractMin(head);
    }
    else
    {
        printf("-1\n");
    }
}      





node_ptr CreateBinomialHeap(int k)
{
	node_ptr H = make_heap();
	insert(&H, k);
	return H;
}
/*	
	

Function CountCousins(H, k):
	node = FindNode(k)
	count = 0
	if node:
		parent = node → parent
		if parent  :
			grandparent = parent →parent
			
			if grandparent:
		
				temp = grandparent->child
				while(temp):
					if( temp != parent):
						count += temp→ degree
	
		return count
	else:
		return -1


Function Main:
	H =  MakeHeap()
	char in
	Switch in:
		case ‘i’:
		 	take in val
			H.insert(val)
		case ‘c’:
		 	take in val
			cousins = CountCousins(H, k):
			print(cousins)
		case ‘e’:
		 	return 0
		

		


	Return 0



*/

int CountCousins(node_ptr H, int k)
{
	node_ptr node = searchBinomialHeap(H, k);
	int count = 0;
	if (node!=NULL)
	{
		node_ptr parent = node -> parent;
		if(parent!=NULL)
		{
			node_ptr grandparent = parent -> parent;
			if (grandparent!=NULL)
			{
				node_ptr temp = grandparent->child;
				while(temp!=NULL)
				{
					if(temp!=parent)
					{
						count+= temp->degree;
					}
					temp = temp -> next;					

				}
			}
		}
		return count;
	}
	else return -1;
}
	
		


int main()
{

    char in ;
    int val;
    int cousins;




    node_ptr head = NULL;
    while(1)
    {
        scanf("%c", &in );
        //• Each line contains a character from ‘i’, ‘m’, ‘x’, ‘r’, ‘d’ and ‘e’ followed by at most one integer.
        switch(in )
        {
            case 'i':
            {
                scanf("%d", &val);
                insert(&head, val);
                break;
            }
           
            
            case 'c':
            {
                scanf("%d", &val);
                cousins = CountCousins(head, val);
                printf("%d\n", cousins);
                break;
            }
            case 'e':
            {
                return 0;
                break;
            }
            default:
            {
                break;
            }


        }

    }

    return 0;


}

