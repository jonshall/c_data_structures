/**
 * @file   queue_p.c
 * @author Jon S Hall
 * @brief  queue_p
 * @date   November 2021
 */

#include <queue_p.h>

/**
 * @references:
 * https://www.geeksforgeeks.org/priority-queue-using-array-in-c/
 * https://www.tutorialspoint.com/data_structures_algorithms/priority_queue.htm
 * https://codereview.stackexchange.com/questions/186474/priority-queue-implementation-in-c-based-on-heap-ordered-resizable-array/186492#186492
 */

// helper free function to use if no user-supplied free
static void
free_queue(queue_p_node_t *node)
{
    free(node);
}

// helper print function used for debugging
static void
print_queue(queue_p_t *queue)
{
    puts("\n----\n");
    for (int inc = 0; inc < queue->currentsz; inc++)
    {
        printf("%d : %d, ",
               *(int *)queue->arr[inc]->data,
               queue->arr[inc]->priority);
    }
    puts("\n----\n");
}

// helper function to reset queue if needed
static void
reset_queue(queue_p_t *queue)
{
    int inc = 0;

    queue_p_node_t *tmp = NULL;

    while (queue->currentsz != 0)
    {
        tmp = queue_p_dequeue(queue);
        if (NULL != tmp)
        {
            free(tmp);
            tmp = NULL;
        }
    }
    while (queue->currentsz != queue->capacity)
    {
        queue_p_enqueue(queue, queue->arr[inc], 0);
        inc++;
    }
}

queue_p_t *
queue_p_init(uint32_t capacity, FREE_F customfree)
{
    queue_p_t *que_p = NULL;

    // calloc temp queue
    que_p = (queue_p_t *)calloc(1, sizeof(queue_p_t));

    // checks for failed queue creation
    if (NULL == que_p)
    {
        goto EXIT;
    }

    // check for valid capacity
    if (0 > capacity - 1)
    {
        goto EXIT;
    }

    // check and set customfree
    if (NULL == customfree)
    {
        que_p->customfree = customfree;
    }
    else
    {
        que_p->customfree = (FREE_F)free_queue;
    }

    // calloc space for nodes by queue_p capacity
    que_p->arr = calloc(capacity, sizeof(queue_p_node_t *));

    if (NULL == que_p->arr)
    {
        free(que_p);
        que_p = NULL;
        goto EXIT;
    }

    // assign to queue
    que_p->capacity  = capacity;
    que_p->currentsz = 0;

EXIT:
    return (que_p);
}

int
queue_p_fullcheck(queue_p_t *queue)
{
    int check = 0;

    // check input
    if (NULL == queue)
    {
        check = 1;
        goto EXIT;
    }

    // determines if queue is full
    if (queue->capacity != queue->currentsz)
    {
        check = 1;
        goto EXIT;
    }

EXIT:
    // returns 0 if full, 1 if not
    return (check);
}

int
queue_p_emptycheck(queue_p_t *queue)
{
    int check = 0;

    // check input
    if (NULL == queue)
    {
        check = 1;
        goto EXIT;
    }

    // determines if queue is empty
    if (0 != queue->currentsz)
    {
        check = 1;
        goto EXIT;
    }

EXIT:
    // returns 0 if empty, 1 if not
    return (check);
}

int
queue_p_enqueue(queue_p_t *queue, void *data, int priority)
{
    int          check  = 0;
    int          index  = 0;
    unsigned int size   = 0;
    unsigned int number = 0;

    queue_p_node_t *enq     = NULL;
    queue_p_node_t *current = NULL;

    // check input
    if (NULL == queue)
    {
        check = 1;
        goto EXIT;
    }

    // check input data
    if (NULL == data)
    {
        check = 1;
        goto EXIT;
    }

    // check input priority
    if (0 > priority)
    {
        check = 1;
        goto EXIT;
    }

    // checks if queue is full
    if (0 == queue_p_fullcheck(queue))
    {
        check = 1;
        goto EXIT;
    }

    // calloc to enqueue node
    enq = calloc(1, sizeof(queue_p_node_t));

    // ensure enq was allocated successfully
    if (NULL == enq)
    {
        free(enq);
        check = 1;
        goto EXIT;
    }

    // assign input to enq
    enq->data     = data;
    enq->priority = priority;

    // if empty list, insert as only node
    if (0 == queue_p_emptycheck(queue))
    {
        // insert node and increase size
        queue->arr[queue->currentsz] = enq;
        queue->currentsz++;
        goto EXIT;
    }

    while (index < queue->capacity)
    {
        // assign current to current position in queue_p
        current = queue->arr[index];

        // checks if queue is full
        if (0 == queue_p_fullcheck(queue))
        {
            check = 1;
            goto EXIT;
        }

        // inserts enq at front of queue_p
        if (NULL == queue->arr[index])
        {
            queue->arr[index] = enq;
            queue->currentsz++;
            goto EXIT;
        }

        // if enq priority is < current priority, then insert enq into queue_p
        if (enq->priority < current->priority)
        {
            size   = queue->currentsz;
            number = size - 1;

            // go through queue_p from front to rear
            while (number >= index)
            {
                // move nodes up one index until enq can be inserted
                current                = queue->arr[number];
                queue->arr[number + 1] = current;
                number--;
            }

            // insert enq into queue_p once we found proper location based on
            // priority
            queue->arr[index] = enq;
            queue->currentsz++;

            goto EXIT;
        }

        // increase index and keep searching if no conditions above are met
        index++;
    }

    queue->customfree(enq);
    enq = NULL;

EXIT:
    return (check);
}

queue_p_node_t *
queue_p_dequeue(queue_p_t *queue)
{
    queue_p_node_t *deq = NULL;

    // check input
    if (NULL == queue)
    {
        goto EXIT;
    }

    // checks if queue is full
    if (0 == queue_p_emptycheck(queue))
    {
        goto EXIT;
    }

    // set deq to rear, then remove and decrease size
    deq = queue->arr[(queue->capacity - queue->currentsz)];
    queue->arr[(queue->capacity - queue->currentsz)] = NULL;

    queue->currentsz--;

EXIT:
    return (deq);
}

queue_p_node_t *
queue_p_peek(queue_p_t *queue)
{
    queue_p_node_t *peek = NULL;

    // check input
    if (NULL == queue)
    {
        goto EXIT;
    }

    // checks if queue is empty
    if (0 == queue_p_emptycheck(queue))
    {
        goto EXIT;
    }

    peek = queue->arr[(queue->capacity - queue->currentsz)];

EXIT:
    return (peek);
}

int
queue_p_clear(queue_p_t *queue)
{
    int check = 0;
    int inc   = 0;

    queue_p_node_t *clear = NULL;

    // check input
    if (NULL == queue)
    {
        check = 1;
        goto EXIT;
    }

    // while things are in the queue, dequeue all
    while (inc < queue->capacity)
    {
        clear = queue_p_dequeue(queue);
        free(clear);
        clear = NULL;
        inc++;
    }

EXIT:
    return (check);
}

int
queue_p_destroy(queue_p_t **queue)
{
    int check = 0;

    // check input
    if (NULL == *queue)
    {
        check = 1;
        goto EXIT;
    }

    // check for empty queue_p
    if (0 != queue_p_emptycheck(*queue))
    {
        // queue_p is not empty, so clear
        queue_p_clear(*queue);
    }

    // free arr
    free((*queue)->arr);
    (*queue)->arr = NULL;

    // free queue
    free(*queue);
    *queue = NULL;

EXIT:
    return (check);
}
