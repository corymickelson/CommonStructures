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
#define dict_remove(dict, key) _dict_remove(&dict, key)
/**
 * @def iterate over each key/value in dictionary.
 *      Any changes are made to self.
 *
 * @property fn - function to be called on each key/value.
 *      fn takes a char * (key), and (t) (value). Return value is assigned to value
 *
 * @see structures for test examples
 */
#define dict_foreach(self, t, fn) {\
    t (*fn_ptr)(char*, t);\
    fn_ptr = fn;\
    for(int i = 0; i < self.keys.size; i++) {\
        char* k = vector_get(self.keys, char*, i);\
        t v = vector_get(self.values, t, i);\
        t v_fn = (*fn_ptr)(k, v);\
        vector_set(self.values, i, v_fn);\
    }\
}

struct dict_entry {
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

void _dict_remove(dictionary *, char *);

#endif //STRUCTURES_DICT_H
