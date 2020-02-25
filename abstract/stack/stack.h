#pragma once

typedef void* _stack_t;

_stack_t stack_init();

extern void stack_destroy(const _stack_t handle);

extern int stack_is_empty(const _stack_t handle);

extern int stack_push(const _stack_t handle, void* item);

extern void* stack_pop(const _stack_t handle);

extern void* stack_peek(const _stack_t handle);
