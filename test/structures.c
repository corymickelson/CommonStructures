//
// Created by red on 6/7/17.
//

#include "vendor/unity.h"
#include "../vector.h"


void test_vector_init_macro(void) {
    VECTOR_INIT(v);
    TEST_ASSERT_EQUAL_INT(v.capacity, 100);
    TEST_ASSERT_EQUAL_INT(v.size, 0);
    VECTOR_FREE(v);
}

void test_vector_init(void) {
    vector v;
    vector_init(&v);
    TEST_ASSERT_EQUAL_INT(v.capacity, 100);
    TEST_ASSERT_EQUAL_INT(v.size, 0);
    vector_free(&v);
}

void test_vector_add_str_macro(void) {
    char *expected[2] = {"test value", "value two"};
    VECTOR_INIT(v);
    VECTOR_ADD(v, expected[0]);
    VECTOR_ADD(v, expected[1]);
    for (int i = 0; i < v.size; i++) {
        char *actual = VECTOR_GET(v, char*, i);
        TEST_ASSERT_EQUAL_STRING(expected[i], actual);
    }
    VECTOR_FREE(v);
}

void test_vector_add_str(void) {
    vector v;
    char *expected[2] = {"test value", "value two"};
    vector_init(&v);
    vector_add(&v, (void *) expected[0]);
    vector_add(&v, (void *) expected[1]);
    for (int i = 0; i < v.size; ++i) {
        char *actual = vector_get(&v, i);
        TEST_ASSERT_EQUAL_STRING(expected[i], actual);
    }
    vector_free(&v);
}

void test_vector_add_int_macro(void) {
    VECTOR_INIT(v);
    int x = 3, i = 0;
    int expects[] = {1, 2, 3};
    for (i = 0; i < x; i++) {
        VECTOR_ADD(v, expects[i]);
    }
    for (i = 0; i < x; ++i) {
        int *actual = VECTOR_GET(v, int*, i);
        TEST_ASSERT_EQUAL_INT(expects[i], actual);
    }
    VECTOR_FREE(v);
}

int main(void) {
    UnityBegin("test/structures.c");
    RUN_TEST(test_vector_init_macro);
    RUN_TEST(test_vector_init);
    RUN_TEST(test_vector_add_str_macro);
    RUN_TEST(test_vector_add_str);
    RUN_TEST(test_vector_add_int_macro);
    UnityEnd();
    return 0;
}
