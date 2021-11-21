#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
typedef long int li;



typedef struct stack * stack_ptr;
typedef struct node * node_ptr;

struct node
{
    char  val;
    node_ptr left ;
    node_ptr right;
};

node_ptr create_node(char val)
{
    node_ptr new_node = (node_ptr) malloc(sizeof(struct node));
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;

}






struct stack
{
    int capacity ;
    int top;
    node_ptr * array;
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
void push (stack_ptr  stack, node_ptr  k)
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

node_ptr peek(stack_ptr stack)
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

node_ptr constructTree(stack_ptr stack, char * postfix )
{
    int postfix_length = get_string_length(postfix);

    for ( int i =0 ; i< postfix_length; i++)
    {
        if(isOperand(postfix[i]))
        {
            push(stack , create_node(postfix[i]));

        }
        else if(isOperator(postfix[i]))
        {
            node_ptr new = create_node(postfix[i]);
            new->right = peek(stack); // this order is very important
            pop(stack); 
            new->left = peek(stack);// this order is very important
            pop(stack);
            
            push(stack, new);
        }
    }
    node_ptr binary_expression_tree =  peek(stack);
    pop(stack);
    return binary_expression_tree;
}

void inorder(node_ptr tree)
{
    //left root right
    if(tree)
    {
        inorder(tree->left);
        printf("%c", tree->val);
        inorder(tree->right);
    }
    

}
void preorder(node_ptr tree)
{
    //root left right
    if(tree)
    {
        printf("%c", tree->val);
        preorder(tree->left);
        preorder(tree->right);
    }

}

void postorder(node_ptr tree)
{
    //left right root
    if(tree)
    {
        postorder(tree->left);
        postorder(tree->right);
        printf("%c", tree->val);
    }

}




int main()
{
    int UPPERBOUND =1000;
    char * postfix = (char *)malloc(sizeof(char)*UPPERBOUND);
  
    

    // intializing stack 
    node_ptr *array = (node_ptr *) malloc(sizeof(node_ptr)*UPPERBOUND);
    stack_ptr S  = (stack_ptr)malloc(sizeof(struct stack));
    S->array = array;
    S->top = -1;
    S->capacity = UPPERBOUND;

    // tree
    node_ptr binary_expression_tree = NULL;

    char in;
    while(1)
    {
        scanf(" %c", &in);
        
        switch (in)
        {
            case 'e':

                scanf("%s",postfix);
                binary_expression_tree = constructTree(S, postfix);
                break;

            case 'i':
                inorder(binary_expression_tree);
                printf("\n");
                break;
            case 'p':
                preorder(binary_expression_tree);
                printf("\n");
                break;
            case 's':
                postorder(binary_expression_tree);
                printf("\n");
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