#pragma once

#include <stdbool.h>

typedef void* ds_set_t;

/*
* Return an initialized set object.
*/
extern ds_set_t set_init();

/*
* Destroy a set object.
*/
extern void set_destroy(const ds_set_t S);

/*
* returns the union of sets S and T.
*/
extern ds_set_t set_union(const ds_set_t S, const ds_set_t T);

/*
* returns the intersection of sets S and T.
*/
extern ds_set_t set_intersection(const ds_set_t S, const ds_set_t T);

/*
* returns the difference of sets S and T.
*/
extern ds_set_t set_difference(const ds_set_t S, const ds_set_t T);

/*
* a predicate that tests whether the set S is a subset of set T.
*/
extern bool set_subset(const ds_set_t S, const ds_set_t T);

/*
* adds the element elem to S, if it is not present already.
*/
extern int set_add(const ds_set_t S, const void* elem);

/*
* removes the element elem from S, if it is present.
*/
extern int set_remove(const ds_set_t S, const void* elem);

/*
* checks whether the value elem is in the set S.
*/
extern bool set_is_element_of(const ds_set_t S, const void* elem);

/*
* checks whether the set S is empty.
*/
extern bool set_is_empty(const ds_set_t S);

/*
* returns a function that returns one more value of S at each call, in some arbitrary order.
*/
extern void* set_iterate(const ds_set_t S);

/*
* returns a list containing the elements of S in some arbitrary order.
*/
extern void* set_enumerate(const ds_set_t S);
