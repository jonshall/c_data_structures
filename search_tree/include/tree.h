/**
 * @file   tree.h
 * @author Jon S Hall
 * @brief  search tree
 * @date   December 2021
 */

#ifndef _TREE_H
#define _TREE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// debug print
#ifdef DEBUG
#define debug_print(x) printf x
#else
#define debug_print(x) ;
#endif

// defines for success and fail returns
#define TREE_SUCCESS 0
#define TREE_FAIL    1

/**
 * @struct      node_t
 * @brief       structure for a tree node
 *
 * @param data  data to put into node
 * @param left  node_t * to left side of tree
 * @param right node_t* to right side of tree
 */
typedef struct node_t
{
    void *         data;
    struct node_t *left;
    struct node_t *right;
} node_t;

/**
 * @brief       create a new tree with the given elements.
 *
 * @param  data void * data to start tree
 * @return ptr  node_t * to the tree, NULL on fail
 */

node_t *tree_create(void *data);

/**
 * @brief       create a new node with the given elements.
 *
 * @param  data void * data to put into node
 * @return ptr  node_t * to the node, NULL on fail
 */
node_t *tree_new_node(void *data);

/**
 * @brief       insert an item into the appropriate location in the tree
 *
 * @param  node tree to insert item into
 * @param  item void *item to insert
 * @return int  0 on success, 1 on fail
 */
node_t *tree_insert(node_t *node, void *item);

/**
 * @brief       find the first node in the tree with a given item
 *
 * @param  tree tree to search
 * @param  item void *item to insert
 * @return ptr  node_t * to the node with the item, NULL if item not intree
 */
node_t *tree_find(node_t *tree, void *item);

/**
 * @brief       destroy and free tree
 *
 * @param  tree tree to destroy
 * @return int  0 on success, 1 on fail
 */
int tree_destroy(node_t *tree);

/**
 * @brief      print a tree in an inorder traversal
 *
 * @param tree tree to print
 * @return int 0 on success, 1 on fail
 */
int tree_inorder(node_t *tree);

/**
 * @brief      print a tree in an preorder traversal
 *
 * @param tree tree to print
 * @return int 0 on success, 1 on fail
 */
int tree_preorder(node_t *tree);

/**
 * @brief      print a tree in an postorder traversal
 *
 * @param tree tree to print
 * @return int 0 on success, 1 on fail
 */
int tree_postorder(node_t *tree);

#endif