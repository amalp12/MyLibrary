#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define INT_MAX 214748364
#define INT_MIN -214748364
/*

Write a program that implements Dijkstra’s algorithm for computing shortest paths in a directed
graph with positive edge weights. Assume that the nodes are labeled from 0 to n − 1.

*/
struct node
{
    int u; // source
    int v; // destination
    int w; // weight
    struct node * next;

};
struct distance_node
{
    int distance;
    int visited;
    int index;
};


void insert(struct node ** head, int u, int v, int w)
{
    // index uth node
    struct node * uth_node = head[u];
    // create new node
    struct node * new_node = (struct node *) malloc(sizeof(struct node));
    new_node->u = u;
    new_node->v = v;
    new_node->w = INT_MAX;
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


void insert_cost(struct node ** head, int u,  int w)
{
    // index uth node
    struct node * uth_node = head[u];
    // search for v in uth node
    while(uth_node != NULL)
    {
        if(uth_node->w == INT_MAX)
        {
            uth_node->w = w;
            return;
        }
        uth_node = uth_node->next;
    }

}


void take_in_adjacent_vertices( struct node * * adjacency_list, int source_vertex)
{
    char c;
    scanf("%c", &c);
    if(c == ' ')scanf("%c", &c);

    int flag = 0;
    int data =-1;
    if(c == '\0') return ;
    while(c!='\n')
    {
        
        if(c==' ')
        {
            
            flag = 0;
            insert(adjacency_list, source_vertex, data, INT_MAX);
            //printf("%d ", data);
        }
        else if (isdigit(c)>0)
        {
            if(flag==1)
            {

                data = data*10 + (c-'0');
            }
            else if (flag==0)
            {
                flag = 1;
                data = c-'0';
            }
        }
        
        scanf("%c", &c);
    }
    if(data!=-1)
    {
        insert(adjacency_list, source_vertex, data, INT_MAX);
        //printf("%d ", data);

    }
    return ;
}



void take_in_cost( struct node * * adjacency_list, int source_vertex)
{
    char c;
    scanf("%c", &c);
    if(c == ' ')scanf("%c", &c);

    int flag = 0;
    int data =-1;
    if(c == '\0') return ;
    while(c!='\n')
    {
        
        if(c==' ')
        {
            
            flag = 0;
            insert_cost(adjacency_list, source_vertex, data);
            //printf("%d ", data);
        }
        else if (isdigit(c)>0)
        {
            if(flag==1)
            {
                data = data*10 + (c-'0');
            }
            else if (flag==0)
            {
                flag = 1;
                data = c-'0';
            }
        }
        
        scanf("%c", &c);
    }
    if(data!=-1)
    {
        insert_cost(adjacency_list, source_vertex, data);
        //printf("%d ", data);

    }
    return ;
}



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

struct distance_node * * create_array_of_distances(int m,  struct node * * adjacency_list, int src)
{
    struct distance_node * * container = (struct distance_node * *) malloc(sizeof(struct distance_node  *) *m);
    struct distance_node * new_node ;
    for(int i = 0; i<m; i++)
    {
        if(i!=src)
        {
            new_node = (struct distance_node * ) malloc(sizeof(struct distance_node  ) *m);
            new_node->distance=INT_MAX;
            new_node->visited=0;
            new_node->index=i;
            container[i] = new_node;
        }
    }

    new_node = (struct distance_node * ) malloc(sizeof(struct distance_node  ) *m);
    new_node->distance=0;
    new_node->visited=0;
    new_node->index=src;
    container[src] = new_node;
    return container;
}

void take_input(int n , struct node * * adjacency_list)
{
    int source_vertex;
    for(int i = 0 ; i <n ; i++)
    {
        scanf("%d", &source_vertex);
        take_in_adjacent_vertices(adjacency_list, source_vertex);   
    }
    for(int i = 0 ; i <n ; i++)
    {
        scanf("%d", &source_vertex);
        take_in_cost(adjacency_list, source_vertex);
    }


}

void relaxation_single( int u, int v, int w,  struct distance_node **  cost)
{
    if(cost[v]->distance > cost[u]->distance + w)
    {
        cost[v]->distance = cost[u]->distance + w;  
    }
}

struct distance_node *  getMinimumDistanceHelper(struct distance_node * * distance_container, int n)
{
    struct distance_node * min = (struct distance_node *) malloc(sizeof(struct distance_node ));
    min ->visited = 0 ;
    min ->distance = INT_MAX;
    min ->index = -1;
    struct distance_node *temp;
    // get minimum distance that is not visited
    for(int i = 0;i<n;i++)
    {
        temp = distance_container[i];
        if(temp->visited == 0 && temp->distance< min->distance)
        {
            min = temp;
        }
    }
    return min;
}


void minimumDistances(struct node * * adjacency_list,  struct distance_node * * distance_container, int n, int src)
{
    
    // get the first node's adjacent node from adjacency list
    struct node * first_node_adj_list = adjacency_list[src];
    
    while (first_node_adj_list !=NULL)
    {
        relaxation_single(first_node_adj_list->u, first_node_adj_list->v, first_node_adj_list->w, distance_container);
        first_node_adj_list = first_node_adj_list->next;
    }
    distance_container[src]->visited=1;
    struct distance_node *  min ;//= getMinimumDistanceHelper(distance_container, n);
    struct node *  temp ;
    for(int i = 0 ; i < n;i++)
    {
    
        min = getMinimumDistanceHelper(distance_container, n);
        min -> visited+=1;
        if(min -> index == -1)break;
        temp = adjacency_list[min->index];
        while (temp !=NULL)
        {
            relaxation_single(temp-> u, temp->v,temp->w, distance_container);
            temp = temp->next;
        }
    }
}

void print_shortest_paths(struct distance_node * * distance_container, int n)
{
    int data;
    for(int i = 0; i <n;i++)
    {
        data = distance_container[i]->distance;
        if(data == INT_MAX)printf("INF ");
        else printf("%d ", data);
    }
    printf("\n");
}

int main()
{
    // number of vertices and number of edges
    int n ;
    struct node * temp;

    
    scanf("%d\n", &n);
    struct node * * adjacency_list = create_array_of_vertices(n);
    
    take_input(n, adjacency_list);
    

    char * str = (char *) malloc(sizeof(char)*5);
    int src, dest, data;

    while(scanf("%s", str))
    {
        if(strcmp(str,"apsp" )==0)
        {
            scanf("%d", &src);
            struct distance_node **  distance_container = create_array_of_distances(n,adjacency_list,  src);

            minimumDistances(adjacency_list, distance_container, n, src);   
            print_shortest_paths(distance_container,n);         
            free(distance_container);

        }
        else if(strcmp(str,"sssp")==0)
        {
            scanf("%d", &src);
            scanf("%d", &dest);
            struct distance_node * *  distance_container = create_array_of_distances(n,adjacency_list,  src);

            minimumDistances(adjacency_list, distance_container, n, src);
            data =  distance_container[dest]->distance;
            if(data == INT_MAX)printf("UNREACHABLE\n");
            else printf("%d\n", data);
            free(distance_container);

        }

        else if(strcmp(str,"stop" )==0)
        {
            return 0;
        }

    }


    return 0;
} 
