//
// Created by red on 6/7/17.
//

#include <sybdb.h>
#include "vector.h"

void vector_init(vector *vec) {
    vec->size = 0;
    vec->capacity = VECTOR_INIT_CAPACITY;
    vec->items = calloc(sizeof(void *), VECTOR_INIT_CAPACITY);
    vec->freeze_growth = FALSE;
}

vector_meta vector_size(vector *vec) {
    vector_meta vec_size = {
            .capacity = vec->capacity,
            .occupied = (vec->size / vec->capacity) * 100,
            .remaining = ((vec->capacity - vec->size) / vec->capacity) * 100
    };
    return vec_size;
}

static void vector_resize(vector *vec) {
    int lower_bounds = (int) (vec->capacity * VECTOR_RESIZE_CONTRACT_AT_PERCENT);
    int upper_bounds = (int) (vec->capacity * VECTOR_RESIZE_EXPAND_AT_PERCENT);
    int current_percent = vec->size / vec->capacity * 100;
    int resize_value = NULL;
    if (current_percent >= upper_bounds) resize_value = vec->capacity * VECTOR_RESIZE_FACTOR;
    else if (current_percent <= lower_bounds &&
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

static BOOL vector_check(vector *vec, int index) {
    if (vec->capacity > index || index < 0) {
        printf("index out of bounds");
        return FALSE;
    }
    if (index > vec->size) {
        printf("head of vector at: %d\nattempted to add item at %d\nUse the vector_add method",
               vec->size, index);
        return FALSE;
    }
    return TRUE;
}

void vector_add(vector *vec, void *item) {
    if (vec->freeze_growth) {
        if (vec->size == vec->capacity) {
            printf("Can not add to vector\nVector growth frozen.Vector at capacity.");
            return;
        }
    }
    else vector_resize(vec);

    vec->items[vec->size++] = item;
}

void vector_set(vector *vec, int index, void *item) {
    if (!vector_check(vec, index)) return;
    vec->items[index] = item;
}

void *vector_get(vector *vec, int index) {
    if (vec->size < index || index < 0) {
        printf("index out of bounds");
        return NULL;
    }
    return vec->items[index];
}

void vector_delete(vector *vec, int index) {
    vector_size(vec);
    if (!vector_check(vec, index)) return;
    for (; index <= vec->size - 1; index++) {
        int next = index + 1;
        vec->items[index] = vec->items[next];
    }
    vec->items[vec->size] = NULL;
    vec->size--;
}

void vector_free(vector *vec) {
    free(vec->items);
}

void vector_expand(vector *vec, int capped) {
    void *items = realloc(vec->items, sizeof(void *) * capped);
    vec->items = items;
    vec->capacity = capped;
    vec->freeze_growth = TRUE;
}

void vector_contract(vector *vec) {
    vector_meta sizing = vector_size(vec);
    int resize_value = (int) sizing.occupied + ((10 / sizing.capacity) * 100);
    void *items = realloc(vec->items, sizeof(void *) * resize_value);
    vec->items = items;
    vec->freeze_growth = TRUE;
}
