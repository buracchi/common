#pragma once

#include <stdbool.h>

typedef void* ds_queue_t;

/*
* Return an initialized queue object.
*
* @return the initialized queue on success; NULL otherwise.
*/
extern ds_queue_t ds_queue_init();

/*
* Destroy a queue object.
*
* @param queue - the queue to destroy.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_queue_destroy(const ds_queue_t queue);

/*
* Set the value referenced by is_empty as true if the queue is empty or as flase
* otherwise.
*
* @param queue - the queue to check.
* @param is_empty - the pointer that will reference the state of the queue.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_queue_is_empty(const ds_queue_t queue, bool* is_empty);

/*
* Enqueue an item into a queue.
*
* @param queue - the queue to enqueue the item into.
* @param item - the item to enqueue into the queue.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_queue_enqueue(const ds_queue_t queue, const void* item);

/*
* Dequeue an item out a queue.
*
* @param queue - the queue to dequeue the item out.
* @param item - the pointer that will reference the item, if the parameter
* is NULL the item is ignored.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_queue_dequeue(const ds_queue_t queue, void** item);
