/**
 * @file   stack.h
 * @author Jon S Hall
 * @brief  stack
 * @date   December 2021
 */

#ifndef _STACK_H
#define _STACK_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief s    tructure of a stack node
 *
 * @param data void pointer to whatever data that stack points to
 */
typedef struct stack_node_t
{
    void *data;
} stack_node_t;

/**
 * @brief A pointer to a user-defined free function.  This is used to free
 *        memory allocated for stack data.  For simple data types, this is
 *        just a pointer to the standard free function.  More complex structs
 *        stored in stacks may require a function that calls free on multiple
 *        components.
 *
 */
typedef void (*FREE_F)(void *);

/**
 * @brief                  structure of a stack object
 *
 * @param capacity         number of nodes stack can hold
 * @param currentsz        number of nodes stack is currently storing
 * @param arr              array containing stack node pointers
 * @param customfree       pointer to user defined free function
 * @param compare_function pointer to user defined compare function
 */
typedef struct stack_t
{
    uint32_t       capacity;
    uint32_t       currentsz;
    stack_node_t **arr;
    FREE_F         customfree;
} stack_t;

/**
 * @brief            creates a new stack
 *
 * @param capacity   max number of nodes the stack will hold
 * @param customfree pointer to the free function to be used with that list
 * @returns          pointer to allocated stack on SUCCESS, NULL on failure
 */
stack_t *stack_init(uint32_t capacity, FREE_F customfree);

/**
 * @brief       verifies that stack isn't full
 *
 * @param stack pointer stack object
 * @return      int exit code of the function
 */
int stack_fullcheck(stack_t *stack);

/**
 * @brief       verifies that stack isn't empty
 *
 * @param stack pointer stack object
 * @return      int exit code of the function
 */
int stack_emptycheck(stack_t *stack);

/**
 * @brief       pushes a new node into the stack
 *
 * @param stack pointer to stack pointer to push the node into
 * @param data  data to be pushed into node
 * @return      0 on success, non-zero value on failure
 */
int stack_push(stack_t *stack, void *data);

/**
 * @brief       pops the front node out of the stack
 *
 * @param stack pointer to stack pointer to pop the node off of
 * @return      pointer to popped node on SUCCESS, NULL on failure
 */
stack_node_t *stack_pop(stack_t *stack);

/**
 * @brief       get data from node at front of stack without popping
 *
 * @param stack pointer to stack pointer to peek
 * @return      pointer to peeked node on SUCCESS, NULL on failure
 */
stack_node_t *stack_peek(stack_t *stack);

/**
 * @brief       clear all nodes out of a stack
 *
 * @param stack pointer to stack pointer to clear out
 * @return      0 on success, non-zero value on failure
 */
int stack_clear(stack_t *stack);

/**
 * @brief       delete a stack
 *
 * @param stack pointer to stack pointer to be destroyed
 * @return      0 on success, non-zero value on failure
 */
int stack_destroy(stack_t **stack);

#endif
