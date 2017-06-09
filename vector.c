//
// Created by red on 6/7/17.
//

#include "vector.h"

void _vector_init(vector *vec) {
    vec->size = 0;
    vec->capacity = VECTOR_INIT_CAPACITY;
    vec->items = calloc(sizeof(void *), VECTOR_INIT_CAPACITY);
    vec->lock_size = false;
}

vector_meta _vector_stats(vector *vec) {
    vector_meta vec_size = {
            .capacity = vec->capacity,
            .percent_occupied = (int) (((double) vec->size / vec->capacity) * 100),
            .percent_remaining = (int) (((double) (vec->capacity - vec->size) / vec->capacity) * 100)
    };
    return vec_size;
}

static void _vector_realloc(vector *vec) {
    int current_percent = (int) (((double) vec->size / vec->capacity) * 100);
    int resize_value = NULL;
    if (current_percent >= VECTOR_UPPER_BOUNDS) resize_value = vec->capacity * VECTOR_RESIZE_FACTOR;
    else if (current_percent <= VECTOR_LOWER_BOUNDS&&
             vec->capacity > VECTOR_INIT_CAPACITY)
        resize_value = (vec->capacity / VECTOR_RESIZE_FACTOR) * 2;
    else return;

#ifdef LOG_DEBUG
    printf("vector_resize: %d to %d\n", vec->capacity, resize_value)
#endif

    void *items = realloc(vec->items, sizeof(void *) * resize_value);
    if (items) {
        vec->items = items;
        vec->capacity = resize_value;
    }
}

static bool vector_check(vector *vec, int index) {
    if (vec->capacity < index || index < 0) {
        printf("index out of bounds");
        return false;
    }
    if (index > vec->size) {
        printf("head of vector at: %d\nattempted to add item at %d\nUse the vector_add method",
               vec->size, index);
        return false;
    }
    return true;
}

void _vector_add(vector *vec, void *item) {
    if (vec->lock_size) {
        if (vec->size == vec->capacity) {
            printf("Can not add to vector\nVector growth frozen.Vector at capacity.");
            return;
        }
    }
    else _vector_realloc(vec);

    vec->items[vec->size++] = item;
}

void _vector_set(vector *vec, int index, void *item) {
    if (!vector_check(vec, index)) return;
    vec->items[index] = item;
}

void *_vector_get(vector *vec, int index) {
    if (vec->size < index || index < 0) {
        printf("index out of bounds");
        return NULL;
    }
    return vec->items[index];
}

void _vector_delete(vector *vec, int index) {
    _vector_stats(vec);
    if (!vector_check(vec, index)) return;
    for (; index <= vec->size - 1; index++) {
        int next = index + 1;
        vec->items[index] = vec->items[next];
    }
    vec->items[vec->size] = NULL;
    vec->size--;
}

void _vector_free(vector *vec) {
    free(vec->items);
}

void _vector_expand(vector *vec, int capped) {
    if(vec->size > capped) {
        printf("Can not resize to length less than that currently occupied.");
        return;
    }
    void *items = realloc(vec->items, sizeof(void *) * capped);
    vec->items = items;
    vec->capacity = capped;
    vec->lock_size = true;
}

void _vector_contract(vector *vec) {
    int resize_value = (vec->capacity / 10) + vec->size;
    void *items = realloc(vec->items, sizeof(void *) * resize_value);
    vec->capacity = resize_value;
    vec->items = items;
    vec->lock_size = true;
}

