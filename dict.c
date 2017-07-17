//
// Created by red on 6/11/17.
//

#include <string.h>
#include <assert.h>
#include "dict.h"

void _dict_init(dictionary *dict) {
    vector_init(keys);
    vector_init(vals);
    dict->keys = keys;
    dict->values = vals;
}

void _dict_free(dictionary *dict) {
    vector_free(dict->keys);
    vector_free(dict->values);
}

void _dict_set(dictionary *dict, struct dict_entry *item) {
    vector_add(dict->keys, item->key);
    vector_add(dict->values, item->value);
}

int _dict_key_compare(char *target, char *candidate) {
    int match = strcmp(target, candidate);
    return match == 0 ? 1 : -1;
}

/**
 * @todo Get is only valid on keys, making comparison simpler since all keys are strings values.
 *
 * @param dict
 * @param k
 * @return
 */
void *_dict_get(dictionary *dict, char *k) {
    vector_index_of(dict->keys, k, idx, _dict_key_compare, char*);
    if (idx == -1) return NULL;
    void *val = vector_get(dict->values, void*, idx);
    return val;
}

void _dict_remove(dictionary *dict, char *k) {
    vector_index_of(dict->keys, k, idx, _dict_key_compare, char*);
    assert(dict->keys.size == dict->values.size);
    vector_delete(dict->keys, idx);
    vector_delete(dict->values, idx);
    assert(dict->keys.size == dict->values.size);
}
