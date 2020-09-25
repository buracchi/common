#pragma once

#include <stdbool.h>

typedef void* set_t;

/*
* Return an initialized set object.
*/
extern set_t set_init();

/*
* Destroy a set object.
*/
extern void set_destroy(const set_t S);

/*
* returns the union of sets S and T.
*/
extern set_t set_union(const set_t S, const set_t T);

/*
* returns the intersection of sets S and T.
*/
extern set_t set_intersection(const set_t S, const set_t T);

/*
* returns the difference of sets S and T.
*/
extern set_t set_difference(const set_t S, const set_t T);

/*
* a predicate that tests whether the set S is a subset of set T.
*/
extern bool set_subset(const set_t S, const set_t T);

/*
* adds the element elem to S, if it is not present already.
*/
extern int set_add(const set_t S, const void* elem);

/*
* removes the element elem from S, if it is present.
*/
extern int set_remove(const set_t S, const void* elem);

/*
* checks whether the value elem is in the set S.
*/
extern bool set_is_element_of(const set_t S, const void* elem)

/*
* checks whether the set S is empty.
*/
extern bool set_is_empty(const set_t S)

/*
* returns a function that returns one more value of S at each call, in some arbitrary order.
*/
extern void* set_iterate(const set_t S)

/*
* returns a list containing the elements of S in some arbitrary order.
*/
extern void* set_enumerate(const set_t S)
