//
// Created by red on 6/7/17.
//

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "try_catch.h"

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
#define vector_compare_ints(a, b) a == b
#define vector_compare_strings(a, b) strcmp(&a,&b) == 0 ? 1 : -1
#define vector_index_of(self, target, index, cmp_fn, t) int index= -1; {\
    int (*fn_ptr)(t, t);\
    fn_ptr = cmp_fn;\
    for(int i = 0; i < self.size; i++) {\
        t candidate = vector_get(self, t, i);\
        int cmp = (*fn_ptr)(target, candidate);\
        if(cmp > 0) index = i;\
    }\
}

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

#define vector_reduce_int(vec, accum, fn) int accum=0;{\
    int (*fn_ptr)(int, int);\
    fn_ptr = fn;\
    for(int i = 0; i < vec.size; i++) { \
        int result = (*fn_ptr)((int)accum, (int)vec.items[i]);\
        accum = result;\
    }\
}

#define vector_reduce_str(vec, accum, fn) {\
    \
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
