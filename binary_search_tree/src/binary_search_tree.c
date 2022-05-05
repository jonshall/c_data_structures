/**
 * @file   binary_search_tree.c
 * @author Jon S Hall
 * @brief  binary search tree
 * @date   December 2021
 */

#include <binary_search_tree.h>

/**
 * @references:
 * https://www.codesdope.com/blog/article/binary-search-tree-in-c/
 * https://www.programiz.com/dsa/tree-traversal
 * https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
 * https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
 * https://www.geeksforgeeks.org/write-a-c-program-to-delete-a-tree/
 */

node_t *
bst_create(void *data)
{
    node_t *bst = { 0 };

    // check input
    if (NULL == data)
    {
        fprintf(stderr, "ERROR: Null passed to bst create\n");
        goto FAIL;
    }

    // calloc bst
    if (NULL == (bst = calloc(1, sizeof(node_t))))
    {
        fprintf(stderr, "ERROR: Calloc failed create bst\n");
        goto FAIL;
    }

    // assign defaults
    bst->data  = data;
    bst->left  = NULL;
    bst->right = NULL;

    debug_print(("--------------------------------------------\n"));
    debug_print(("bst_create: bst created\n"));
    debug_print(("--------------------------------------------\n"));

    goto END;

FAIL:
    bst = NULL;

END:
    return (bst);
}

node_t *
bst_new_node(void *data)
{
    node_t *node = { 0 };

    // check input
    if (NULL == data)
    {
        fprintf(stderr, "ERROR: Null passed to bst new node\n");
        goto FAIL;
    }

    // calloc node
    if (NULL == (node = calloc(1, sizeof(node_t))))
    {
        fprintf(stderr, "ERROR: Calloc failed create new node\n");
        goto FAIL;
    }

    // assign defaults
    node->data  = data;
    node->left  = NULL;
    node->right = NULL;

    goto END;

FAIL:
    if (NULL != node)
    {
        free(node);
        node = NULL;
    }

END:
    return (node);
}

node_t *
bst_insert(node_t *node, void *item)
{
    // check input
    if (NULL == item)
    {
        fprintf(stderr, "ERROR: Null passed to bst insert\n");
        goto END;
    }

    // insert node as bst if tree is empty
    if (NULL == node)
    {
        node = bst_new_node(item);
        debug_print(("bst_insert: new bst node\n"));
        debug_print(("--------------------------------------------\n"));
        goto END;
    }

    // traverse to correct place and insert node
    if (item < node->data)
    {
        node->left = bst_insert(node->left, item);
        debug_print(("bst_insert: looking left\n"));
        debug_print(("--------------------------------------------\n"));
    }
    else if (item > node->data)
    {
        node->right = bst_insert(node->right, item);
        debug_print(("bst_insert: looking right\n"));
        debug_print(("--------------------------------------------\n"));
    }

END:
    return (node);
}

node_t *
bst_find(node_t *bst, void *item)
{
    node_t *node = { 0 };

    // set node to bst of bst
    node = bst;

    // check input
    if ((NULL == bst) || (NULL == item))
    {
        fprintf(stderr, "ERROR: Null passed to bst find\n");
        goto END;
    }

    // if node is bst
    if (item == node->data)
    {
        debug_print(("bst_find: node is root\n"));
        goto END;
    }
    // item is greater, so we will go to the right subtree
    else if (item > node->data)
    {
        return bst_find(node->right, item);
    }
    // item is smaller than the data, so we will bst_find the left subtree
    else
    {
        return bst_find(node->left, item);
    }

FAIL:
    node = NULL;

END:
    return (node);
}

node_t *
bst_remove(node_t *bst, void *item)
{
    node_t *current = { 0 };
    node_t *prev    = { 0 };
    node_t *temp    = { 0 };
    node_t *order   = { 0 };

    current = bst;

    // check if the item is present in the bst
    while ((NULL != current) && (item != current->data))
    {
        prev = current;
        if (item < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (NULL == current)
    {
        debug_print(("bst_remove: node not found in bst\n"));
        goto EXIT;
    }

    // check if node to be deleted has one child.
    if (current->left == NULL || current->right == NULL)
    {
        // temp will replace the node to be deleted

        // if the left child does not exist
        if (NULL == current->left)
        {
            temp = current->right;
        }
        else
        {
            temp = current->left;
        }

        // check if the node to be deleted is the root.
        if (NULL == prev)
        {
            bst = temp;
            goto EXIT;
        }

        if (current == prev->left)
        {
            prev->left = temp;
        }
        else
        {
            prev->right = temp;
        }

        // free and null the node to be deleted
        free(current);
        current = NULL;
    }
    // node to be deleted has two children
    else
    {
        // compute the inorder successor
        temp = current->right;

        while (NULL != temp->left)
        {
            order = temp;
            temp  = temp->left;
        }

        if (NULL != order)
        {
            order->left = temp->right;
        }
        // if current = the matches data to delete
        else
        {
            current->right = temp->right;
        }

        current->data = temp->data;

        free(temp);
        temp = NULL;
    }

EXIT:
    return (bst);
}

int
bst_destroy(node_t *bst)
{
    int status = BST_SUCCESS;

    node_t *temp = NULL;

    temp = bst;

    // check input
    if (NULL == temp)
    {
        debug_print(("bst node is NULL\n"));
        goto END;
    }

    bst_destroy(temp->left);
    bst_destroy(temp->right);

    if (NULL != bst)
    {
        free(bst);
        bst = NULL;
    }

    goto END;

FAIL:
    status = BST_FAIL;

END:
    return (status);
}

void
bst_inorder(node_t *bst)
{
    // checking if the bst is not null
    if (NULL != bst)
    {
        // visiting left child
        bst_inorder(bst->left);

        // printing data at bst
        fprintf(stdout, " %ls ", (int *)bst->data);

        // visiting right child
        bst_inorder(bst->right);
    }
}

// function to find the minimum value in a node
node_t *
bst_min(node_t *node)
{
    if (NULL == node)
    {
        fprintf(stderr, "ERROR: Null passed to find min\n");
        goto EXIT;
    }
    // node with minimum value will have no left
    else if (NULL != node->left)
    {
        // left most element will be minimum
        node = bst_min(node->left);
    }

EXIT:
    return (node);
}
