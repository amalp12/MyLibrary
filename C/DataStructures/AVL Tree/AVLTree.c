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
    BST_node_ptr parent;
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
            new_node->parent = root;
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
            new_node->parent = root;
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


BST_node_ptr BST_get_sucessor (BST_node_ptr root, int data)
{

    BST_node_ptr search_result = BST_search(root, data);
    if(search_result!=NULL)
    {
        // if  rights subtree is not empty then return the minimum value of the right subtree
        if(search_result->right != NULL)
        {
            BST_node_ptr temp = search_result->right;
            while(temp->left != NULL)
            {
                temp = temp->left;
            }
            return temp;
        }

        // if the right subtree is null then the sucessors lies above in among the parents 
        // travel up using parent pointer until we see a node which is left child of parent
        BST_node_ptr temp = search_result->parent;
        while(temp->parent != NULL)
        {
            if(temp->parent->left == temp)
            {
                return temp->parent;
            }
            temp = temp->parent;
        }
        return temp;

        
    }
    else
    {
        return NULL;
    }
}


BST_node_ptr BST_get_predecessor (BST_node_ptr root, int data)
{

    BST_node_ptr search_result = BST_search(root, data);
    if(search_result!=NULL)
    {
        // if  left subtree is not empty then return the maximum value of the left subtree
        if(search_result->left != NULL)
        {
            BST_node_ptr temp = search_result->left;
            while(temp->right != NULL)
            {
                temp = temp->right;
            }
            return temp;
        }

        // if the left subtree is null then the predecessor lies above in among the parents 
        // travel up using parent pointer until we see a node which is right child of parent
        BST_node_ptr temp = search_result->parent;
        while(temp->parent != NULL)
        {
            if(temp->parent->right == temp)
            {
                return temp->parent;
            }
            temp = temp->parent;
        }
        return temp;

        
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
        BST_node_ptr parent = search_result->parent;

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
        printf("FALSE\n");
    }
}

int BST_height(BST_node_ptr root)
{
    if(root == NULL)
    {
        return 0;
    }
    else
    {
        int left_height = BST_height(root->left);
        int right_height = BST_height(root->right);
        if(left_height > right_height)
        {
            return left_height + 1;
        }
        else
        {
            return right_height + 1;
        }
    }
}
int  getBalanceFactor(BST_node_ptr current)
{
   
    
    int left_height = BST_height(current->left);
    int right_height = BST_height(current->right);
    int balance_factor = left_height - right_height;
    return balance_factor;
 
   
}


void  getBalance(BST_node_ptr root, int key)
{
   
    BST_node_ptr search_result = BST_search(root, key);
    if( search_result!=NULL)
    {
        int left_height = BST_height(search_result->left);
        int right_height = BST_height(search_result->right);
        int balance_factor = left_height - right_height;
        printf("%d\n",balance_factor);
    }
    else 
    {
        printf("FALSE\n");
    }
   
}


/*
T1, T2 and T3 are subtrees of the tree 
rooted with y (on the left side) or x (on 
the right side)           
     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3
Keys in both of the above trees follow the 
following order 
 keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
So BST property is not violated anywhere.
*/

BST_node_ptr rightRotate(BST_node_ptr y)
{
    // root is y
    BST_node_ptr x = y->left;
    BST_node_ptr T3 = y->right;

    if(x!=NULL)
    {
        
        BST_node_ptr T1 = x->left;
        BST_node_ptr T2 = x->right;

        // perform rotation
        
        x->left = T1;
        if(T1!=NULL)T1->parent = x;
        y->left = T2;
        if(T2!=NULL)T2->parent = y;
        y->right = T3;
        if(T3!=NULL) T3->parent = y;


        x->parent = y->parent;
        y->parent = x;
        x->right = y;


        // if the parent has has parent
        if(x->parent!=NULL)
        {
            if(x->parent->left == y)
            {
                x->parent->left = x;
            }
            else if(x->parent->right == y)
            {
                x->parent->right = x;
            }
        }


    }
    else
    {
        printf("error!\n");
    }

    return x;
}

BST_node_ptr leftRotate(BST_node_ptr x)
{
    // root is x

    BST_node_ptr y = x->right;
    BST_node_ptr T1 = x->left;

    if(y!=NULL)
    {
        BST_node_ptr T2 = y->left;
        BST_node_ptr T3 = y->right;

        // perform rotation
        if(T3!=NULL)T3->parent = y;
        y->right = T3;

        if(T2!=NULL)T2->parent = x;
        x->left = T1;
        if(T1!=NULL)T1->parent = x;
        x->right = T2;

        

        y->parent = x->parent;
        x->parent = y;
        y->left = x;

        // if the parent has a parent
        if(y->parent!=NULL)
        {
            if(y->parent->left == x)
            {
                y->parent->left = y;
            }
            else
            {
                y->parent->right = y;
            }
        }


    }
    else
    {
        printf("error!\n");
    }

    return y;
}

