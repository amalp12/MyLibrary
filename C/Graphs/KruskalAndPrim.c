

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define INT_MAX 214748364
#define INT_MIN -214748364

/*

Write a program to compute the minimum spanning tree of a connected undirected graph G using the following algorithms:
    (a) Kruskal’s algorithm
    (b) Prim’s algorithm

*/


struct node
{
    int u; // source
    int v; // destination
    int w; // weight
    struct node * next;
    int visited;

};
struct set_node
{
    int data;
    int index;
    int rank;
    int visited;
    struct set_node * next;
};
struct distance_node
{
    int distance;
    int visited;
    int index;
};

struct set_node * get_node(struct set_node * container , int data)
{
    return (container + data*sizeof(struct set_node));
}

// create empty array and set all values as -2
// exists = 0 means  that element doesn't exist in set collection
// 1 means that element is in set collection
struct set_node * create_set_container_array(int upperbound)
{
    struct set_node * container = (struct set_node *) malloc(sizeof(struct set_node) *upperbound );
    struct set_node * temp;
    for(int i = 0; i<upperbound; i++)
    {
        temp = &container[i];
        temp->data = -1;
        temp->index = i;
        temp->rank = 0;
        temp->visited = 0;
    }
    return container;
}
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
    new_node->visited = 0;

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

