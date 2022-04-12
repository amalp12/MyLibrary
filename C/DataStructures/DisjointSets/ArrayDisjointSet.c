#include <stdio.h>
#include <stdlib.h>


struct node
{
    int data;
    int index;
    int rank;
    struct node * next;
};

struct node * get_node(struct node * container , int data)
{
    return (container + data*sizeof(struct node));
}
// create empty array and set all values as -2
// exists = 0 means  that element doesn't exist in set collection
// 1 means that element is in set collection
struct node * create_set_container_array()
{
    int upperbound = 10001;
    struct node * container = (struct node *) malloc(sizeof(struct node) *upperbound );
    struct node * temp;
    for(int i = 0; i<upperbound; i++)
    {
        
        container[i].data = -1;
        container[i].index = i;
        container[i].rank = 0;
    }
    return container;
}
void make_set( struct node  * container , int data, int print)
{

    struct node * indexed_node = &container[data];
    if(indexed_node->rank == 0)
    {
        indexed_node ->rank = 1;
        if(print)printf("%d\n",data);
    }
    else{
        if(print)printf("-1\n");
    }

}

struct node * find_set(struct node * container , int data, int * cnt)
{
    (*cnt)++;
    struct node * indexed_node = &container[data];

    if(indexed_node->rank==0) return NULL;
    // if the value is -1 then it is a singleton element

    if(indexed_node->data == -1)
    {
        return indexed_node;
    }
    // if the value is not -1 then it is not a singleton element
    // so we need to find the parent of the element
    // and return the parent
    else
    {
        struct node * parent = find_set(container,indexed_node->data, cnt);
        return parent;
    }   
}


struct node * find_set_path_compression(struct node * container , int data, int * cnt)
{
    (*cnt)++;
    struct node * indexed_node = &container[data];

    if(indexed_node->rank==0) return NULL;
    // if the value is -1 then it is a singleton element

    if(indexed_node->data == -1)
    {
        return indexed_node;
    }
    // if the value is not -1 then it is not a singleton element
    // so we need to find the parent of the element
    // and return the parent
    else
    {
        struct node * parent = find_set_path_compression(container,indexed_node->data, cnt);
        indexed_node->data = parent->index;
        return parent;
    }   
}
void UnionA(struct node * container , int x , int y, int * cnt)
{
    struct node * rep_x = find_set(container,x, cnt); 
    struct node * rep_y = find_set(container,y, cnt);
    
    
    if( rep_x != NULL && rep_y != NULL)
    {
        // if both same rep then print it and return
        if(rep_x->index== rep_y->index)
        {
            printf("%d ",rep_x->index);  
        }
        else
        {// make x parent of y
            rep_y->data = rep_x->index;
            printf("%d ",rep_x->index);
        }
    }
    else
    {
        printf("-1 ");
    }



}
// rank heuristic only
void UnionB(struct node * container , int x , int y, int * cnt)
{
    struct node * rep_x = find_set(container,x, cnt); 
    struct node * rep_y = find_set(container,y, cnt);
    
    
    if( rep_x != NULL && rep_y != NULL)
    {
        // if both same rep then print it and return
        if(rep_x->index== rep_y->index)
        {
            printf("%d ",rep_x->index);  
        }
        else
        {
            // applying rank heuristic
            if(rep_x->rank > rep_y->rank)
            {
                rep_y->data = rep_x->index;
                printf("%d ",rep_x->index);
            }
            else if(rep_x->rank < rep_y->rank)
            {
                rep_x->data = rep_y->index;
                printf("%d ",rep_y->index);
            }
            else
            {
                rep_y->data = rep_x->index;
                rep_x->rank++;
                printf("%d ",rep_x->index);
            }
        

        }
    }
    else
    {
        printf("-1 ");
    }




}
// path compression only
void UnionC(struct node * container , int x , int y, int * cnt)
{
    struct node * rep_x = find_set_path_compression(container,x, cnt); 
    struct node * rep_y = find_set_path_compression(container,y, cnt);
    
    
    if( rep_x != NULL && rep_y != NULL)
    {
        // if both same rep then print it and return
        if(rep_x->index== rep_y->index)
        {
            printf("%d ",rep_x->index);  
        }
        else
        {// make x parent of y
            rep_y->data = rep_x->index;
            printf("%d ",rep_x->index);
        }
    }
    else
    {
        printf("-1 ");
    }



}




