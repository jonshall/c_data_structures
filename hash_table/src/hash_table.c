/**
 * @file   hash_table.c
 * @author Jon S Hall
 * @brief  hash_table
 * @date   November 2021
 */

#include <hash_table.h>

/**
 * @references:
 * https://medium.com/@bennettbuchanan/an-introduction-to-hash-tables-in-c-b83cbf2b4cf6
 * https://stackoverflow.com/questions/7666509/hash-function-for-string
 * http://www.cse.yorku.ca/~oz/hash.html
 * https://www.log2base2.com/algorithms/searching/hashing-in-c-data-structure.html
 * https://www.programiz.com/dsa/hash-table
 */

/**
 * @brief      helper function to create a hash index
 *
 * @param key  key for data
 * @return     hash
 */
static unsigned int
create_hash(const char *key)
{
    uint32_t length = 0;
    uint32_t value  = 0;
    uint32_t inc    = 0;

    // get the len of the key
    length = strnlen(key, HASH_TABLE_SIZE);

    for (inc = 0; inc < length; inc++)
    {
        value += key[inc];
        value = ((value * key[inc]) % HASH_TABLE_SIZE);
    }

    return (value);
}

hash_table_t *
hash_table_init(uint32_t size)
{
    int inc = 0;

    hash_table_t *hash_table = NULL;

    // calloc new hash table and ensure table was allocated
    if (NULL == (hash_table = calloc(1, sizeof(hash_table_t))))
    {
        goto EXIT;
    }

    // assign size to hash table
    hash_table->size = size;

    // calloc space based on array size
    // casting to node_t struct
    hash_table->table = (node_t **)calloc(hash_table->size, sizeof(node_t *));

    // ensure table was calloced
    if (NULL == hash_table->table)
    {
        // if fail, free hash_table
        free(hash_table);
        hash_table = NULL;
    }

EXIT:
    return (hash_table);
}

int
hash_table_add(hash_table_t *table, int data, const char *key)
{
    int check = HASH_SUCCESS;

    // check input
    if ((NULL == table) || (0 > data) || (NULL == key))
    {
        debug_print(("NULL passed to hash_add\n"));
        goto EXIT;
    }

    uint32_t hash_index = 0;
    uint32_t inc        = 0;
    uint32_t next_num   = 0;

    // node struct to add
    node_t *add = NULL;

    // pointer for actual key
    char *p_key_str = NULL;

    // calloc node, key and check
    add       = calloc(1, sizeof(node_t));
    p_key_str = calloc(strlen(key) + 1, sizeof(char));

    if (!(add && p_key_str))
    {
        debug_print(("ERROR: hash_add: calloc add failed\n"));
        goto FAIL;
    }

    // copy passed in key
    if (NULL == strncpy(p_key_str, key, strlen(key)))
    {
        debug_print(("ERROR: hash_add: failed to copy key\n"));
        goto FAIL;
    }

    // assign key and data to node
    add->key  = p_key_str;
    add->data = data;
    add->next = NULL;

    // create hash_index
    hash_index = create_hash(add->key);

    for (inc = 0; inc < HASH_TABLE_SIZE; inc++)
    {
        next_num = (inc + hash_index) % HASH_TABLE_SIZE;

        if (NULL == table->table[next_num])
        {
            // add->next              = table->table[(hash_index)];
            table->table[next_num] = add;

            debug_print(("\n------------------------\n\n"));
            debug_print(("hash_add: table: %p\n", table));
            debug_print(("hash_add: data:  %d\n", add->data));
            debug_print(("hash_add: key:   %s\n", add->key));
            debug_print(("hash_add: index  [%d]\n", next_num));
            debug_print(("\n------------------------\n\n"));

            goto EXIT;
        }
    }

FAIL:
    check = HASH_FAILURE;
    if (NULL != add)
    {
        free(add);
        add = NULL;
    }

    if (NULL != p_key_str)
    {
        free(p_key_str);
        p_key_str = NULL;
    }

EXIT:
    return (check);
}

