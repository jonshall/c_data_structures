/**
 * @file   queue.h
 * @author Jon S Hall
 * @brief  queue
 * @date   November 2021
 */

// defines success and failure
#ifndef _QUEUE_H
#define _QUEUE_H

#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define Q_SUCCESS 0;
#define Q_FAIL    1;

/**
 * @brief       structure of a queue node
 *
 * @param data  void pointer to whatever data that queue points to
 * @param next  pointer to the node after it
 */
typedef struct queue_node_t
{
    void *               data;
    struct queue_node_t *next;
} queue_node_t;

/**
 * @brief       structure of a queue object
 *
 * @param size  the number of nodes the queue is currently storing
 * @param front pointer to the front node
 * @param rear  pointer to the rear node
 */
typedef struct queue_t
{
    uint32_t      size;
    queue_node_t *front;
    queue_node_t *rear;
} queue_t;

/**
 * @brief   creates a new queue
 *
 * @returns pointer to allocated queue on success, NULL on fail
 */
queue_t *queue_init(void);

/**
 * @brief       pushes a new node onto the rear of queue
 *
 * @param queue queue to push the node into
 * @param data  data to be pushed into node
 * @return      0 on success, non-zero value on failure
 */
int queue_enqueue(queue_t *queue, void *data);

/**
 * @brief       checks if the queue object is empty
 *
 * @param queue pointer to linked queue object to be checked
 * @returns     0 value if empty, 1 if queue is not empty
 */
int queue_emptycheck(queue_t *queue);

/**
 * @brief       pops the front node out of the queue
 *
 * @param queue queue to pop the node out of
 * @return      pointer to popped node on success, NULL on failure
 */
queue_node_t *queue_dequeue(queue_t *queue);

/**
 * @brief                remove a specific node from the queue based on the
 *                       data stored in that node
 * @param queue          queue to remove the node from
 * @param item_to_remove the data object to be searched for
 * @return               0 on success, non-zero value on failure
 */
int queue_remove(queue_t *queue, void **item_to_remove);

/**
 * @brief       clear all nodes out of a queue
 *
 * @param queue queue to clear out
 * @return      0 on success, non-zero value on failure
 */
int queue_clear(queue_t *queue);

/**
 * @brief               delete a queue
 *
 * @param queue_address pointer to queue pointer
 * @return              0 on success, non-zero value on failure
 */
int queue_delete(queue_t **queue_address);

#endif