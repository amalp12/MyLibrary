#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
typedef long int li;
typedef struct tree_node * tree_node_ptr;


struct tree_node
{
    int data;
    tree_node_ptr left; // left child less than data
    tree_node_ptr right; // right child greater than data
};



tree_node_ptr create_node(int key)
{
    tree_node_ptr new_node = (tree_node_ptr) malloc(sizeof(struct tree_node));
    new_node->data = key;
    new_node->right = NULL;
    new_node->left = NULL;
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
int main()
{
    char in; int data;
    tree_node_ptr root = NULL,x,y; // initalizing head to null
    while(1)
    {
        scanf(" %c", &in);
        //  ‘a’, ‘d’, ‘s’, ‘c’, ‘r’, ‘i’, ‘p’, ‘t’, or ‘e’
        switch (in)
        {
            case 'a':

                scanf(" %d", &data);
                insert(&root, data);
                
                
                break;
            
            case 'd':
                scanf(" %d", &data);
                delete(&root, data);
                break;

            case 's':
                scanf(" %d", &data);
                tree_node_ptr search_result= search(root, data);
                if (search_result != NULL)
                {
                    printf("1\n");
                }
                else
                {
                    printf("-1\n");
                }
                break;

            case 'c':
                scanf(" %d", &data);
                sucessor(root, data);
                
                break;
            case 'r':
                scanf(" %d", &data);
                predecessor(root, data);

                break;
            case 'i':
                inorder(root);
                printf("\n");
                
                break;
            case 'p':
                preorder(root);
                printf("\n");

                break;
           
           
            case 't':
                postorder(root);
                printf("\n");
                break;

            case 'e':
                return 0;
                break;

            default:
                break;
        }
    }
	return 0;
}

