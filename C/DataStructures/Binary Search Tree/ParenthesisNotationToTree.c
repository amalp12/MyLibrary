#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define INT_MAX  2147483647
#define INT_MIN  -2147483647
typedef long int li;
typedef struct tree_node * tree_node_ptr;


// queue using linked lists start
typedef struct queue_linked_node * queue_linked_node_ptr;

struct queue_linked_node
{
    char key ;
    queue_linked_node_ptr next;
};

int queue_linked_isEmpty(queue_linked_node_ptr * list)
{
    return ((*list)==NULL);
}
queue_linked_node_ptr queue_linked_create_node(char key)
{
    queue_linked_node_ptr new_node = (queue_linked_node_ptr)malloc(sizeof(struct queue_linked_node));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}
queue_linked_node_ptr queue_linked_list_search(queue_linked_node_ptr * list, char k)
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
        char temp = x->key;
        x->key = y_adress->key;
        y_adress->key = temp; 

    } 
}
void queue_linked_list_delete(queue_linked_node_ptr* list,queue_linked_node_ptr x)
{
    if(queue_linked_isEmpty(list))
    {
        printf("-1\n");
        return;
    }
    queue_linked_node_ptr ptr = *list;
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
        printf("%d\n", ptr->next->key);
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
                printf("%d\n", ptr->next->key);
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
        printf("%c ", ptr->key);
        ptr=ptr->next;
    }
    printf("\n");
}

void queue_linked_QueueEmpty(queue_linked_node_ptr *list)
{
    int bool =  queue_linked_isEmpty(list);
    if (bool) bool = -1;
    else bool = 1;
    printf("%d\n", bool);
}
void queue_linked_Enqueue(queue_linked_node_ptr* list, queue_linked_node_ptr x)
{
    queue_linked_list_insert_tail( list, x);
}

void queue_linked_Dequeue(queue_linked_node_ptr * list)
{
    queue_linked_list_delete_first(list);
}
char queue_linked_front(queue_linked_node_ptr * list)
{
    if(queue_linked_isEmpty(list))
    {
        
        return '\0';
    }
    return (*list)->key;
}
char queue_linked_rear(queue_linked_node_ptr * list)
{
    if(queue_linked_isEmpty(list))
    {
        return '\0';
    }
    queue_linked_node_ptr ptr = *list;
    while(ptr->next!=NULL)
    {
        ptr=ptr->next;
    }
    return ptr->key;
}
// queue using linked lists end

struct tree_node
{
    int data;
    tree_node_ptr parent ;
    tree_node_ptr left; // left child less than data
    tree_node_ptr right; // right child greater than data
    int visited;
};



tree_node_ptr create_node(int key)
{
    tree_node_ptr new_node = (tree_node_ptr) malloc(sizeof(struct tree_node));
    new_node->data = key;
    new_node->right = NULL;
    new_node->left = NULL;
    new_node->parent = NULL;
    new_node->visited = 0;
    return new_node;
}

void insert_tree_node(tree_node_ptr root, tree_node_ptr new_node)
{
    // if tree is empty put the current node as root node
    if (root ==NULL)
    {
        root = new_node;
        return;
    }
    
    // if the new node is less than current node then go left
    if(new_node-> data < root->data)
    {
        //if the left child is empty then insert the new node as left child
        if(root->left == NULL)
        {
            root->left = new_node;
            new_node->parent = root;
            return;
        }
        // if the left child is not empty then recursively call the function insert tree node towards left
        else
        {
            insert_tree_node(root->left, new_node); // pass by memory
        }

    }
    // if new node is greater than the current node then go right
    else if (new_node -> data >root->data)
    {
        //if the right child is empty then insert the new node as right child
        if(root->right == NULL)
        {
            root->right = new_node;
            new_node->parent = root;
            return;
        }
        // if the right child is not empty then recursively call the function insert tree node towards right
        else
        {
            insert_tree_node(root->right, new_node); // pass by memory
        }
    }
    else// if the new node is equal to the current node then do nothing
    {
        return;
    }
}
tree_node_ptr search(tree_node_ptr  root, int key)
{
    // if the root is empty then return NULL
    if(root == NULL)
    {
        return NULL;
    }
    tree_node_ptr ptr = root;
    //if key is equal to the current node then return the current node
    if(ptr->data == key)
    {
        return ptr;
    }
    // if the key is less than the current node then go left
    else if(key < ptr->data)
    {
        return search(ptr->left, key);
    }
    // if the key is greater than the current node then go right
    else if (key > ptr->data)
    {
        return search(ptr->right, key);
    }
    else
    {
        return NULL;
    }

}
tree_node_ptr get_parent( tree_node_ptr root, tree_node_ptr child)
{
    // if the root is empty then return NULL
    if(root == NULL)
    {
        return NULL;
    }
    // if the root is equal to the child then return NULL
    if(root == child)
    {
        return NULL;
    }
    // if the left child is equal to the child then return the root
    if(root->left == child)
    {
        return root;
    }
    // if the right child is equal to the child then return the root
    else if(root->right == child)
    {
        return root;
    }
    // if the left child is not empty then recursively call the function get parent towards left
    if(child->data <root->data )
    {
        return get_parent(root->left, child);
    }
    // if the right child is not empty then recursively call the function get parent towards right
    else if(child->data >root->data)
    {
        return get_parent(root->right, child);
    }
    
}

