/*
2. Write a program to create a Red Black Tree from the given input. After creating the tree, find the
number of Beautiful Nodes in the tree. A Beautiful Node is a node (can be red or black)
which has minimum one black vertex at “X” distance in any direction.

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define INT_MAX  2147483647
typedef long int li;
typedef struct BST_node * BST_node_ptr;


struct BST_node
{
    int data;
    BST_node_ptr parent;
    BST_node_ptr left; // left child less than data
    BST_node_ptr right; // right child greater than data
    int color; // 0 for black, 1 for red
};



BST_node_ptr BST_create_node(int key)
{
    BST_node_ptr new_node = (BST_node_ptr) malloc(sizeof(struct BST_node));
    new_node->data = key;
    new_node->right = NULL;
    new_node->left = NULL;
    new_node->parent = NULL;
    new_node->color = 1; // initially all nodes are red
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


BST_node_ptr BST_get_sucessor_parent (BST_node_ptr root, int data)
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
        BST_node_ptr temp = search_result->right;
        while(temp->parent != NULL)
        {
            if(temp->parent->left == temp)
            {
                return temp->parent;
            }
            temp = temp->parent;
        }

        
    }
    else
    {
        return NULL;
    }
    return NULL;
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


BST_node_ptr Insert(BST_node_ptr  root, int key)
{

    if(root ==NULL)
    {
        BST_node_ptr new_node = BST_create_node(key);
        new_node->parent = NULL;
        return new_node;
    }
    if(root->data > key)
    {
        root->left = Insert(root->left, key);
        if (root->left!=NULL)
        {
            root->left->parent = root;
        }
        
    }
    else if (root->data < key)
    {
        root->right = Insert(root->right, key);
        if (root->right!=NULL)
        {
            root->right->parent = root;
        }
        
    }
    else return root;
    
    int balance_factor; 
    int flag = 0;
    if  (root!=NULL) 
    {
        if (root->data == key) flag = 1;
        balance_factor = BST_height(root->left) - BST_height(root->right);
        
        if(balance_factor>1) // left child of root is heavier 
        {
            if(root->left!=NULL &&  root->left->data  > key)//LL
            {
                return  rightRotate(root);
            }
            else // LR
            {
                root->left = leftRotate(root->left);
                if (root->left!=NULL)
                {
                    root->left->parent = root;
                }
                return  rightRotate(root);
            }

         
     
        }
        else if(balance_factor<-1) // right  child of root is heavier 
        {
            if(root->right!=NULL &&  root->right->data < key) //RR
            {
                return  leftRotate(root);
            }
            else // RL
            {
                root ->right = rightRotate(root->right);
                if (root->right!=NULL)
                {
                    root->right->parent = root;
                }
                return  leftRotate(root);
            }
     
        }

        
        
    }
    return root;
    
}

BST_node_ptr balance(BST_node_ptr current )
{
    if (current == NULL)
    {
        return current;
    }
    if (current->left != NULL)
    {
        current->left = balance(current->left);
    }
    if (current->right != NULL)
    {
        current->right = balance(current->right);
    }

    int left_height = BST_height(current->left);
    int right_height = BST_height(current->right);
    int balance_factor = left_height - right_height;
    if(balance_factor>1) // left child of root is heavier 
    {
        if(current->left!=NULL &&  current->left->left!=NULL) //LL
        {
            return  rightRotate(current);
        }
        else  if (current->left != NULL && current -> left ->right != NULL) // LR
        {
            current->left = leftRotate(current->left);
            return  rightRotate(current);
        }

     
    }
    else if(balance_factor<-1) // right  child of root is heavier 
    {
        if(current->right!=NULL &&  current->right->right!=NULL) //RR
        {
            return  leftRotate(current);
        }
        else if (current->right!=NULL && current->right->left!=NULL)// RL
        {
            current ->right = rightRotate(current->right);
            return  leftRotate(current);
        }
        
     
    }
    return current;
    
    
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
    if (root->color == 1)
    {
        printf("R ");
    }
    else
    {
        printf("B ");
    }
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

void AVL_Tree_Delete(BST_node_ptr * root, int key){
    
    
    
    // if root is NULL
    if(*root == NULL)
    {
        return;
    }
    // if root is is to be deleted is the root and a leaf node
    if(key == (*root)->data && (*root)->left == NULL && (*root)->right == NULL)
    {
        free(*root);
        *root = NULL;
        return;
}
    BST_node_ptr search_result = BST_search(*root, key);
    if (search_result!=NULL)
    {
        // if node to be deleted is leaf node
        if(search_result->left == NULL && search_result->right == NULL)
        {
            if(search_result->parent->left == search_result)
            {
                search_result->parent->left = NULL;
            }
            else
            {
                search_result->parent->right = NULL;
            }
            free(search_result);
        }    
        // if node to be deleted has only one child
        else if(search_result->left == NULL || search_result->right == NULL)
        {
            BST_node_ptr child = search_result->left;
            if(search_result->left == NULL)
            {
                child = search_result->right;
            }
            if(search_result->parent->left == search_result)
            {
                search_result->parent->left = child;
            }
            else
            {
                search_result->parent->right = child;
            }

            child->parent = search_result->parent;
            free(search_result);

        }

        // if node to be deleted has two children
        else
        {
            BST_node_ptr successor = BST_get_sucessor_parent(*root,key);
            int temp = search_result->data;
            search_result->data = successor->data;

            successor->data = temp;
            AVL_Tree_Delete(root, temp);
        }


    }
    else
    {
        printf("FALSE\n");
    }

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
        AVL_Tree_Delete(root, key);
    }
    else
    {
        printf("FALSE\n");
    }
    
}

BST_node_ptr RedBlackTree_Fix(BST_node_ptr new_node)
{
    BST_node_ptr temp_root  = new_node;
    while(temp_root->parent!=NULL)
    {
        temp_root = temp_root->parent;
    }

    
    
    while(new_node->parent!=NULL && new_node->parent->color == 1)// while parent of the  new node is red
    {
        // if the new node's parent is the left child of its parent (grandparent of new node) three cases arise
       
            
             if(new_node->parent== new_node->parent->parent ->right)
            {
                // if the color of the left child of the grandparent is  red  set the bolor of both children of the grandparent to black and set the color of the grandparent to red
                if(new_node->parent->parent ->left!=NULL && new_node->parent->parent ->left->color == 1)
                {
                    new_node->parent->parent->color = 1;
                    new_node->parent->parent->left->color = 0;
                    if(new_node->parent->parent->right!=NULL)new_node->parent->parent->right->color = 0;
                    // Assigning grandparent to new node
                    new_node = new_node->parent->parent ;
                    
                    
                    
                    

                }
                else
                {

                    // else if new node is left child of parent  then assign  parent to new node and right rotate new node
                    if (new_node == new_node->parent->left)
                    {
                        new_node= new_node->parent;
                        rightRotate(new_node);
                        

                    }  
                    // set the color of parent as black and grandoarent as red
                    new_node->parent->color = 0;
                    if(new_node->parent->parent !=NULL)new_node->parent->parent ->color = 1;
                    // left rotate grandparnt 
                    leftRotate(new_node->parent->parent );
                    
                    
                    
                    
                }

            }
            

            // if parent is the left child of grandparent
            else if (new_node->parent== new_node->parent->parent ->left)
            {
                // Case one : if the color of the right child of the grandparent is red then  set the color of both children of the grandparent to black and set the color of the grandparent to red
            
                if(new_node->parent->parent ->right!=NULL && new_node->parent->parent ->right->color == 1)
                {
                    new_node->parent->parent ->color = 1;
                    new_node->parent->parent ->right->color = 0;
                    if(new_node->parent->parent ->left!=NULL)new_node->parent->parent ->left->color = 0;
                    // Assigning grandparent to new node
                    new_node = new_node->parent->parent ;
                    
                   
                }
                else
                {

                    // Case two if new node is the right child of its parent then assign parent to new node
                    if(new_node == new_node->parent->right)
                    {
                    
                        new_node= new_node->parent;
                        leftRotate(new_node);
                        
                        

                        
                    }
                    // Case three :  else  set  color or parent as black and color of grandparent as red and then right rotate gradparent
                
                    new_node->parent->color = 0;
                    if(new_node->parent->parent !=NULL)new_node->parent->parent ->color = 1;
                    rightRotate(new_node->parent->parent );
                    
                    
                    
                }
            }
           
        //}   
        if (new_node==temp_root)
        {
            break;
        }

        
    }
    // setting root color to black
    temp_root  = new_node;
    while(temp_root->parent!=NULL)
    {
        temp_root = temp_root->parent;
    }
    temp_root->color = 0;
    return temp_root;
}


   


     
/*
Properties of red black tree. 
1) Every node is either red or black.
2) The root is black.
3) All leaves are black. (NULL leaves are considered as leaves)
4) There cannot be two adjacent red nodes. (means parent and child of a red node are both black)
5) Every path from a given node to any of its descendant leaves contains the same number of black nodes.

*/
BST_node_ptr InsertRedBlack( BST_node_ptr root , int key)
{
    // a new node is always inserted as a red node
    /*
    After normal insertion if the tree violates the properties of a red black tree,
    then the tree is rebalanced using the following steps.
    1)  Recolor 
    2)  Rotate
    */

    BST_node_ptr new_node = BST_create_node(key);
   // if root is empty 
   if ((root)==NULL)
   {
         new_node->color = 0; // root is always black
         (root) = new_node;
         return new_node;
   }


    BST_node_ptr current = (root);
    // normal insertion of a node, note that new node is always red
   while(current!=NULL)
   {
         if(key < current->data)
         {
              if(current->left!=NULL)current = current->left;
              else{
                    current->left = new_node;
                    new_node->parent = current;
                    break;
              }
         }
         else if(key > current->data)
         {
              if(current->right!=NULL)current = current->right;
              else{
                    current->right = new_node;
                    new_node->parent = current;
                    break;
                }
         }   
         else if (key == current->data)
         {
             
             return root;
         }      
   }
    if (new_node->parent->parent==NULL)
    {
        return new_node->parent;
    }
    
    // if the tree violates the properties of a red black tree, then the tree is rebalanced using the following steps.
    
    return RedBlackTree_Fix(new_node);
    

}


