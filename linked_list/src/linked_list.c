/**
 * @file   linked_list.c
 * @author Jon S Hall
 * @brief  linked_list
 * @date   November 2021
 */

#include <linked_list.h>

/**
 * @references:
 * https://www.geeksforgeeks.org/program-for-all-operations-on-circular-linked-list-in-c/
 * http://www.btechsmartclass.com/data_structures/circular-linked-list.html
 * https://www.guru99.com/circular-linked-list.html
 * https://www.geeksforgeeks.org/write-a-function-that-counts-the-number-of-times-a-given-int-occurs-in-a-linked-list/
 * https://www.javatpoint.com/program-to-sort-the-elements-of-the-circular-linked-list
 * https://www.youtube.com/watch?v=aChfZ86FJbU
 */

// establish head, tail, next nodes
list_node_t *head = NULL;
list_node_t *tail = NULL;
list_node_t *next = NULL;

static void
free_node(list_node_t *node)
{
    free(node);
    node = NULL;
}

static void *
compare_default(int value_to_find, list_node_t *node)
{
    printf("Checking for: %d, found: %d\n", value_to_find, *(int *)node->data);

    void *compare = NULL;

    if (*(int *)((list_node_t *)node)->data == value_to_find)
    {
        compare = node;
    }

    return (compare);
}

// Helper print function for debugging nodes
static void
print_list_members(list_t *list)
{
    if (NULL != list)
    {
        printf(
            "\nLIST:\t%p,\nSIZE:\t%d\nHEAD:\t%p\nTAIL:\t%p\nFREE:\t%p\nCOMPARE:"
            "\t%p\n",
            list,
            list->size,
            list->head,
            list->tail,
            list->customfree,
            list->compare_function);
    }
}

// Helper print function for debugging list
static void
print_list(list_t *list)
{
    int          inc  = 0;
    list_node_t *node = NULL;

    if (NULL != list)
    {
        puts("LIST: ");
        node = list->head;
        for (int inc = 1; (inc != list->size) && (node != NULL); inc++)
        {
            printf("%d", *(int *)node->data);
            node = node->next;
            puts("\n");
        }
    }
}

list_t *
list_new(FREE_F customfree, CMP_F compare_function)
{
    list_t *list = NULL;

    list = (list_t *)calloc(1, sizeof(list_t));

    // checking calloc
    if (NULL == list)
    {
        free(list);
        goto EXIT;
    }

    // setting customreee
    if (NULL != customfree)
    {
        list->customfree = customfree;
    }
    else
    {
        list->customfree = (FREE_F)free_node;
    }

    // setting compare_function
    if (NULL != compare_function)
    {
        list->compare_function = compare_function;
    }
    else
    {
        list->compare_function = (CMP_F)compare_default;
    }

    // set size to 0
    list->size = 0;

    // set head and tail to null
    list->head = NULL;
    list->tail = NULL;

EXIT:
    return (list);
}

int
list_push_head(list_t *list, void *data)
{
    int check = 0;

    // create push_head node and calloc
    list_node_t *push_head = NULL;
    push_head              = (list_node_t *)calloc(1, sizeof(list_node_t));

    // checking NULL push_head node
    if (NULL == push_head)
    {
        check = 1;
        free(push_head);
        goto EXIT;
    }

    // checking NULL list
    if (NULL == list)
    {
        check = 1;
        free(push_head);
        goto EXIT;
    }

    // checking NULL data
    if (NULL == data)
    {
        check = 1;
        free(push_head);
        goto EXIT;
    }

    // setting data to push_head node
    push_head->data = data;
    push_head->next = NULL;

    // If list is empty
    if (0 == list_emptycheck(list))
    {
        list->tail      = push_head;
        push_head->next = list->tail;
        list->head      = list->tail;
    }
    else
    {
        push_head->next  = list->head;
        list->tail->next = push_head;
        list->head       = push_head;
        list->head->next = push_head->next;
    }

    // increment the list->size
    list->size++;

EXIT:
    return (check);
}