BST_node_ptr AVL_Tree_Insert_Fix(BST_node_ptr new_node)
{
    BST_node_ptr temp_root  = new_node;
    while(temp_root->parent!=NULL)
    {
        temp_root = temp_root->parent;
    }

    int balance_factor; 
        
    do
    {
        // calculating balace factor
        balance_factor = BST_height(new_node->left) - BST_height(new_node->right);
        // if the new node's parent is the left child of its parent (grandparent of new node) three cases arise
       
        // right chlld is heavier than left child
        if(balance_factor <-1)
        {
            if(new_node->right != NULL)
            {
                if(new_node->right->left != NULL)
                {
                    rightRotate(new_node->right);
                }
                
                new_node = leftRotate(new_node);
                
            }

        }
        

        // right chlld is heavier than left child
        else if (balance_factor>1)
        {
                if(new_node->left != NULL)
            {
                if(new_node->left->right != NULL)
                {
                    leftRotate(new_node->left);
                }
                
                new_node = rightRotate(new_node);
                
            }
        }
           
         
        
        new_node = new_node->parent;

        
    }while(new_node->parent !=NULL );
    return new_node;   
}
BST_node_ptr Insert( BST_node_ptr node , int key)
{
    // Normal BST insertion
    if (node == NULL)
        return(BST_create_node(key));
 
    if (key < node->data)
        node->left  = Insert(node->left, key);
    else if (key > node->data)
        node->right = Insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 

    int balance = getBalanceFactor(node);
 
    // If this node becomes unbalanced, then balamce it
 
    
    if (balance > 1 )
    {
        if(getBalanceFactor(node->left) < 0) node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
   
    if (balance < -1  )
    {
        if(getBalanceFactor(node->right) > 0) node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
 
    /* return the (unchanged) node pointer */
    return node;
}
// parenthesis notation code start

void parenthesisNotation(BST_node_ptr root)
{
    if(root==NULL)
    {
        printf("( )");
        return;
    }


    printf("( ");
    printf("%d ", root->data);
    int flag = 0;
    if(root->left!=NULL)
    {
        parenthesisNotation(root->left);
    }
    else
    {
        printf("( ) ");
        flag=1;
    }
    if(root->right!=NULL)
    {
        parenthesisNotation(root->right);
    }
    else
    {
        printf("( ) ");
    }
    printf(") ");
    
}

BST_node_ptr Search(BST_node_ptr root, int key)
{
    return BST_search(root, key);
}
// parenthesis notation code end



BST_node_ptr minValueNode(BST_node_ptr node)
{
    BST_node_ptr current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

BST_node_ptr maxValueNode(BST_node_ptr node)
{
    BST_node_ptr current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->right != NULL)
        current = current->right;
 
    return current;
}
BST_node_ptr AVL_Tree_Delete(BST_node_ptr root, int key){
    
    
    // Normall BST deletion
 
    if (root == NULL)
        return root;
 
    
    if ( key < root->data )
        root->left = AVL_Tree_Delete(root->left, key);
 
    
    else if( key > root->data )
        root->right = AVL_Tree_Delete(root->right, key);
 
    // found the node
    else
    {
        // node with only one child or 
        if( (root->left == NULL) || (root->right == NULL) )
        {
            BST_node_ptr temp = root->left ;
            if (temp == NULL)
            {
                temp = root->right;
            }
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp;
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            BST_node_ptr temp = maxValueNode(root->left);
 
            // Copy the inorder successor's data to this node
            root->data = temp->data;
 
            // Delete the inorder successor
            root->left = AVL_Tree_Delete(root->left, temp->data);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    
    int balance = getBalanceFactor(root);
 
    
 
    
    if (balance > 1 )
    {
        if(getBalanceFactor(root->left) < 0) root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
   
    if (balance < -1  )
    {
        if(getBalanceFactor(root->right) > 0) root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
   
}

void PrintTree(BST_node_ptr root)
{
    parenthesisNotation(root);
    printf("\n");
}

void DeleteNode(BST_node_ptr * root, int key)
{
    BST_node_ptr search_result = BST_search(*root, key);
    if (search_result!=NULL)
    {
        printf("%d\n", search_result->data);
        (*root)=AVL_Tree_Delete(*root, key);
    }
    else
    {
        printf("FALSE\n");
    }
    
}
int main()
{
    char in; int data;
    BST_node_ptr root = NULL,x,y; // initalizing head to null
    while(1)
    {
        scanf("%c", &in);
        //  ‘i’, ‘d’, ‘s’, ‘b’, ‘p’ and ‘e’
        switch (in)
        {
            case 'i':

                scanf("%d", &data);
                root = Insert(root, data);
                break;
            
            case 'd':
                scanf("%d", &data);
                DeleteNode(&root, data);
                break;

            case 's':
                scanf("%d", &data);
                BST_node_ptr search_result= Search(root, data);
                if (search_result != NULL)
                {
                    printf("TRUE\n");
                }
                else
                {
                    printf("FALSE\n");
                }
                break;
    
            case 'b':
                scanf("%d", &data);
                getBalance(root, data);
                break;

            case 'p':
                PrintTree(root);
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
