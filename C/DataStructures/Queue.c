#include <stdio.h>
#include <stdlib.h>
#define max_string_length 20
typedef struct queue * queue_ptr;

struct queue
{
    int capacity ;
    int head,tail ;
    char * * array;
};

int queueFull(queue_ptr  queue)
{
    if ((queue->capacity-1)==(queue->tail)) return -1;//full
    else return 1;
}
int queueEmpty(queue_ptr  queue)
{
    if (queue->head == -1 ) return -1; //empty
    else return 1;
}
void enqueue (queue_ptr  queue, char* k)
{
    if (queueFull(queue)==1) // if not full
    {
        if(queueEmpty(queue)==-1) // if queue empty
        { 
            queue->head+=1;
        }
        queue->tail +=1;
        queue->array[queue->tail] = k;  
    }
    else
    {
        printf("-1\n");
    }

}
void dequeue (queue_ptr queue)
{
    if(queueEmpty(queue)==1)//not empty
    {
        printf("%s\n",queue->array[queue->head]);
        if(queue->head == queue->tail)
        {
            queue->head =-1;
            queue->tail =-1;
            return;
        }
        queue->head += 1;
        
    }
    else
    {
        printf("-1\n");
    }
}


int main() 
{
    int n ,full , empty;
    char in ,k;
    scanf("%d",&n);
    char **array = (char **) malloc(sizeof(char*)*n);
    queue_ptr Q  = (queue_ptr)malloc(sizeof(struct queue));
    Q->array = array;
    Q->head = -1; Q->tail = -1;
    Q->capacity =n;
    while(1)
    {
        scanf(" %c", &in);
        //repeatedly reads a character `f', `t', `a', `b', `d', `i', `l', `p' or `e'
        switch (in)
        {
            case 'i':
            {
                char * string = (char *) malloc(sizeof(char)*(max_string_length+1));
                scanf("%s", string);
                enqueue(Q,string);
                //printf("%s\n" , Q->array[Q->tail]);
                break;
            }
            case 'd':
            {
                dequeue(Q);
                break;
            }
            case 'f':
            {
                full = queueFull(Q);
                printf("%d\n",full);
                break;
            }
            case 'e':
            {
                empty = queueEmpty(Q);
                printf("%d\n",empty);
                break;
            }
            case 't':
            {
                return 0;
                break;
            }
            // case 'p':
            //     print_list(&head);
            //     break;
            default:
                break;
        }
    }
	return 0;
}

