/**
 * @file   stack.c
 * @author Jon S Hall
 * @brief  stack
 * @date   December 2021
 */

#include <stack.h>

/**
 * @references:
 * https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
 * https://www.programiz.com/dsa/stack
 */

static void
free_stack(stack_t *stack)
{
    free(stack);
}

stack_t *
stack_init(uint32_t capacity, FREE_F customfree)
{
    stack_t *stack = NULL;

    // calloc new stack
    stack = (stack_t *)calloc(1, sizeof(stack_t));

    // checks for failed stack creation
    if (NULL == stack)
    {
        free(stack);
        goto EXIT;
    }

    // checks for valid capacity
    if (0 > capacity - 1)
    {
        goto EXIT;
    }

    // checks for null input
    if (NULL != customfree)
    {
        stack->customfree = customfree;
    }
    else
    {
        stack->customfree = (FREE_F)free_stack;
    }

    stack->arr = calloc(capacity, sizeof(stack_node_t *));

    if (NULL == stack->arr)
    {
        free(stack->arr);
        free(stack);
        stack = NULL;
        goto EXIT;
    }

    // assign to stack
    stack->capacity  = capacity;
    stack->currentsz = 0;

EXIT:
    return (stack);
}

int
stack_fullcheck(stack_t *stack)
{
    int check = 0;

    // checks for null input
    if (NULL == stack)
    {
        check = 1;
        goto EXIT;
    }

    // determines if stack is full
    if (stack->capacity != stack->currentsz)
    {
        check = 1;
        goto EXIT;
    }

EXIT:
    // returns 0 if full, 1 if not
    return (check);
}

int
stack_emptycheck(stack_t *stack)
{
    int check = 0;

    // checks for null input
    if (NULL == stack)
    {
        check = 1;
        goto EXIT;
    }

    // determines if stack is empty
    if (0 != stack->currentsz)
    {
        check = 1;
        goto EXIT;
    }

EXIT:
    // returns 0 if empty, 1 if not
    return (check);
}

int
stack_push(stack_t *stack, void *data)
{
    int check = 0;

    stack_node_t *push = NULL;

    // checks for null input
    if (NULL == stack)
    {
        check = 1;
        goto EXIT;
    }

    if (NULL == data)
    {
        check = 1;
        goto EXIT;
    }

    // checks if stack is full
    if (0 == stack_fullcheck(stack))
    {
        check = 1;
        goto EXIT;
    }

    // calloc to push node
    push = calloc(1, sizeof(stack_node_t));

    if (NULL == push)
    {
        check = 1;
        goto EXIT;
    }

    push->data                                           = data;
    stack->arr[(stack->capacity - stack->currentsz) - 1] = push;

    stack->currentsz++;

EXIT:
    return (check);
}

stack_node_t *
stack_pop(stack_t *stack)
{
    stack_node_t *pop = NULL;

    if (NULL == stack)
    {
        goto EXIT;
    }

    // checks if stack is empty
    if (0 == stack_emptycheck(stack))
    {
        goto EXIT;
    }

    pop = stack->arr[(stack->capacity - stack->currentsz)];
    stack->arr[(stack->capacity - stack->currentsz)] = NULL;

    // decrease current stack size
    stack->currentsz--;

EXIT:
    return (pop);
}

stack_node_t *
stack_peek(stack_t *stack)
{
    stack_node_t *peek = NULL;

    // checks for null input
    if (NULL == stack)
    {
        goto EXIT;
    }

    // checks if stack is empty
    if (0 == stack_emptycheck(stack))
    {
        goto EXIT;
    }

    peek = stack->arr[(stack->capacity - stack->currentsz)];

EXIT:
    return (peek);
}

int
stack_clear(stack_t *stack)
{
    int           check = 0;
    int           inc   = 0;
    stack_node_t *node  = NULL;

    // checks for null input
    if (NULL == stack)
    {
        check = 1;
        goto EXIT;
    }

    while (inc <= stack->capacity)
    {
        node = stack_pop(stack);
        free(node);
        node = NULL;
        inc++;
    }

EXIT:
    return (check);
}

int
stack_destroy(stack_t **stack)
{
    int check = 0;

    if (NULL == *stack)
    {
        check = 1;
        goto EXIT;
    }

    // check for empty stack
    if (0 != stack_emptycheck(*stack))
    {
        // stack is not empty, so clear
        stack_clear(*stack);
    }

    // free arr
    free((*stack)->arr);
    (*stack)->arr = NULL;

    // free stack
    free(*stack);
    *stack = NULL;

EXIT:
    return (check);
}