int
list_push_tail(list_t *list, void *data)
{
    int check = 0;

    // create push_tail node and calloc
    list_node_t *push_tail = NULL;
    push_tail              = (list_node_t *)calloc(1, sizeof(list_node_t));

    // checking NULL push_tail node
    if (NULL == push_tail)
    {
        check = 1;
        free(push_tail);
        goto EXIT;
    }

    // checking NULL data
    if (NULL == data)
    {
        check = 1;
        free(push_tail);
        goto EXIT;
    }

    // checking NULL list
    if (NULL == list)
    {
        check = 1;
        free(push_tail);
        goto EXIT;
    }

    // setting data to push_tail node
    push_tail->data = data;
    push_tail->next = NULL;

    // If list is empty
    if (0 == list_emptycheck(list))
    {
        list->tail      = push_tail;
        push_tail->next = list->tail;
        list->head      = list->tail;
    }
    else
    {
        list->head       = list->tail->next;
        push_tail->next  = list->tail->next;
        list->tail->next = push_tail;
        list->tail       = push_tail;
    }

    // increment the list->size
    list->size++;

EXIT:
    return (check);
}

int
list_emptycheck(list_t *list)
{
    int check = 0;

    // check for NULL head and tail
    if ((NULL != list->head) || (NULL != list->tail))
    {
        check = 1;
        goto EXIT;
    }

EXIT:
    return (check);
}

list_node_t *
list_pop_head(list_t *list)
{
    list_node_t *pop_head = NULL;

    // checking null list
    if (NULL == list)
    {
        goto EXIT;
    }

    // check for NULL head and tail
    if (0 == list_emptycheck(list))
    {
        goto EXIT;
    }

    if (0 < list->size)
    {
        // assign pop_head and temp to list->head
        pop_head         = list->head;
        list->tail->next = pop_head->next;
        list->head       = pop_head->next;

        // Decrease list->size
        list->size--;
    }

EXIT:
    return (pop_head);
}

list_node_t *
list_pop_tail(list_t *list)
{
    list_node_t *pop_tail = NULL;

    // checking null list
    if (NULL == list)
    {
        goto EXIT;
    }

    // check for NULL head and tail
    if (0 == list_emptycheck(list))
    {
        goto EXIT;
    }

    pop_tail = list->tail;

    if (0 < list->size)
    {
        // Traverse until node before tail
        while (pop_tail->next != list->tail)
        {
            pop_tail = pop_tail->next;
        }

        // Pop out tail and assign new tail
        pop_tail->next = list->tail->next;
        list->tail     = pop_tail;

        // Decrease list->size
        list->size--;
    }

EXIT:
    return (pop_tail);
}

list_node_t *
list_peek_head(list_t *list)
{
    list_node_t *peek_head = NULL;

    // checking null list
    if (NULL == list)
    {
        goto EXIT;
    }

    // check for NULL head and tail
    if (0 == list_emptycheck(list))
    {
        goto EXIT;
    }

    peek_head = list->head;

EXIT:
    return (peek_head);
}

list_node_t *
list_peek_tail(list_t *list)
{
    list_node_t *peek_tail = NULL;

    // checking null list
    if (NULL == list)
    {
        goto EXIT;
    }

    // check for NULL head and tail
    if (0 == list_emptycheck(list))
    {
        goto EXIT;
    }

    peek_tail = list->tail;

EXIT:
    return (peek_tail);
}

int
list_remove(list_t *list, void **item_to_remove)
{
    list_node_t *remove_node = NULL;
    list_node_t *position    = NULL;

    int check = 0;
    int inc   = 0;

    // checking null list
    if (NULL == list)
    {
        check = 1;
        goto EXIT;
    }

    // check for NULL head and tail
    if (0 == list_emptycheck(list))
    {
        check = 1;
        goto EXIT;
    }

    // check for an empty item_to_remove
    if (NULL == item_to_remove)
    {
        check = 1;
        goto EXIT;
    }

    position       = list->head;
    position->next = list->head->next;

    // Traverse till the node to be deleted is reached
    while (inc < (list->size))
    {
        if (*(int *)position->next->data == *(int *)item_to_remove)
        {
            // Reassigning nodes
            remove_node    = position->next;
            position->next = remove_node->next;

            // free remove_node
            list->customfree(remove_node);
            remove_node = NULL;

            // Decrease list->size to reflect removed node
            list->size--;

            goto EXIT;
        }
        else
        {
            position = position->next;
            inc++;
        }
    }

    // this catches if item is not in the list
    check = 1;

EXIT:
    return (check);
}

int
list_foreach_call(list_t *list, ACT_F action_function)
{
    int check = 0;
    int inc   = 0;

    list_node_t *foreach = NULL;

    // checking null list
    if (NULL == list)
    {
        check = 1;
        goto EXIT;
    }

    // check for null action_function
    if (NULL == action_function)
    {
        check = 1;
        goto EXIT;
    }

    // check for NULL head and tail
    if (0 == list_emptycheck(list))
    {
        check = 1;
        goto EXIT;
    }

    foreach
        = list->head;
    foreach
        ->next = list->head->next;

    // Traverse and perform action on all nodes
    while (inc < (list->size))
    {
        action_function(foreach);

        foreach
            = foreach->next;
        inc++;
    }

EXIT:
    return (check);
}

