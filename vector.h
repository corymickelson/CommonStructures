//
// Created by red on 6/7/17.
//

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef STRUCTURES_VECTOR_H
#define STRUCTURES_VECTOR_H

#define vector_init(vec) vector vec; _vector_init(&vec)
#define vector_add(vec, item) _vector_add(&vec, (void*) item)
#define vector_set(vec, id, item) _vector_set(&vec, id, (void*) item)
#define vector_get(vec, t, id) (t) _vector_get(&vec, id)
#define vector_delete(vec, id) _vector_delete(&vec, id)
#define vector_stats(vec) vector_meta meta; _vector_stats(&vec)
#define vector_free(vec) _vector_free(&vec)
#define vector_expand(vec, size) _vector_expand(&vec, size)
#define vector_contract(vec) _vector_contract(&vec)
#define vector_map(self, t, fn, vec) vector vec;  {\
    _vector_init(&vec);\
    t (*fn_ptr)(t);\
    fn_ptr = fn;\
    for(int i = 0; i < self.size; i++) {\
        t item = vector_get(self, t, i);\
        t result = (*fn_ptr)((t) item);\
        vector_add(vec, result);\
    }\
}
// map = calloc(self.capacity, sizeof(void));
// map[i] = (void*) result;

#define vector_map_self(vec, t, fn) {\
   t (*fn_ptr)(t);\
    fn_ptr = fn;\
    for(int i = 0; i < vec.size; i++) {\
        t item = vector_get(vec, t, i);\
        t result = (*fn_ptr)((t) item);\
        vector_set(vec, i,(t) result);\
    }\
}

/**
 * @property {vector} vec - vector
 * @property t - pointer type
 * @property accum - accumulator, results object
 * @property {Function} fn - function pointer, fn must take two arguments, and return same type
 *      as arguments.
 * @returns {pointer} accum
 */
#define vector_reduce(vec, t, accum, fn) t accum=0;{\
    t (*fn_ptr)(t, t);\
    fn_ptr = fn;\
    for(int i = 0; i < vec.size; i++) { \
        t result = (*fn_ptr)((t)accum, (t)vec.items[i]);\
        accum = result;\
    }\
}

#define VECTOR_INIT_CAPACITY 100
#define VECTOR_RESIZE_FACTOR 2
#define VECTOR_LOWER_BOUNDS 30
#define VECTOR_UPPER_BOUNDS 70

typedef struct {
    int capacity;
    int size;
    void **items;
    bool lock_size;
} vector;

typedef struct {
    int capacity;
    double percent_remaining;
    double percent_occupied;
} vector_meta;

void _vector_init(vector *);

vector_meta _vector_stats(vector *);

static void _vector_realloc(vector *);

void _vector_add(vector *, void *);

void _vector_set(vector *, int, void *);

void *_vector_get(vector *, int);

void _vector_delete(vector *, int);

void _vector_free(vector *);

void _vector_contract(vector *);

void _vector_expand(vector *, int);

#endif //STRUCTURES_VECTOR_H