tree_node_ptr get_sucessor(tree_node_ptr root, int data)
{

    tree_node_ptr search_result = search(root, data);
    if(search_result!=NULL)
    {
        // if right subtree not null then  sucessor will be the leftmost child of hte right subtree or right child itself
        if(search_result->right != NULL)
        {
            tree_node_ptr temp = search_result->right; ;
            while(temp->left != NULL)
            {
                temp = temp->left;
            }
            if (temp->data < search_result->data) return NULL;
            return temp;
        }
        else // if right subtree is null sucessor will be the last left child's parent while searching the current node
        {
            tree_node_ptr sucessor= root;
            tree_node_ptr temp = root;
            while(temp->data != search_result->data)
            {
                if (search_result->data > temp->data)
                {
                    temp = temp->right;
                }
                else
                {
                    sucessor = temp;
                    temp = temp->right;
                }
            }
            if (sucessor->data < search_result->data) return NULL;
            return sucessor;
            
        }
    }
    else
    {
        return NULL;
    }

}



tree_node_ptr get_predecessor(tree_node_ptr root, int data)
{
  


    tree_node_ptr search_result = search(root, data);
    if(search_result!=NULL)
    {
        // if left subtree not null then  sucessor will be the rightmost child of hte left subtree or left child itself
        if(search_result->left != NULL)
        {
            tree_node_ptr temp = search_result->left; 
            while(temp->right != NULL)
            {
                temp = temp->right;
            }
            if (temp->data > search_result->data) return NULL;
            return temp;
        }
        else // if left subtree is null sucessor will be the last right child's parent while searching the current node
        {
            tree_node_ptr predecessor = root;
            tree_node_ptr temp = root;
            while(temp->data != search_result->data)
            {
                if (search_result->data < temp->data)
                {
                    temp = temp->left;
                }
                else
                {
                    predecessor = temp;
                    temp = temp->right;
                }
               
            }
            if (predecessor->data > search_result->data) return NULL;
            return predecessor;
            
        }
    }
    else
    {
        return NULL;
    }

}

void delete_node(tree_node_ptr * root, int key)
{
    
    // if the root is empty then return
    if(*root == NULL)
    {
        return ;
    }
    if((*root)->data == key && (*root)->left == NULL && (*root)->right == NULL)
    {
        *root = NULL;
        return;
    }
    tree_node_ptr search_result = search(*root, key);
    if(search_result != NULL)
    {
        tree_node_ptr parent = get_parent(*root, search_result);

        // if parent is null then that means root node is to be deleted
        if (parent==NULL)
        {
            tree_node_ptr sucessor = get_sucessor(*root, key);
            if(sucessor != NULL)
            {
                int temp = sucessor->data;
                delete_node(root, sucessor->data);
                search_result->data = temp;
            }
            else
            {
                tree_node_ptr predecessor = get_predecessor(*root, key);        
                int temp = predecessor->data;
                delete_node(root, predecessor->data);
                search_result->data = temp;
            }
        }
        // if the node to be deleted has no children aka leaf node
        else if(search_result->left == NULL && search_result->right == NULL)
        {
            
            if(parent->left == search_result)
            {
                parent->left = NULL;
            }
            else if(parent->right == search_result)
            {
                parent->right = NULL;
            }
            else
            {
                printf("error! out of bounds.");
            }
        }
        // if the node to be deleted has one child only
        else if (search_result->left == NULL || search_result->right == NULL)
        {   
            // if the node to be deleted has right child
            if(search_result->left == NULL)
            {
                // if the node to be deleted is the parent's left child
                if(parent->left == search_result)
                {
                    // set the parent's left child to the right child of the node to be deleted
                    parent->left = search_result->right;
                }
                // if the node to be deleted is the parent's right child
                else if(parent->right == search_result)
                {
                    // set the parent's right child to the right child of the node to be deleted
                    parent->right = search_result->right;
                }
                else
                {
                    printf("error! out of bounds.");
                }
            }
            // if the node to be deleted has left child
            else if(search_result->right == NULL)
            {
                // if the node to be deleted is the parent's left child
                if(parent->left == search_result)
                {
                    // set the parent's left child to the left child of the node to be deleted
                    parent->left = search_result->left;
                }
                // if the node to be deleted is the parent's right child
                else if(parent->right == search_result)
                {
                    // set the parent's right child to the left child of the node to be deleted
                    parent->right = search_result->left;
                }
                else
                {
                    printf("error! out of bounds.");
                }
            }
        }
        // if the node to be deleted has two children
        else
        {
            tree_node_ptr successor = get_sucessor( *root, search_result->data );
            int temp_data = successor->data;
            delete_node (root, successor->data);
            // if the node to be deleted is the parent's left child
            if(parent->left == search_result)
            {
                
                parent->left->data =temp_data;
            }
            // if the node to be deleted is the parent's right child
            else if(parent->right == search_result)
            {
        
                parent->right->data =temp_data;
            }
            else
            {
                printf("error! out of bounds.");
            }
        }
    }
    else return ;

    
}
tree_node_ptr minimum(tree_node_ptr root)
{
    if(root == NULL)
    {
        return NULL;
    }
    tree_node_ptr ptr = root;
    while(ptr->left!=NULL)
    {
        ptr = ptr->left;
    }
    return ptr;
}

