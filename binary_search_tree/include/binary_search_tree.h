/**
 * @file   binary_search_tree.h
 * @author Jon S Hall
 * @brief  binary search tree
 * @date   December 2021
 */

#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

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

// success and fail returns
#define BST_SUCCESS 0
#define BST_FAIL    1

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
 * @brief       create a new binary search tree (bst) with the given elements.
 *
 * @param  data void * data to start bst
 * @return ptr  node_t * to the bst, NULL on fail
 */
node_t *bst_create(void *data);

/**
 * @brief       create a new node with the given elements.
 *
 * @param  data void * data to put into node
 * @return ptr  node_t * to the node, NULL on fail
 */
node_t *bst_new_node(void *data);

/**
 * @brief       insert an item into the appropriate location in the bst
 *
 * @param  node bst to insert item into
 * @param  item void * item to insert
 * @return ptr  node_t * on success, NULL on fail
 */
node_t *bst_insert(node_t *node, void *item);

/**
 * @brief       find the first node in the tree with a given item
 *
 * @param  bst  bst to search
 * @param  item void * item to find
 * @return ptr  node_t * to node, NULL if item not in bst
 */
node_t *bst_find(node_t *bst, void *item);

/**
 * @brief       remove the given item from the bst
 *
 * @param  bst  bst to remove item from
 * @param  item void * item to remove
 * @return ptr  node_t * on success, NULL on fail
 */
node_t *bst_remove(node_t *bst, void *item);

/**
 * @brief       destroy and free bst
 *
 * @param  bst  node_t * to bst to destroy
 * @return int  0 on success, 1 on fail
 */
int bst_destroy(node_t *bst);

/**
 * @brief     inorder list
 *
 * @param bst node_t passed to start
 */
void bst_inorder(node_t *bst);

/**
 * @brief          find the minimum value in a node
 *
 * @param  node    node_t * to minimum node value
 * @return node_t* returns the minimum node, NULL on fail
 */
node_t *bst_min(node_t *node);

#endif