#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INT_MAX  2147483647
typedef long int li;
typedef struct BST_node * BST_node_ptr;


struct BST_node
{
    int data;
    BST_node_ptr left; // left child less than data
    BST_node_ptr right; // right child greater than data
};



BST_node_ptr BST_create_node(int key)
{
    BST_node_ptr new_node = (BST_node_ptr) malloc(sizeof(struct BST_node));
    new_node->data = key;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

void BST_insert_node(BST_node_ptr root, BST_node_ptr new_node)
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
            BST_insert_node(root->left, new_node); // pass by memory
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
            BST_insert_node(root->right, new_node); // pass by memory
        }
    }
    else// if the new node is equal to the current node then do nothing
    {
        return;
    }
}
BST_node_ptr BST_search(BST_node_ptr  root, int key)
{
    // if the root is empty then return NULL
    if(root == NULL)
    {
        return NULL;
    }
    BST_node_ptr ptr = root;
    //if key is equal to the current node then return the current node
    if(ptr->data == key)
    {
        return ptr;
    }
    // if the key is less than the current node then go left
    else if(key < ptr->data)
    {
        return BST_search(ptr->left, key);
    }
    // if the key is greater than the current node then go right
    else if (key > ptr->data)
    {
        return BST_search(ptr->right, key);
    }
    else
    {
        return NULL;
    }

}
BST_node_ptr BST_get_parent( BST_node_ptr root, BST_node_ptr child)
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
        return BST_get_parent(root->left, child);
    }
    // if the right child is not empty then recursively call the function get parent towards right
    else if(child->data >root->data)
    {
        return BST_get_parent(root->right, child);
    }
    
}

BST_node_ptr BST_get_sucessor(BST_node_ptr root, int data)
{

    BST_node_ptr search_result = BST_search(root, data);
    if(search_result!=NULL)
    {
        // if right subtree not null then  sucessor will be the leftmost child of hte right subtree or right child itself
        if(search_result->right != NULL)
        {
            BST_node_ptr temp = search_result->right; ;
            while(temp->left != NULL)
            {
                temp = temp->left;
            }
            if (temp->data < search_result->data) return NULL;
            return temp;
        }
        else // if right subtree is null sucessor will be the last left child's parent while searching the current node
        {
            BST_node_ptr sucessor= root;
            BST_node_ptr temp = root;
            while(temp->data != search_result->data)
            {
                if (search_result->data > temp->data)
                {
                    temp = temp->right;
                }
                else
                {
                    sucessor = temp;
                    temp = temp->left;
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



BST_node_ptr BST_get_predecessor(BST_node_ptr root, int data)
{
  


    BST_node_ptr search_result = BST_search(root, data);
    if(search_result!=NULL)
    {
        // if left subtree not null then  sucessor will be the rightmost child of hte left subtree or left child itself
        if(search_result->left != NULL)
        {
            BST_node_ptr temp = search_result->left; 
            while(temp->right != NULL)
            {
                temp = temp->right;
            }
            if (temp->data > search_result->data) return NULL;
            return temp;
        }
        else // if left subtree is null sucessor will be the last right child's parent while searching the current node
        {
            BST_node_ptr predecessor = root;
            BST_node_ptr temp = root;
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

void BST_delete_node(BST_node_ptr * root, int key)
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
    BST_node_ptr search_result = BST_search(*root, key);
    if(search_result != NULL)
    {
        BST_node_ptr parent = BST_get_parent(*root, search_result);

        // if parent is null then that means root node is to be deleted
        if (parent==NULL)
        {
            BST_node_ptr sucessor = BST_get_sucessor(*root, key);
            if(sucessor != NULL)
            {
                int temp = sucessor->data;
                BST_delete_node(root, sucessor->data);
                search_result->data = temp;
            }
            else
            {
                BST_node_ptr predecessor = BST_get_predecessor(*root, key);        
                int temp = predecessor->data;
                BST_delete_node(root, predecessor->data);
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
            BST_node_ptr successor = BST_get_sucessor( *root, search_result->data );
            int temp_data = successor->data;
            BST_delete_node (root, successor->data);
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

void BST_preorder(BST_node_ptr  current_node)
{
    if(current_node == NULL)
    {
        return;
    }

    printf("%d ", current_node->data);
    BST_preorder(current_node->left);
    BST_preorder(current_node->right);
}

void BST_postorder(BST_node_ptr  current_node)
{
    if(current_node == NULL)
    {
        return;
    }

    BST_postorder((current_node->left));
    BST_postorder((current_node->right));
    printf("%d ", current_node->data);
}


void BST_inorder(BST_node_ptr current_node)
{
    if(current_node == NULL)
    {
        return;
    }

    BST_inorder((current_node->left));
    printf("%d ", current_node->data);
    BST_inorder((current_node->right));
}
void BST_insert(BST_node_ptr * root, int key)
{
    // if the root is empty then create a new node
    if(*root == NULL)
    {
        (*root) = BST_create_node(key);
        return;
    }
    BST_node_ptr new_node = BST_create_node(key);
    BST_insert_node(*root, new_node);
}
void BST_sucessor(BST_node_ptr root, int data)
{
    BST_node_ptr sucessor = BST_get_sucessor(root, data);
    if(sucessor!=NULL)
    {
        printf("%d\n", sucessor->data);
    }
    else
    {
        printf("-1\n");
    }
}

void BST_predecessor(BST_node_ptr root, int data)
{
    BST_node_ptr predecessor = BST_get_predecessor(root, data);
    if(predecessor!=NULL)
    {
        printf("%d\n", predecessor->data);
    }
    else
    {
        printf("-1\n");
    }
}

void BST_delete(BST_node_ptr * root, int key)
{
    BST_node_ptr search_result = BST_search(*root, key);
    if (search_result!=NULL)
    {
        BST_delete_node(root, key);
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
    BST_node_ptr root = NULL,x,y; // initalizing head to null
    while(1)
    {
        scanf(" %c", &in);
        //  ‘a’, ‘d’, ‘s’, ‘c’, ‘r’, ‘i’, ‘p’, ‘t’, or ‘e’
        switch (in)
        {
            case 'a':

                scanf(" %d", &data);
                BST_insert(&root, data);
                
                
                break;
            
            case 'd':
                scanf(" %d", &data);
                BST_delete(&root, data);
                break;

            case 's':
                scanf(" %d", &data);
                BST_node_ptr search_result= BST_search(root, data);
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
                BST_sucessor(root, data);
                
                break;
            case 'r':
                scanf(" %d", &data);
                BST_predecessor(root, data);

                break;
            case 'i':
                BST_inorder(root);
                printf("\n");
                
                break;
            case 'p':
                BST_preorder(root);
                printf("\n");

                break;
           
           
            case 't':
                BST_postorder(root);
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