node_t *
hash_table_lookup(hash_table_t *table, const char *key)
{
    // temp node_t
    node_t *lookup = NULL;

    // ensure table, key not null
    if ((NULL == table) || (NULL == key))
    {
        debug_print(("ERROR: NULL passed to hash_lookup\n"));
        goto EXIT;
    }

    uint32_t hash_index     = 0;
    uint32_t inc            = 0;
    uint32_t next_num       = 0;
    size_t   key_len        = 0;
    size_t   lookup_key_len = 0;

    // create hash_index
    hash_index = create_hash(key);

    for (inc = 0; inc < HASH_TABLE_SIZE; inc++)
    {
        next_num = (inc + hash_index) % HASH_TABLE_SIZE;

        if ((NULL != table->table[next_num])
            && (NULL != table->table[next_num]->key)
            && (0 == strncmp(table->table[next_num]->key, key, strlen(key))))
        {
            lookup = table->table[next_num];

            debug_print(("\n------------------------\n\n"));
            debug_print(("hash_lookup: table: %p\n", table));
            debug_print(("hash_lookup: data:  %d\n", lookup->data));
            debug_print(("hash_lookup: key:   %s\n", lookup->key));
            debug_print(("hash_lookup: index  [%d]\n", next_num));
            debug_print(("\n------------------------\n\n"));

            goto EXIT;
        }
    }

    // if here then no node match
    debug_print(("hash_lookup: no match found\n"));
    lookup = NULL;

EXIT:
    return (lookup);
}

int
hash_table_remove(hash_table_t *table, const char *key)
{
    int check = HASH_SUCCESS;

    // ensure table, key not null
    if ((NULL == table) || (NULL == key))
    {
        check = HASH_FAILURE;
        goto EXIT;
    }

    uint32_t hash_index = 0;
    uint32_t inc        = 0;
    uint32_t next_num   = 0;

    // node struct to remove
    node_t *temp = NULL;

    // create hash_index
    hash_index = create_hash(key);

    for (inc = 0; inc < HASH_TABLE_SIZE; inc++)
    {
        next_num = (inc + hash_index) % HASH_TABLE_SIZE;

        if ((NULL != table->table[next_num])
            && (NULL != table->table[next_num]->key)
            && (0 == strncmp(table->table[next_num]->key, key, strlen(key))))
        {
            temp                   = table->table[next_num];
            table->table[next_num] = NULL;

            debug_print(("\n------------------------\n\n"));
            debug_print(("hash_remove: table: %p\n", table));
            debug_print(("hash_remove: data:  %d\n", temp->data));
            debug_print(("hash_remove: key:   %s\n", temp->key));
            debug_print(("hash_remove: index   [%d]\n", next_num));
            debug_print(("\n------------------------\n\n"));

            goto REMOVE;
        }
    }

    // if this is reached, node not in table to remove
    check = HASH_FAILURE;

    goto EXIT;

REMOVE:
    // check and free key
    debug_print(("hash_remove: node removed\n"));
    if (NULL != temp->key)
    {
        free(temp->key);
        temp->key = NULL;
    }
    temp->data = 0;

    // check and free node
    if (NULL != temp)
    {
        free(temp);
        temp = NULL;
    }

EXIT:
    return (check);
}

int
hash_table_destroy(hash_table_t *table)
{
    int status = HASH_SUCCESS;

    if (NULL == table)
    {
        debug_print(("hash_free: table is NULL\n"));
        status = HASH_FAILURE;
        goto END;
    }

    uint32_t inc = 0;
    node_t * temp;

    // traverse the list, free and null nodes
    for (inc = 0; inc < table->size; ++inc)
    {
        if (NULL != table->table[inc])
        {
            // free and null keys and table indices
            if (NULL != table->table[inc]->key)
            {
                free(table->table[inc]->key);
                table->table[inc]->key  = NULL;
                table->table[inc]->data = 0;
            }

            free(table->table[inc]);
            table->table[inc] = NULL;
        }
    }
    // free and null tables
    free(table->table);
    table->table = NULL;
    free(table);
    table = NULL;

END:
    return (status);
}