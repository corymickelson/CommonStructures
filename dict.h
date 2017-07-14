//
// Created by red on 6/11/17.
//

#ifndef STRUCTURES_DICT_H
#define STRUCTURES_DICT_H

#include "vector.h"

#define dict_init(dict) dictionary dict ; _dict_init(&dict)
#define dict_free(dict) _dict_free(&dict)
#define dict_set(dict, item) _dict_set(&dict, &item)
#define dict_get(dict, t, key) (t) _dict_get(&dict, key)

typedef struct dict_entry {
    char *key;
    void *value;
};
typedef struct {
    vector keys;
    vector values;
} dictionary;

void _dict_init(dictionary *);

void _dict_free(dictionary *);

void _dict_set(dictionary *, struct dict_entry *);

void *_dict_get(dictionary *, char *);

#endif //STRUCTURES_DICT_H
