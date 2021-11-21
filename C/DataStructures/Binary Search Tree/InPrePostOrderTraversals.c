
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