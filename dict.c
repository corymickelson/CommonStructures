//
// Created by red on 6/11/17.
//

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

/**
 * @todo Get is only valid on keys, making comparison simpler since all keys are strings values.
 *
 * @param dict
 * @param k
 * @return
 */
void *_dict_get(dictionary *dict, char *k) {
}
