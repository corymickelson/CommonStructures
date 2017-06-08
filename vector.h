//
// Created by red on 6/7/17.
//

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef STRUCTURES_VECTOR_H
#define STRUCTURES_VECTOR_H

#define VECTOR_INIT(vec) vector vec; vector_init(&vec)
#define VECTOR_ADD(vec, item) vector_add(&vec, (void*) item)
#define VECTOR_SET(vec, id, item) vector_set(&vec, id, (void*) item)
#define VECTOR_GET(vec, t, id) (t) vector_get(&vec, id)
#define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
#define VECTOR_SIZE(vec) vector_meta meta; vector_size(&vec)
#define VECTOR_FREE(vec) vector_free(&vec)
#define VECTOR_EXPAND(vec) vector_expand(&vec)
#define VECTOR_CONTRACT(vec) vector_contract(&vec)

#define VECTOR_INIT_CAPACITY 100
#define VECTOR_RESIZE_FACTOR 2
#define VECTOR_RESIZE_EXPAND_AT_PERCENT 0.7
#define VECTOR_RESIZE_CONTRACT_AT_PERCENT 0.3

typedef struct {
    int capacity;
    int size;
    void **items;
    bool lock_size;
} vector;

typedef struct {
    int capacity;
    double remaining;
    double occupied;
} vector_meta;

void vector_init(vector *);

vector_meta vector_size(vector *);

static void vector_resize(vector *);

void vector_add(vector *, void *);

void vector_set(vector *, int, void *);

void *vector_get(vector *, int);

void vector_delete(vector *, int);

void vector_free(vector *);

void vector_contract(vector*);

void vector_expand(vector *, int);
#endif //STRUCTURES_VECTOR_H
