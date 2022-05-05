/**
 * @file   hash_table.h
 * @author Jon S Hall
 * @brief  hash_table
 * @date   November 2021
 */

#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// debug print
#ifdef DEBUG
#define debug_print(x) printf x
#else
#define debug_print(x) ;
#endif

#define HASH_SUCCESS    0
#define HASH_FAILURE    1
#define HASH_TABLE_SIZE 64

/**
 * @struct         node_t
 * @brief          structure of a node_t object
 *
 * @param key      key saved key value for item
 * @param data     int corresponding to key
 * @param node_t * pointer to next node
 */
typedef struct node_t
{
    char *         key;
    int            data;
    struct node_t *next;
} node_t;

/**
 * @struct      hash_table_t
 * @brief       structure of a hash_table_t object
 *
 * @param size  uint32_t number of indices supported by table
 * @param table void ** array of pointers
 */
typedef struct hash_table_t
{
    uint32_t size;
    node_t **table;
} hash_table_t;

/**
 * @brief      initializes hash table
 *
 * @param size number indexes in the table
 * @return ptr hash_table_t ptr to allocated table, NULL on fail
 */
hash_table_t *hash_table_init(uint32_t size);

/**
 * @brief       adds an item to the table
 *
 * @param table pointer to table address
 * @param data  data to be stored at that key value
 * @param key   key for data to be stored at (assumes data not 0)
 * @return int  0 for success, 1 for failure
 */
int hash_table_add(hash_table_t *table, int data, const char *key);

/**
 * @brief       looks up an item in the table by key
 *
 * @param table pointer to table address
 * @param key   key for data being searched for
 * @return ptr  node_t pointer on success, NULL on fail
 */
node_t *hash_table_lookup(hash_table_t *table, const char *key);

/**
 * @brief       removes an item from the hash table
 *
 * @param table pointer to table address
 * @param key   key of data to be removed
 * @return int  0 for success, 1 for failure
 */
int hash_table_remove(hash_table_t *table, const char *key);

/**
 * @brief       destroys hash table
 *
 * @param table pointer to table address
 * @return int  0 for success, 1 for failure
 */
int hash_table_destroy(hash_table_t *table);

#endif