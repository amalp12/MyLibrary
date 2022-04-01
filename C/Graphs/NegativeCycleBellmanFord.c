#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2147483647
#define INT_MIN -2147483648

struct node
{
    int u; // source
    int v; // destination
    int w; // weight
    struct node * next;

};


void insert(struct node ** head, int u, int v, int w)
{
    // index uth node
    struct node * uth_node = head[u];
    // create new node
    struct node * new_node = (struct node *) malloc(sizeof(struct node));
    new_node->u = u;
    new_node->v = v;
    new_node->w = w;
    new_node->next = NULL;

    // if uth node is empty
    if(uth_node == NULL)
    {
        head[u] = new_node;
        return;
    }
    // if uth node is not empty then insert into that list
    else
    {
        struct node * temp = uth_node;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }

}
// create a array of vertices with m vertices

struct node * * create_array_of_vertices(int m)
{
    struct node * * container = (struct node * *) malloc(sizeof(struct node  *) *m);
    // set all vertices as null
    for(int i = 0; i<m; i++)
    {
        container[i] = NULL;

    }
    
    return container;
}
int * create_array_of_vertices_cost(int m)
{
    int * container = (int *) malloc(sizeof(int) *m);
    container[0] = 0;
    for(int i = 1; i<m; i++)
    {
        container[i] = INT_MAX;
    }
    
    return container;
}



void relaxation_single( int u, int v, int w, int * cost, int * change_flag)
{
    if(cost[v] > cost[u] + w)
    {
        cost[v] = cost[u] + w;
        (*change_flag) = 1;
    }
}
void relaxation_single_iteration(struct node * * head, int * cost, int m, int * change_flag)
{
    (*change_flag) = 0;
    for(int i = 0; i<m; i++)
    {
        struct node * temp = head[i];
        while(temp != NULL)
        {
            relaxation_single(temp->u,temp->v,temp->w,cost, change_flag);
            temp = temp->next;
            
        }
    }
}

int containsNegativeCyle(struct node ** adj_list, int * cost, int n )
{
    // perform relaxation n-1 times
    int change_flag = 0;
    for(int i = 0; i<n-1; i++)
    {
        
        relaxation_single_iteration(adj_list,cost,n,&change_flag);
        
    }

    // perform relaxation nth time
    relaxation_single_iteration(adj_list,cost,n,&change_flag);
    // check if there is a negative cycle
    if(change_flag == 0)
    {
        return 0;
    }
    else return 1;

   

}

int main()
{

    // number of vertices and number of edges
    int n , m;
    struct node * temp;

    
    int x,y,w;
    scanf("%d %d", &n, &m);
    struct node * * adjacency_list = create_array_of_vertices(m);
    int * cost_array = create_array_of_vertices_cost(n);

    // Next m lines contains three integers x,y,w denoting there is a directed edge from x to y having a weight w.
    for(int i = 0; i<m; i++)
    {
        
        scanf("%d %d %d", &x, &y, &w);

        insert(adjacency_list,x,y,w);


    }
    int ans = containsNegativeCyle(adjacency_list,cost_array,n);
    
    if(ans == 1)
    {
        printf("1\n");
    }
    else
    {
        printf("-1\n");
    }

    


    return 0;
}