int inputHandler(int * stop_flag)
{
    

    char c;
    scanf("%c", &c);
    if (c=='t'){
        *stop_flag = 1;
        return INT_MAX;
    }
  
    
    int flag = 0;
    int data =0;

    if(c == '\0') {
        *stop_flag = 1;
        return INT_MAX;
    }
    while(c!='\n')
    {
        
        if(c==' ')
        {
            
            flag = 0;
            return data;
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
    
    return data;
    
}
int isBeautifulNode(BST_node_ptr current, BST_node_ptr prev,int x)
{
    if (current==NULL)
    {
        return 0;
    }
    if ( x == 0 && current -> color ==0)
    {
        return 1;
    }
    int left = 0 , right = 0 , parent = 0;
    if(current->left != prev)left = isBeautifulNode(current->left, current,x-1);
    if(current->right != prev)right = isBeautifulNode(current->right, current, x-1);
    if(current->parent != prev)parent = isBeautifulNode(current->parent,current, x-1);
    return left+right+parent;
}
int numberOfBeautifulNodes(BST_node_ptr current, int x)
{
    if (current==NULL)
    {
        return 0;
    }
    int beautiful = isBeautifulNode(current, NULL, x);
    if(beautiful>0)
    {
        return 1+numberOfBeautifulNodes(current->left, x)+numberOfBeautifulNodes(current->right, x);
    }
    else
    {
        return numberOfBeautifulNodes(current->left, x)+numberOfBeautifulNodes(current->right, x);
    }
}

int main()
{
    int x,n,data;
    scanf("%d",&x);
    scanf("%d",&n);
    
    BST_node_ptr root = NULL; // initalizing head to null
    while(n--)
    {
       
        
        scanf("%d",&data);
        root = InsertRedBlack(root,data);

        

       
    }
    printf("%d\n",numberOfBeautifulNodes(root, x));
	return 0;
}
