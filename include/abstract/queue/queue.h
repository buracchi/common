#pragma once

typedef void* ds_queue_t;

/*
* Return an initialized queue object.
*/
ds_queue_t queue_init();

/*
* Destroy a queue object.
*/
void queue_destroy(const ds_queue_t queue);

int queue_is_empty(const ds_queue_t queue);

int queue_enqueue(const ds_queue_t queue, void* item);

void* queue_dequeue(const ds_queue_t queue);
