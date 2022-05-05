/**
 * @file   queue.c
 * @author Jon S Hall
 * @brief  queue
 * @date   November 2021
 */

#include <queue.h>

/**
 * @references:
 * https://www.geeksforgeeks.org/queue-linked-list-implementation/
 * https://www.techiedelight.com/queue-implementation-using-linked-list/
 * https://www.codesdope.com/blog/article/making-a-queue-using-linked-list-in-c/
 * https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
 * https://codeforwin.org/2015/09/c-program-to-create-and-traverse-singly-linked-list.html
 */

queue_t *
queue_init(void)
{
    queue_t *queue = NULL;

    if (NULL == (queue = calloc(1, sizeof(queue_t))))
    {
        goto EXIT;
    }

    // set size to 0
    queue->size = 0;

    // set front and rear to null
    queue->front = NULL;
    queue->rear  = NULL;

EXIT:
    return (queue);
}

int
queue_enqueue(queue_t *queue, void *data)
{
    int check = Q_SUCCESS;

    // checking NULL enq node, data, queue
    if ((NULL == data) || (NULL == queue))
    {
        check = Q_FAIL;
        goto EXIT;
    }

    // create enq node
    queue_node_t *enq = NULL;

    // calloc and check enq
    if (NULL == (enq = calloc(1, sizeof(queue_node_t))))
    {
        check = Q_FAIL;
        goto EXIT;
    }

    // setting data to enq node
    enq->data = data;
    enq->next = NULL;

    // check if queue is empty
    if (0 == queue_emptycheck(queue))
    {
        queue->rear  = enq;
        enq->next    = queue->rear;
        queue->front = queue->rear;
    }
    else
    {
        queue->front      = queue->rear->next;
        enq->next         = queue->rear->next;
        queue->rear->next = enq;
        queue->rear       = enq;
    }

    // increment the queue->size
    queue->size++;

EXIT:
    return (check);
}

int
queue_emptycheck(queue_t *queue)
{
    int check = Q_SUCCESS;

    // check input
    if (NULL == queue)
    {
        check = Q_FAIL;
        goto EXIT;
    }

    // check for NULL front and rear
    if ((NULL != queue->front) || (NULL != queue->rear))
    {
        check = Q_FAIL;
    }

EXIT:
    // returns 0 if empty, 1 if not
    return (check);
}

queue_node_t *
queue_dequeue(queue_t *queue)
{
    queue_node_t *deq = NULL;

    // check input
    if (NULL == queue)
    {
        goto EXIT;
    }

    // checking null front and rear
    if (0 == queue_emptycheck(queue))
    {
        goto EXIT;
    }

    if (0 < queue->size)
    {
        // assign deq and temp to queue->front
        deq               = queue->front;
        queue->rear->next = deq->next;
        queue->front      = deq->next;

        // decrease queue->size
        queue->size--;
    }

    if (0 == queue->size)
    {
        deq          = queue->front;
        queue->front = NULL;
        queue->rear  = NULL;
    }

EXIT:
    return (deq);
}

int
queue_remove(queue_t *queue, void **item_to_remove)
{
    int check = Q_SUCCESS;

    // checking null queue, item_to_remove
    if ((NULL == queue) || (NULL == item_to_remove))
    {
        check = Q_FAIL;
        goto EXIT;
    }

    uint32_t inc = 0;

    queue_node_t *remove_node = NULL;
    queue_node_t *current     = NULL;

    // check for NULL front and rear
    if (0 == queue_emptycheck(queue))
    {
        check = Q_FAIL;
        goto EXIT;
    }

    current       = queue->front;
    current->next = queue->front->next;

    // traverse till the node to be deleted is reached
    while (inc < queue->size)
    {
        if (*(int *)current->next->data == *(int *)item_to_remove)
        {
            // reassigning nodes
            remove_node   = current->next;
            current->next = remove_node->next;

            // free remove_node
            free(remove_node);
            remove_node = NULL;

            // decrease queue->size to reflect removed node
            queue->size--;

            goto EXIT;
        }
        else
        {
            current = current->next;
            inc++;
        }
    }

    // this catches if item is not in the queue
    check = Q_FAIL;

EXIT:
    return (check);
}

void
queue_traverse(queue_t *queue)
{
    uint32_t      inc           = 1;
    queue_node_t *traverse_node = NULL;

    traverse_node = queue->front;

    if (NULL != traverse_node)
    {
        while (traverse_node->next != queue->front)
        {
            printf("Node %d: %p\n", inc, traverse_node);
            printf("Data: %d\n", *(int *)traverse_node->data);
            inc++;

            traverse_node = traverse_node->next;
        }

        printf("Node %d: %p\n", inc++, traverse_node);
        printf("Data: %d\n", *(int *)traverse_node->data);
    }
}

int
queue_clear(queue_t *queue)
{
    int check = Q_SUCCESS;

    // checking null queue
    if (NULL == queue)
    {
        check = Q_FAIL;
        goto EXIT;
    }

    uint32_t inc        = 0;
    uint32_t queue_size = 0;

    queue_node_t *clear_node = NULL;

    // get queue size
    queue_size = queue->size;

    while (inc <= queue_size)
    {
        clear_node = queue_dequeue(queue);

        if (NULL != clear_node)
        {
            free((int *)clear_node->data);
            clear_node->data = NULL;
            free(clear_node);
            clear_node = NULL;
        }

        inc++;
    }

    // ensure NULL front and rear
    queue->front = NULL;
    queue->rear  = NULL;

EXIT:
    return (check);
}

int
queue_destroy(queue_t **queue_address)
{
    int check = Q_SUCCESS;

    // check for null queue_address
    if (NULL == *queue_address)
    {
        check = Q_FAIL;
        goto EXIT;
    }

    // if empty, goto EXIT
    if (0 == queue_emptycheck(*queue_address))
    {
        check = Q_FAIL;
        goto CLEANUP;
    }

    // clear queue
    queue_clear(*queue_address);

CLEANUP:
    // free and null queue
    free(*queue_address);
    *queue_address = NULL;

EXIT:
    return (check);
}