// both rank heuristic and path compression
void UnionD(struct node * container , int x , int y, int * cnt)
{
    struct node * rep_x = find_set_path_compression(container,x, cnt); 
    struct node * rep_y = find_set_path_compression(container,y, cnt);
    
    
    if( rep_x != NULL && rep_y != NULL)
    {
        // if both same rep then print it and return
        if(rep_x->index== rep_y->index)
        {
            printf("%d\n",rep_x->index);  
        }
        else
        {
            // applying rank heuristic
            if(rep_x->rank > rep_y->rank)
            {
                rep_y->data = rep_x->index;
                printf("%d\n",rep_x->index);
            }
            else if(rep_x->rank < rep_y->rank)
            {
                rep_x->data = rep_y->index;
                printf("%d\n",rep_y->index);
            }
            else
            {
                rep_y->data = rep_x->index;
                rep_x->rank++;
                printf("%d\n",rep_x->index);
            }
        

        }
    }
    else
    {
        printf("-1\n");
    }




}


int main()
{

    struct node  * sets_container_a = create_set_container_array();
    struct node  * sets_container_b = create_set_container_array();
    struct node  * sets_container_c = create_set_container_array();
    struct node  * sets_container_d = create_set_container_array();
    struct node * temp1, * temp2, *temp3, *temp4;
    int find_set_cnt_a = 0;
    int find_set_cnt_b = 0;
    int find_set_cnt_c = 0;
    int find_set_cnt_d = 0;
    
    char in;

    int data, data1;
    while(1)
    {
        scanf("%c", &in);
        switch(in)
        {
            case 'm':
            {
                // make set
                // takes in one element
                scanf("%d", &data);
                make_set(sets_container_a, data,1);
                make_set(sets_container_b, data,0);
                make_set(sets_container_c, data,0);
                make_set(sets_container_d, data,0);
                break;
            }
            case 'u':
            {
                scanf("%d", &data);
                scanf("%d", &data1);

                UnionA(sets_container_a,data,data1, &find_set_cnt_a);
                UnionB(sets_container_b,data,data1, &find_set_cnt_b);
                UnionC(sets_container_c,data,data1, &find_set_cnt_c);
                UnionD(sets_container_d,data,data1, &find_set_cnt_d);
                break;
            }
            case 'f':
            {
                scanf("%d", &data);
                

                temp1 = find_set(sets_container_a,data, &find_set_cnt_a);
                temp2 = find_set(sets_container_b,data, &find_set_cnt_b);
                temp3 = find_set_path_compression(sets_container_c,data, &find_set_cnt_c);
                temp4 = find_set_path_compression(sets_container_d,data, &find_set_cnt_d);

                if(temp1 != NULL)
                {
                    printf("%d ",temp1->index);
                }
                else
                {
                    printf("-1 ");
                }

                if(temp2 != NULL)
                {
                    printf("%d ",temp2->index);
                }
                else
                {
                    printf("-1 ");
                }
                if(temp3 != NULL)
                {
                    printf("%d ",temp3->index);
                }
                else
                {
                    printf("-1 ");
                }

                if(temp4 != NULL)
                {
                    printf("%d\n",temp4->index);
                }
                else
                {
                    printf("-1\n");
                }

                break;
            }
            
            case 's':
            {
                printf("%d ",find_set_cnt_a);
                printf("%d ",find_set_cnt_b);
                printf("%d ",find_set_cnt_c);
                printf("%d\n",find_set_cnt_d);
                return 0;
                break;
            }
            default:
                break;

        }
    }
    return 0;
}