list_node_t *
list_find_first_occurrence(list_t *list, void **search_data)
{
    int inc = 0;

    list_node_t *find_first = NULL;

    // checking null list
    if (NULL == list)
    {
        goto EXIT;
    }

    // check for null search_data
    if (NULL == *search_data)
    {
        goto EXIT;
    }

    // check for NULL head and tail
    if (0 == list_emptycheck(list))
    {
        goto EXIT;
    }

    find_first = list->head;

    while (inc < (list->size))
    {
        if (*(int *)find_first->data == *(int *)search_data)
        {
            // Found first occurence
            goto EXIT;
        }
        else
        {
            find_first = find_first->next;
            inc++;
        }
    }

    // This catches if item is not in the list
    find_first = NULL;

EXIT:
    return (find_first);
}

list_t *
list_find_all_occurrences(list_t *list, void **search_data)
{
    int inc = 0;

    list_node_t *find_all = NULL;
    list_t *     list_all = NULL;

    // checking null list
    if (NULL == list)
    {
        goto EXIT;
    }

    // check for null search_data
    if (NULL == *search_data)
    {
        goto EXIT;
    }

    // check for NULL head and tail
    if (0 == list_emptycheck(list))
    {
        goto EXIT;
    }

    // Create new list to store found occurences
    list_all
        = list_new((FREE_F)list->customfree, (CMP_F)list->compare_function);

    // if list_new failed
    if (NULL == list_all)
    {
        goto EXIT;
    }

    find_all       = list->head;
    find_all->next = list->head->next;

    while (inc < (list->size))
    {
        if (*(int *)search_data == *(int *)find_all->data)
        {
            // Found a match
            list_push_tail(list_all, find_all->data);
        }

        find_all = find_all->next;
        inc++;
    }

    // check for an empty list after all occurences should be added
    if (0 == list_emptycheck(list))
    {
        // No occurences were found, list still NULL;
        goto EXIT;
    }

EXIT:
    return (list_all);
}

int
list_sort(list_t *list)
{
    int check      = 0;
    int inc        = 0;
    int node_count = 0;
    int list_size  = 0;

    list_node_t *current_node = NULL;
    list_node_t *next_node    = NULL;
    list_node_t *temp_node    = NULL;

    // checking null list
    if (NULL == list)
    {
        check = 1;
        goto EXIT;
    }

    // check for NULL head and tail
    if (0 == list_emptycheck(list))
    {
        check = 1;
        goto EXIT;
    }

    // Get list size
    list_size = list->size;

    // Loop until all nodes are sorted
    for (node_count = (list_size - 2); 0 <= node_count; node_count--)
    {
        // Point to head and head->next
        current_node = list->head;
        next_node    = current_node->next;

        // Loop until smallest value
        for (inc = 0; inc <= node_count; inc++)
        {
            // Switch if current_node is larger than next_node
            if (current_node->data > next_node->data)
            {
                temp_node          = current_node->data;
                current_node->data = next_node->data;
                next_node->data    = temp_node;
            }

            // Traverse to next nodes
            current_node = current_node->next;
            next_node    = next_node->next;
        }
    }

EXIT:
    return (check);
}

int
list_clear(list_t *list)
{
    int check     = 0;
    int inc       = 0;
    int list_size = 0;

    list_node_t *clear_node = NULL;

    // checking null list
    if (NULL == list)
    {
        check = 1;
        goto EXIT;
    }

    clear_node       = list->head;
    clear_node->next = list->head->next;

    list_size = list->size;

    while (inc <= list_size)
    {
        list_pop_tail(list);
        list_remove(list, (void *)list->tail);

        clear_node = clear_node->next;
        inc++;
    }

    list_pop_head(list);
    list_remove(list, (void *)list->head);

    // ensure NULL head and tail
    list->head = NULL;
    list->tail = NULL;

EXIT:
    return (check);
}

int
list_delete(list_t **list_address)
{
    int check = 0;

    // check for null list_address
    if (NULL == *list_address)
    {
        check = 1;
        goto EXIT;
    }

    // if empty, goto EXIT
    if (0 == list_emptycheck(*list_address))
    {
        check = 1;
        goto EXIT;
    }

    // clear list
    list_clear(*list_address);

    // free list
    free(*list_address);
    *list_address = NULL;

EXIT:
    return (check);
}