tree_node_ptr maximum(tree_node_ptr root)
{
    if(root == NULL)
    {
        return NULL;
    }
    tree_node_ptr ptr = root;
    while(ptr->right!=NULL)
    {
        ptr = ptr->right;
    }
    return ptr;
}
void preorder(tree_node_ptr  current_node)
{
    if(current_node == NULL)
    {
        return;
    }

    printf("%d ", current_node->data);
    preorder(current_node->left);
    preorder(current_node->right);
}

void postorder(tree_node_ptr  current_node)
{
    if(current_node == NULL)
    {
        return;
    }

    postorder((current_node->left));
    postorder((current_node->right));
    printf("%d ", current_node->data);
}


void inorder(tree_node_ptr current_node)
{
    if(current_node == NULL)
    {
        return;
    }

    inorder((current_node->left));
    printf("%d ", current_node->data);
    inorder((current_node->right));
}
void insert(tree_node_ptr * root, int key)
{
    // if the root is empty then create a new node
    if(*root == NULL)
    {
        (*root) = create_node(key);
        return;
    }
    tree_node_ptr new_node = create_node(key);
    insert_tree_node(*root, new_node);
}
void sucessor(tree_node_ptr root, int data)
{
    tree_node_ptr sucessor = get_sucessor(root, data);
    if(sucessor!=NULL)
    {
        printf("%d\n", sucessor->data);
    }
    else
    {
        printf("-1\n");
    }
}

void predecessor(tree_node_ptr root, int data)
{
    tree_node_ptr predecessor = get_predecessor(root, data);
    if(predecessor!=NULL)
    {
        printf("%d\n", predecessor->data);
    }
    else
    {
        printf("-1\n");
    }
}

void delete(tree_node_ptr * root, int key)
{
    tree_node_ptr search_result = search(*root, key);
    if (search_result!=NULL)
    {
        delete_node(root, key);
        printf("%d\n", key);
    }
    else
    {
        printf("-1\n");
    }
}

tree_node_ptr level_search(tree_node_ptr  root, int key, int *cnt)
{
    // if the root is empty then return NULL
    if(root == NULL)
    {
        return NULL;
    }
    tree_node_ptr ptr = root;
    //if key is equal to the current node then return the current node
    if(ptr->data == key)
    {
        return ptr;
    }
    // if the key is less than the current node then go left
    else if(key < ptr->data)
    {
        (*cnt)++;
        return level_search(ptr->left, key, cnt);
    }
    // if the key is greater than the current node then go right
    else if (key > ptr->data)
    {
        (*cnt)++;
        return level_search(ptr->right, key, cnt);
    }
    else
    {
        return NULL;
    }

}
int level(tree_node_ptr root, int key)
{
    int cnt =1;
    tree_node_ptr result = level_search(root, key, &cnt);
    if(result!=NULL)
    {
        return cnt;
    }
    else
    {
        return -1;
    }
}

