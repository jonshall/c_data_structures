/**
 * @file   tree.c
 * @author Jon S Hall
 * @brief  search tree
 * @date   December 2021
 */

#include <tree.h>

/**
 * @references:
 * https://www.programiz.com/dsa/binary-tree
 */

node_t *
tree_create(void *data)
{
    node_t *tree = { 0 };

    // check input
    if (NULL == data)
    {
        fprintf(stderr, "ERROR: Null passed to tree create\n");
        goto FAIL;
    }

    // calloc tree
    if (NULL == (tree = calloc(1, sizeof(node_t))))
    {
        fprintf(stderr, "ERROR: Calloc failed create tree\n");
        goto FAIL;
    }

    // assign defaults
    tree->data  = data;
    tree->left  = NULL;
    tree->right = NULL;

    debug_print(("--------------------------------------------\n"));
    debug_print(("tree_create: tree created\n"));
    debug_print(("--------------------------------------------\n"));

    goto END;

FAIL:
    tree = NULL;

END:
    return (tree);
}

node_t *
tree_new_node(void *data)
{
    node_t *node = { 0 };

    // check input
    if (NULL == data)
    {
        fprintf(stderr, "ERROR: Null passed to tree new node\n");
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
tree_insert(node_t *node, void *item)
{
    // check input
    if (NULL == item)
    {
        fprintf(stderr, "ERROR: Null passed to tree insert\n");
        goto END;
    }

    // insert node as tree if tree is empty
    if (NULL == node)
    {
        node = tree_new_node(item);
        debug_print(("tree_insert: new tree node\n"));
        debug_print(("--------------------------------------------\n"));
        goto END;
    }

    // traverse to correct place and insert node
    if (NULL == node->left)
    {
        node->left = tree_insert(node->left, item);
        debug_print(("tree_insert: looking left\n"));
        debug_print(("--------------------------------------------\n"));
    }
    else if (NULL == node->right)
    {
        node->right = tree_insert(node->right, item);
        debug_print(("tree_insert: looking right\n"));
        debug_print(("--------------------------------------------\n"));
    }

END:
    return (node);
}

node_t *
tree_find(node_t *tree, void *item)
{
    node_t *node = { 0 };

    // set node to tree of tree
    node = tree;

    // check input
    if ((NULL == tree) || (NULL == item))
    {
        fprintf(stderr, "ERROR: Null passed to tree find\n");
        goto END;
    }

    // if node is tree
    if (item == node->data)
    {
        debug_print(("tree_find: node is tree\n"));
        goto END;
    }
    // item is greater, so we will go to the right subtree
    else if (item > node->data)
    {
        return tree_find(node->right, item);
    }
    // item is smaller than the data, so we will tree_find the left subtree
    else
    {
        return tree_find(node->left, item);
    }

FAIL:
    node = NULL;

END:
    return (node);
}

int
tree_destroy(node_t *tree)
{
    int status = TREE_SUCCESS;

    node_t *temp = NULL;

    temp = tree;

    // check input
    if (NULL == temp)
    {
        debug_print(("tree node is NULL\n"));
        goto END;
    }

    tree_destroy(temp->left);
    tree_destroy(temp->right);

    if (NULL != tree)
    {
        free(tree);
        tree = NULL;
    }

    goto END;

FAIL:
    status = TREE_FAIL;

END:
    return (status);
}

int
tree_inorder(node_t *tree)
{
    int status = TREE_SUCCESS;

    if (tree == NULL)
    {
        debug_print(("inorder: NULL passed in\n"));
        status = TREE_FAIL;
        goto EXIT;
    }

    tree_inorder(tree->left);
    fprintf(stdout, "%d -> ", (int *)tree->data);
    tree_inorder(tree->right);

EXIT:
    return (status);
}

int
tree_preorder(node_t *tree)
{
    int status = TREE_SUCCESS;

    if (tree == NULL)
    {
        debug_print(("inorder: NULL passed in\n"));
        status = TREE_FAIL;
        goto EXIT;
    }

    fprintf(stdout, "%d -> ", (int *)tree->data);
    tree_preorder(tree->left);
    tree_preorder(tree->right);

EXIT:
    return (status);
}

int
tree_postorder(node_t *tree)
{
    int status = TREE_SUCCESS;

    if (tree == NULL)
    {
        debug_print(("inorder: NULL passed in\n"));
        status = TREE_FAIL;
        goto EXIT;
    }

    tree_postorder(tree->left);
    tree_postorder(tree->right);
    fprintf(stdout, "%d -> ", (int *)tree->data);

EXIT:
    return (status);
}
