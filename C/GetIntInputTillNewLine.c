

// replace tree_node_ptr with desired output pointer array type
// subsitute root with linked list or array and insert operation accordingly
tree_node_ptr take_in_Tree()
{
    char c;
    tree_node_ptr root = NULL;
    scanf("%c", &c);
    int flag = 0;
    int data =0;
    if(c == '\0') return NULL;
    while(c!='\n')
    {
        
        if(c==' ')
        {
            
            flag = 0;
            insert(&root, data);
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
    if(data!=0)
    {
        insert(&root, data);
    }
    return root;
}
