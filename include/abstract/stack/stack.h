#pragma once

typedef void* ds_stack_t;

/*
* Return an initialized stack object.
*/
extern ds_stack_t stack_init();

/*
* Destroy a set object.
*/
extern void stack_destroy(const ds_stack_t handle);

extern int stack_is_empty(const ds_stack_t handle);

extern int stack_push(const ds_stack_t handle, void* item);

extern void* stack_pop(const ds_stack_t handle);

extern void* stack_peek(const ds_stack_t handle);
