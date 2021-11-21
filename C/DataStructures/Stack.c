#include <stdio.h>
#include <stdlib.h>
typedef struct stack * stack_ptr;

struct stack
{
    int capacity ;
    int top;
    char * array;
};

int StackFull(stack_ptr  stack)
{
    if ((stack->capacity-1)==(stack->top)) return -1;//full
    else return 1;
}
int StackEmpty(stack_ptr  stack)
{
    if (stack->top == -1) return -1; //empty
    else return 1;
}
void push (stack_ptr  stack, char k)
{
    if (StackFull(stack)==1) // if not full
    {
        stack->top +=1;
        stack->array[stack->top] = k;
    }
    else
    {
        printf("-1\n");
    }

}
void pop (stack_ptr stack)
{
    if(StackEmpty(stack)==1)//not empty
    {
        printf("%c\n",stack->array[stack->top]);
        stack->top-=1;
    }
    else
    {
        printf("-1\n");
    }
}

char peek(stack_ptr stack)
{
    if(StackEmpty(stack)==1)//not empty
    {
        printf("%c\n",stack->array[stack->top]);
        return stack->array[stack->top] ;
    }
    else
    {
        printf("-1\n");
        return '\0';
    }
    
}
int main() 
{
    int n ,x_key , y_key;
    char in ,k;
    scanf("%d",&n);
    char *array = (char *) malloc(sizeof(char)*n);
    stack_ptr S  = (stack_ptr)malloc(sizeof(struct stack));
    S->array = array;
    S->top = -1;
    S->capacity =n;
    while(1)
    {
        scanf(" %c", &in);
        //repeatedly reads a character `f', `t', `a', `b', `d', `i', `l', `p' or `e'
        switch (in)
        {
            case 'i':

                scanf(" %c", &k);
                push(S,k);
                break;

            case 'd':
                pop(S);
                break;
            case 'p':
                k = peek(S);
                break;

            case 't':
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

