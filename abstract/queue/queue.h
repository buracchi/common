#pragma once

typedef void* queue_t;

/*
* Return an initialized queue object.
*/
queue_t queue_init();

void queue_destroy(const queue_t queue);

int queue_is_empty(const queue_t queue);

int queue_enqueue(const queue_t queue, void* item);

void* queue_dequeue(const queue_t queue);
