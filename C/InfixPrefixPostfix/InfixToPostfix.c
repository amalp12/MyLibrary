#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
typedef long int li;



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
        //printf("%c\n",stack->array[stack->top]);
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
        //printf("%c\n",stack->array[stack->top]);
        return stack->array[stack->top] ;
    }
    else
    {
        printf("-1\n");
        return '\0';
    }
    
}

int get_string_length(char * s)
{
    int length =0;
    char * ptr = s;
    while(*ptr != '\0')
    {
        ptr++; length++;
    }
    return length;
}


int isOperator(char a)
{
    char  operands[] = { '+', '-', '*','/', '^', '%' };
    int number_of_operands = 5;
    for (int i = 0; i < number_of_operands ; i++)
    {
        if(a == operands[i]) return 1;
    }

    return 0;

}

int isOperand(char a)
{
    if ((a >= 'a' && a <= 'z') ) return 1;
    else if  ((a >= 'A' && a <= 'Z') ) return 1;
    return 0;
}
int precedence(char a)
{
    char highest[] = {'^'}; int h = 1;
    char middle[] = {'*', '/', '%'}; int m = 3;
    char lowest[] = {'+', '-'}; int l = 2;

    // if one among the highest precedence return the value 3
    for (int i = 0; i < h ; i++)
    {
        if(a == highest[i]) return 3;
    }

    // if one among the middle precedence return the value 2
    for (int i = 0; i < m ; i++)
    {
        if(a == middle[i]) return 2;
    }

    // if one among the lowest precedence return the value 1
    for (int i = 0; i < l ; i++)
    {
        if(a == lowest[i]) return 1;
    }
    return -1;

}

char * infixToPostfix(stack_ptr stack, char * infix )
{
    char * postfix = (char *) malloc( sizeof(char) * 1000);
    int infix_length = get_string_length(infix), postfix_index =0;
    char temp;
    for ( int i =0 ; i< infix_length; i++)
    {
        if (isOperand(infix[i]))
        {
            postfix[postfix_index] = infix[i];
            postfix_index++;
        }

        else if (infix[i] == '(')
        {
            push(stack, infix[i]);
        }
        else if (infix[i] == ')')
        {
            temp = peek(stack);
            while(StackEmpty(stack) == 1 && temp !='(' )
            {
                temp = peek(stack);
                if (temp !='(' &&  temp !=')')
                {
                    postfix[postfix_index] = temp;
                    postfix_index++;
                }
                pop(stack);
            }
        }
        else if (isOperator(infix[i]))
        {
            // if stack is empty then push onto stack
            if( StackEmpty(stack)==-1)
            {
                push(stack, infix[i]);
            }
            else if (precedence(infix[i]) > precedence(peek(stack)) )
            {
                push(stack, infix[i]);
            }
            else if (precedence(infix[i]) ==  precedence(peek(stack)) && infix[i] == '^')
            {
                push(stack, infix[i]);
            }
            else
            {

                while(StackEmpty(stack)==1 && precedence(infix[i]) <=  precedence(peek(stack))) //while stack is not empty
                {
                    temp = peek(stack);
                    if (temp !='(' &&  temp !=')')
                    {
                        postfix[postfix_index] = temp;
                        postfix_index++;
                    }
                    pop(stack);

                }
                push(stack, infix[i]);
            }
        }   
        
    }
    while(StackEmpty(stack)==1)
    {
        temp = peek(stack);
        if (temp !='(' &&  temp !=')')
        {
            postfix[postfix_index] = temp;
            postfix_index++;
        }
        pop(stack);
    }
    postfix[postfix_index] ='\0';
    return postfix;
}



int main()
{
    int UPPERBOUND =1000;
    char * infix = (char *)malloc(sizeof(char)*UPPERBOUND);
    scanf("%s",infix);
    

    // intializing stack 
    char *array = (char *) malloc(sizeof(char)*UPPERBOUND);
    stack_ptr S  = (stack_ptr)malloc(sizeof(struct stack));
    S->array = array;
    S->top = -1;
    S->capacity = UPPERBOUND;
    


    char * postfix = infixToPostfix(S,infix);
    printf("%s",postfix);
    
    return 0;
}