queue_linked_node_ptr get_parenthesis_notation(tree_node_ptr *   root)
{
    
    char in ;
    char left_bracket  = '(';
    char right_bracket = ')';
    char space = ' ';
    int bracket_cnt =0, digit;
    int flag = 0; // no conituation
    int data =-1;
    int location = -1; // left = -1 or right = 1
    int empty_bracket = 0;
    queue_linked_node_ptr head = NULL;
    do{
        scanf("%c", &in);
        if(in == left_bracket) 
        {   
            bracket_cnt ++;

           
        }
        else if(in == right_bracket)
        {
           bracket_cnt --;
           
            // when right bracked is found in location right (1) then goto parent
        } 
        if (in !=space)
        {
            queue_linked_node_ptr x = queue_linked_create_node(in);
            queue_linked_Enqueue(&head,x);
        }
        
        
    }while(bracket_cnt!=0);
    //queue_linked_print_list(&head);
    return head;
}
tree_node_ptr parenthesis_queue_to_tree(queue_linked_node_ptr queue)
{
    tree_node_ptr root = create_node(INT_MIN);
    char left_bracket  = '(';
    char right_bracket = ')';
    char in, temp;
    tree_node_ptr new_node;
    tree_node_ptr current = root;

    queue_linked_Dequeue(&queue);
    queue_linked_list_delete_last(&queue);
    while (!queue_linked_isEmpty(&queue))
    {
        in  = queue_linked_front(&queue);
        queue_linked_Dequeue(&queue);
        //case 1
        if(in == right_bracket)
        {
            
            tree_node_ptr temp_node_ptr = NULL;
            if (current->data == INT_MIN)//in current is empty
            {
                temp_node_ptr = current;
                current = current->parent;
                if(current->left == temp_node_ptr)
                {
                    current->left = NULL;
                    free(temp_node_ptr);
                }
                else if (current->right == temp_node_ptr)
                {
                    current->right = NULL;
                    free(temp_node_ptr);
                }
                else {
                    printf("error\n");
                }
            }
            else
            {
                current = current->parent;
            }

        }
        //case 3
        else if (in ==left_bracket)
        {
            
            int visited = current->visited;
            if(visited == 0)
            {
                current->visited = 1;
                current->left = create_node(INT_MIN);
                current->left->parent = current;
                current = current->left;
            }
            else if(visited == 1)
            {
                current->visited = 2;
                current->right = create_node(INT_MIN);
                current->right->parent = current;
                current = current->right;
            }
            else if(visited == 2)
            {
                printf("error\n");
            }
        }
        // case 2: integer
        else if(isdigit(in))
        {
            temp = in ;
            int num = INT_MIN;
            while(isdigit(temp))
            {
                if (num== INT_MIN) num = temp - '0';
                else num = num*10 + (temp - '0');
                temp = queue_linked_front(&queue);
                queue_linked_Dequeue(&queue);
            }
            queue_linked_list_insert_front(&queue, queue_linked_create_node(temp));
            if(current->visited==0 && current->data!=INT_MIN)
            {
                current->visited = 1;
                new_node = create_node(INT_MIN);
                new_node->parent = current;
                current->left = new_node;
                current= current->left;
            }
            else if (current->visited==1 && current->data!=INT_MIN)
            {
                current->visited = 2;
                new_node = create_node(INT_MIN);
                new_node->parent = current;
                current->right = new_node;
                current= current->right;
            }
            current->data = num;
        }
    }
    if(root->data == INT_MIN)
    {
        return NULL;
    }
    else
    {
        return root;
    }
}
int isBST(tree_node_ptr current , int lowerbound, int upperbound)
{
    if (current == NULL)
    {
        return 1;
    }
    if(current->data<=lowerbound)
    {
        return 0;
    }
    else if (current->data>=upperbound)
    {
        return 0;
    }
    else
    {
        int is_right_tree_bst =  isBST(current->left, lowerbound, current->data);
        int is_left_tree_bst = isBST(current->right, current->data, upperbound);

        if (is_right_tree_bst && is_left_tree_bst==1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
            
    }
 
    
}
int subtrees_to_delete(tree_node_ptr root )
{
    // if root then delete both childs if they do not satisfy the condition of bst
    if (root == NULL)
    {
        return 0;
    }
    
        
    
    
    
    int left=0, right=0;
    if(root->left)
    {
        left = !isBST(root->left, INT_MIN, root->data);
    }
    if (root->right)
    {
        right = !isBST(root->right, root->data, INT_MAX);
    }
    return left + right;
    
}

// Tree from string 
int main()
{
    tree_node_ptr root = NULL;
    queue_linked_node_ptr queue = get_parenthesis_notation(&root);
    tree_node_ptr tree = parenthesis_queue_to_tree(queue);
    
    int cnt = subtrees_to_delete(tree);
    printf("%d\n", cnt);
    return 0;
}


