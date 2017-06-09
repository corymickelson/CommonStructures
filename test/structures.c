//
// Created by red on 6/7/17.
//

#include "vendor/unity.h"
#include "../vector.h"
#include "../str.h"


void vector_helper_fill_to(vector *vec, int);

void test_vector_init_macro(void) {
    vector_init(v);
    TEST_ASSERT_EQUAL_INT(v.capacity, 100);
    TEST_ASSERT_EQUAL_INT(v.size, 0);
    vector_free(v);
}

void test_vector_init(void) {
    vector v;
    _vector_init(&v);
    TEST_ASSERT_EQUAL_INT(v.capacity, 100);
    TEST_ASSERT_EQUAL_INT(v.size, 0);
    _vector_free(&v);
}

void test_vector_add_str_macro(void) {
    char *expected[2] = {"test value", "value two"};
    vector_init(v);
    vector_add(v, expected[0]);
    vector_add(v, expected[1]);
    for (int i = 0; i < v.size; i++) {
        char *actual = vector_get(v, char*, i);
        TEST_ASSERT_EQUAL_STRING(expected[i], actual);
    }
    vector_free(v);
}

void test_vector_add_str(void) {
    vector v;
    char *expected[2] = {"test value", "value two"};
    _vector_init(&v);
    _vector_add(&v, (void *) expected[0]);
    _vector_add(&v, (void *) expected[1]);
    for (int i = 0; i < v.size; ++i) {
        char *actual = _vector_get(&v, i);
        TEST_ASSERT_EQUAL_STRING(expected[i], actual);
    }
    _vector_free(&v);
}

void test_vector_add_int_macro(void) {
    vector_init(v);
    int x = 3, i = 0;
    int expects[] = {1, 2, 3};
    for (i = 0; i < x; i++) {
        vector_add(v, expects[i]);
    }
    for (i = 0; i < x; ++i) {
        int *actual = vector_get(v, int*, i);
        TEST_ASSERT_EQUAL_INT(expects[i], actual);
    }
    vector_free(v);
}

void test_vector_get_set(void) {
    vector_init(v);
    for (int i = 0; i < 10; i++) {
        to_string(i, buf);
        vector_add(v, buf);
    }
    vector_set(v, 1, "one");
    vector_set(v, 2, "two");
    vector_set(v, 8, "eight");

    int tests[] = {1,2,8};
    char *values[] ={"one", "two", "eight"};

    for (int j = 0; j < 3; j++) {
       char* actual = vector_get(v, char*, tests[j]);
       TEST_ASSERT_EQUAL_STRING(values[j], actual);
    }
    vector_free(v);
}

void test_vector_delete(void) {
    vector_init(vec);
    vector_add(vec, "TEST");
    vector_add(vec, "TWO");
    vector_delete(vec, 1);
    TEST_ASSERT_TRUE(vec.size == 1);
    char* actual = vector_get(vec, char*, 0);
    TEST_ASSERT_EQUAL_STRING("TEST", actual);
    vector_free(vec);
}

void test_vector_contract(void) {
    vector_init(vec);
    vector_helper_fill_to(&vec, 70);
    vector_add(vec, "should force resize");
    TEST_ASSERT_EQUAL_INT(200, vec.capacity);
    int resize_value = (vec.capacity / 10) + vec.size;
    vector_contract(vec);
    TEST_ASSERT_EQUAL_INT(resize_value, vec.capacity);
    TEST_ASSERT_EQUAL_INT(vec.lock_size, true);
    vector_free(vec);
}

void test_vector_expand(void) {
    vector_init(vec);
    vector_helper_fill_to(&vec, 50);
    int expected = 111;
    vector_expand(vec, expected);
    TEST_ASSERT_EQUAL_INT(vec.lock_size, true);
    TEST_ASSERT_EQUAL_INT(vec.capacity, expected);
    vector_free(vec);
}

void vector_helper_fill_to(vector *vec, int x) {
    for (int i = 0; i < x; ++i) {
        to_string(i, str);
        vector_add(*vec, str);
    }
}

int*  test_times_two(int* item) {
    return (int *) ((int)item * 2);
}

int* test_div_two(int* item) {
    return (int*) ((int)item / 2);
}

void test_vector_map(void) {
    vector_init(vec);
    int i =0;
    int initial_values[] = {1, 2, 3, 4};
    int expected_values[] = {2, 4, 6, 8};
    for (; i < 4; i++) {
        vector_add(vec, initial_values[i]);
    }

    vector_map(vec, int*, &test_times_two, map_vec);

    TEST_ASSERT_EQUAL_INT(4, vec.size);
    TEST_ASSERT_EQUAL_INT(false, vec.lock_size);

    TEST_ASSERT_EQUAL_INT(4, map_vec.size);
    TEST_ASSERT_EQUAL_INT(false, map_vec.lock_size);

    for (i = 0; i < 4; ++i) {
        //int* actual = (int*) (map[i]);
        int* actual = vector_get(map_vec, int*, i);
        TEST_ASSERT_EQUAL_INT(expected_values[i], actual);
    }

    vector_map_self(vec, int*, &test_times_two);
    TEST_ASSERT_EQUAL_INT(4, vec.size);
    TEST_ASSERT_EQUAL_INT(false, vec.lock_size);
    for(i =0; i<4; i++) {
        int* actual = vector_get(vec, int*, i);
        TEST_ASSERT_EQUAL_INT(expected_values[i], actual);
    }
    vector_free(vec);
    vector_free(map_vec);
}

int add_reducer(int accum, int item) {
    int sum = accum + item;
    return sum;
}

void test_vector_reduce_int(void) {
    int i = 0;
    vector_init(vec);
    for(;i<10;i++) {
       vector_add(vec, i);
    }
    vector_reduce(vec, int, accum, &add_reducer);
    TEST_ASSERT_EQUAL_INT(45,(int) accum);
    vector_free(vec);
}

char* cat_reducer(char* dest, char* item) {
    strcat(dest, item);
    return dest;
}

void test_vector_reduce_str(void) {
    int i =0;
    vector_init(vec);
    vector_helper_fill_to(&vec, 10);
    char* expected = "0123456789";
    vector_reduce(vec, char*, accum, &cat_reducer)
    TEST_ASSERT_EQUAL_STRING(expected, accum);
    vector_free(vec);
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
    RUN_TEST(test_vector_map);
    RUN_TEST(test_vector_reduce_int);
    RUN_TEST(test_vector_reduce_str);
    UnityEnd();
    return 0;
}