void make_set( struct set_node  * container , int data)
{

    struct set_node * indexed_node = &container[data];
    if(indexed_node->rank == 0)
    {
        indexed_node ->rank = 1;
        
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


void take_in_adjacent_vertices( struct node * * adjacency_list, int source_vertex, int * cnt)
{
    char c;
    scanf("%c", &c);
    if(c == ' ')scanf("%c", &c);

    int flag = 0;
    int data =-1;
    int sign = 1;
    if(c == '\0') return ;
    while(c!='\n')
    {
        if(c=='-')
        {
            sign =-1;
        }
        
        else if(c==' ')
        {
            
            flag = 0;
            insert(adjacency_list, source_vertex, sign*data, INT_MAX);
            (*cnt)++;
            sign =1;
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
        insert(adjacency_list, source_vertex, sign*data, INT_MAX);
        (*cnt)++;

        sign=1;

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
    int sign = 1;

    if(c == '\0') return ;
    while(c!='\n')
    {
        
        if(c=='-')
        {
            sign =-1;
        }
        
        else if(c==' ')
        {
            
            flag = 0;
            insert_cost(adjacency_list, source_vertex,sign* data);
            sign =1;
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
        insert_cost(adjacency_list, source_vertex, sign* data);
        sign =1;


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

void take_input(int n , struct node * * adjacency_list, int * cnt)
{
    int source_vertex;
    for(int i = 0 ; i <n ; i++)
    {
        scanf("%d", &source_vertex);
        take_in_adjacent_vertices(adjacency_list, source_vertex, cnt);   
    }
    for(int i = 0 ; i <n ; i++)
    {
        scanf("%d", &source_vertex);
        take_in_cost(adjacency_list, source_vertex);
    }


}

int * create_visited_array(int n)
{
    int * arr = (int *) malloc(sizeof(int)*n);
    for(int i =0;i<n;i++)
    {
        arr[i]=0;
    }
    return arr;
}

struct node * minEdge(struct node * * adjacency_list,int n)
{

    struct node * min = adjacency_list[0];
    struct node * temp  ;

    for(int i = 0 ; i <n; i++)
    {
        temp = adjacency_list[i];
        while(temp != NULL)
        {
            if(temp->w < min->w)
            {
                min = temp;
            }
            temp = temp->next;
        }
    }
    return min;
}


        
struct node * minEdgeKruskal(struct node * * adjacency_list,int * visited_array, int n)
{

    struct node * min = adjacency_list[0];
    struct node * temp  ;

    for(int i = 0 ; i <n; i++)
    {
        temp = adjacency_list[i];
        while(temp != NULL)
        {
            if((temp->w<min->w && visited_array[temp->v]==0 && visited_array[temp->u]==0)||( visited_array[min->v]==1 &&  visited_array[temp->v]==0))
            {
                min = temp;
            }
            temp = temp->next;
        }
    }
    return min;
}
struct node * minConnection(struct node * curr, int * visited_array)
{
    
    struct node * min = curr;
    struct node * temp = min ;
    while (temp !=NULL)
    {
        if((temp->w<min->w && visited_array[temp->v]==0)||( visited_array[min->v]==1 &&  visited_array[temp->v]==0))
        {
            min = temp;
        }
        temp = temp->next;
    }
    return min;


}
int sumArray(int* arr, int n )
{
    int sum =0;
    for(int i =0 ;i<n;i++)
    {
        sum+=arr[i];
    }
    return sum;
}
int prims1(struct node * * adjacency_list,int n)
{
    int * visited_arr = create_visited_array(n);
    int sum = 0; 
    // search for the minimum cost edge
    struct node * min_cost_edge  = minEdge(adjacency_list,n);
    sum += min_cost_edge->w;
    visited_arr[(min_cost_edge->u)] =1;
    visited_arr[(min_cost_edge->v)] =1;
    struct node * u_min = minConnection(adjacency_list[min_cost_edge->u] , visited_arr);
    struct node * v_min = minConnection(adjacency_list[min_cost_edge->v] , visited_arr);
    
    if((u_min->w<v_min->w && visited_arr[u_min->v]==0)||(visited_arr[v_min->v]==1))
        min_cost_edge = u_min;
    else if((u_min->w>v_min->w && visited_arr[v_min->v]==0)||(visited_arr[u_min->v]==1)) min_cost_edge =v_min;
    else return sum;
    //sum += min_cost_edge->w;
    

    // mark the min cost edge as visited
    for(int i = 0 ; i < n-2 ; i++)
    {
        sum += min_cost_edge->w;
        visited_arr[(min_cost_edge->v)] =1;
        min_cost_edge = adjacency_list[min_cost_edge->v];
        min_cost_edge = minConnection(min_cost_edge , visited_arr);
    }

    return sum;
}
struct node_container_list
{
    struct node * nod;
    struct node_container_list * next;
};

void insert_into_list(struct node_container_list * * head, struct node * nod, int* visited_arr)
{
    if(visited_arr[nod->v]==1 && visited_arr[nod->u]==1)return;
    struct node_container_list * new_node = (struct node_container_list *) malloc(sizeof(struct node_container_list));
    new_node->nod = nod;
    new_node->next = NULL;
    
    if((*head)==NULL)
    {
        (*head) = new_node;
        return;
    }
    
    struct node_container_list * temp= (*head);
    while(temp->next!=NULL)
    {
        if((temp->nod->u == nod->u && temp->nod->v == nod->v) || (temp->nod->u == nod->v && temp->nod->v == nod->u) )
        {
            return;
        }
        temp = temp->next;
    }
    temp->next = new_node;
}

struct node_container_list * min_cost_node_not_visited(struct node_container_list * * head )
{
    struct node_container_list * temp= (*head);
    if(temp==NULL)
    {
        return NULL;
    }
    struct node_container_list * min = temp;
    while(temp!=NULL)
    {
        if((temp->nod->w < min->nod->w && temp->nod->visited == 0) || (min->nod->visited == 1&& temp->nod->visited == 0))
        {
            min = temp;
        }

        temp = temp->next;
    }
    return min;
}

int prims(struct node * * adjacency_list,int n)
{
    int * visited_arr = create_visited_array(n);
    int sum = 0; 

    // search for the minimum cost edge
    struct node * min_cost_edge  = minEdge(adjacency_list,n);
    sum += min_cost_edge->w;
    struct node_container_list *  head =NULL;
    struct node * temp;
    visited_arr[min_cost_edge->u] =1;
    visited_arr[min_cost_edge->v] =1;
    temp = adjacency_list[min_cost_edge->u];
    while(temp!=NULL)
    {
        if(visited_arr[temp->v]==0)
        {
            insert_into_list(&head,temp,visited_arr);
        }
        temp = temp->next;
    }

    temp = adjacency_list[min_cost_edge->v];
    while(temp!=NULL)
    {
        if(visited_arr[temp->v]==0)
        {
            insert_into_list(&head,temp,visited_arr);
        }
        temp = temp->next;
    }

    // search for the minimum cost edge that is not visited from the list 
    // mark it visited 
    // add its weight to the sum
    // take its unvisited connections and add it to list
    // repeat until all possible edges are visited
    for(int i = 0 ; i < n-2 ; i++)
    {
        struct node_container_list * min = min_cost_node_not_visited(&head);
        if(min==NULL || min->nod->visited == 1)
        {
            return sum;
        }

        sum += min->nod->w;
        min->nod->visited = 1;
        visited_arr[(min->nod->v)] =1;
        temp = adjacency_list[min->nod->v];
        while(temp!=NULL)
        {
            if(visited_arr[temp->v]==0)
            {
                insert_into_list(&head,temp,visited_arr);
            }
            temp = temp->next;
        }
        
    }


    return sum;

}

void swap(struct node  **  a, struct node  * *b)
{
    struct node  *   temp  = *a;
    *a = *b;
    *b = temp;
}
void insertionSort(struct node  * * arr, int n)
{
    int i,  j;
    struct node  *  key;
    for (i = 1; i < n; i++) 
    {
        key = arr[i];
        j = i - 1;
 
       
        while (j >= 0 && arr[j]->w > key->w) 
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

struct node * *adj_list_to_arr(struct node * * adjacency_list, int n, int num_edges )
{
    struct node  * * arr = (struct node **) malloc(sizeof(struct node*)*num_edges);
    int index =0;
    struct node * temp;
    for(int i = 0 ; i < n ; i++)
    {
        temp = adjacency_list[i];
        while (temp!=NULL)
        {
            arr[index] = temp;
            index++;
            temp = temp->next;
        }   
        
    }
    insertionSort(arr,num_edges);
    return arr;
}


struct set_node * find_set_path_compression(struct set_node * container , int data)
{
    struct set_node * indexed_node = &container[data];

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
        struct set_node * parent = find_set_path_compression(container,indexed_node->data);
        indexed_node->data = parent->index;
        return parent;
    }   
}

// both rank heuristic and path compression
void UnionD(struct set_node * container , int x , int y)
{
    struct set_node * rep_x = find_set_path_compression(container,x); 
    struct set_node * rep_y = find_set_path_compression(container,y);
    
    
    if( rep_x != NULL && rep_y != NULL)
    {
        // if both same rep then print it and return
        if(rep_x->index== rep_y->index)
        {
            //printf("%d\n",rep_x->index);  
        }
        else
        {
            // applying rank heuristic
            if(rep_x->rank > rep_y->rank)
            {
                rep_y->data = rep_x->index;
                //printf("%d\n",rep_x->index);
            }
            else if(rep_x->rank < rep_y->rank)
            {
                rep_x->data = rep_y->index;
                //printf("%d\n",rep_y->index);
            }
            else
            {
                rep_y->data = rep_x->index;
                rep_x->rank++;
                //printf("%d\n",rep_x->index);
            }
        

        }
    }
   




}
 
int prim(struct node * * array,int num_edges,int n)
{


    struct set_node * container = create_set_container_array(n);
    
   for(int i = 0; i <n; i++)
   {
       make_set(container,i);
   }
    int sum = 0;
    struct set_node * rep_u;
    struct set_node * rep_v;

    for(int i = 0 ; i < num_edges ; i++)
    {
        rep_u = find_set_path_compression(container,array[i]->u);
        rep_v = find_set_path_compression(container,array[i]->v);

        if (rep_u != rep_v)
        {
            sum += array[i]->w;
            UnionD(container,array[i]->u,array[i]->v);
        }
        
    }
    return sum;

}

int kruskal(struct node * * array,int num_edges,int n)
{


    struct set_node * container = create_set_container_array(n);
    
   for(int i = 0; i <n; i++)
   {
       make_set(container,i);
   }
    int sum = 0;
    struct set_node * rep_u;
    struct set_node * rep_v;

    for(int i = 0 ; i < num_edges ; i++)
    {
        rep_u = find_set_path_compression(container,array[i]->u);
        rep_v = find_set_path_compression(container,array[i]->v);

        if (rep_u != rep_v)
        {
            sum += array[i]->w;
            UnionD(container,array[i]->u,array[i]->v);
        }
        
    }
    return sum;

}


int main()
{
    // number of vertices and number of edges
    int n ;
    char c;
    struct node * temp;
    int ans ;

    scanf("%c\n",&c);
    scanf("%d\n", &n);
    int num_of_edges = 0;
    struct node * * adjacency_list = create_array_of_vertices(n);
    take_input(n, adjacency_list,&num_of_edges);
    if(c=='b')
    {
        ans = prims(adjacency_list,n);
        printf("%d\n", ans);
    }
    else if (c=='a')
    {
        struct node * *arr= adj_list_to_arr(adjacency_list,n,num_of_edges);
        ans = kruskal(arr, num_of_edges,n);
        printf("%d\n", ans);
    }


    return 0;
}
