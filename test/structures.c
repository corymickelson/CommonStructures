//
// Created by red on 6/7/17.
//

#include "vendor/unity.h"
#include "../vector.h"
#include "../str.h"


void fill_x_vector_helper(vector *vec, int);

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

void test_vector_get_set(void) {
    VECTOR_INIT(v);
    for (int i = 0; i < 10; i++) {
        TO_STRING(i, buf);
        VECTOR_ADD(v, buf);
    }
    VECTOR_SET(v, 1, "one");
    VECTOR_SET(v, 2, "two");
    VECTOR_SET(v, 8, "eight");

    int tests[] = {1,2,8};
    char *values[] ={"one", "two", "eight"};

    for (int j = 0; j < 3; j++) {
       char* actual = VECTOR_GET(v, char*, tests[j]);
       TEST_ASSERT_EQUAL_STRING(values[j], actual);
    }
   VECTOR_FREE(v);
}

void test_vector_delete(void) {
    VECTOR_INIT(vec);
    VECTOR_ADD(vec, "TEST");
    VECTOR_ADD(vec, "TWO");
    VECTOR_DELETE(vec, 1);
    TEST_ASSERT_TRUE(vec.size == 1);
    char* actual = VECTOR_GET(vec, char*, 0);
    TEST_ASSERT_EQUAL_STRING("TEST", actual);
    VECTOR_FREE(vec);
}

void test_vector_contract(void) {
    VECTOR_INIT(vec);
    fill_x_vector_helper(&vec, 70);
    VECTOR_ADD(vec, "should force resize");
    TEST_ASSERT_EQUAL_INT(200, vec.capacity);
    int resize_value = (vec.capacity / 10) + vec.size;
    VECTOR_CONTRACT(vec);
    TEST_ASSERT_EQUAL_INT(resize_value, vec.capacity);
    TEST_ASSERT_EQUAL_INT(vec.lock_size, true);
    VECTOR_FREE(vec);
}

void test_vector_expand(void) {
    VECTOR_INIT(vec);
    fill_x_vector_helper(&vec, 50);
    int expected = 111;
    VECTOR_EXPAND(vec, expected);
    TEST_ASSERT_EQUAL_INT(vec.lock_size, true);
    TEST_ASSERT_EQUAL_INT(vec.capacity, expected);
    VECTOR_FREE(vec);
}

void fill_x_vector_helper(vector *vec, int x) {
    for (int i = 0; i < x; ++i) {
        TO_STRING(i, str);
        VECTOR_ADD(*vec, str);
    }
}


int main(void) {
    UnityBegin("test/structures.c");
    RUN_TEST(test_vector_init_macro);
    RUN_TEST(test_vector_init);
    RUN_TEST(test_vector_add_str_macro);
    RUN_TEST(test_vector_add_str);
    RUN_TEST(test_vector_add_int_macro);
    RUN_TEST(test_vector_get_set);
    RUN_TEST(test_vector_delete);
    RUN_TEST(test_vector_contract);
    RUN_TEST(test_vector_expand);
    UnityEnd();
    return 0;
}
