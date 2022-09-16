#include <assert.h>
#include <stdio.h>

#include "binary_search.h"

void test(void)
{
    int int_array[] = {1, 3, 5, 7, 9, 13, 19, 29, 30, 41};
    int int_array2[] = {1, 4, 9};
    int int_array3[] = {};
    int int_array4[] = {13, 79};

    printf("Printing array sizes:\n");
    printf("%d\n", ARRAY_SIZE(int_array));
    printf("%d\n", ARRAY_SIZE(int_array2));
    printf("%d\n", ARRAY_SIZE(int_array3));
    printf("%d\n", ARRAY_SIZE(int_array4));

    assert(binary_search_loop(int_array, 0, ARRAY_SIZE(int_array), 9) == 4);
    assert(binary_search_recursion(int_array, 0, ARRAY_SIZE(int_array), 9) == 4);

    assert(binary_search_loop(int_array, 0, ARRAY_SIZE(int_array), 14) == -1);
    assert(binary_search_recursion(int_array, 0, ARRAY_SIZE(int_array), 14) == -1);

    assert(binary_search_loop(int_array2, 0, ARRAY_SIZE(int_array2), 1) == 0);
    assert(binary_search_recursion(int_array2, 0, ARRAY_SIZE(int_array2), 1) == 0);

    assert(binary_search_loop(int_array3, 0, ARRAY_SIZE(int_array3), 1) == -1);
    assert(binary_search_recursion(int_array3, 0, ARRAY_SIZE(int_array3), 1) == -1);

    assert(binary_search_loop(int_array4, 0, ARRAY_SIZE(int_array4), 13) == 0);
    assert(binary_search_loop(int_array4, 0, ARRAY_SIZE(int_array4), 79) == 1);
    assert(binary_search_loop(int_array4, 0, ARRAY_SIZE(int_array4), 80) == -1);
    assert(binary_search_recursion(int_array4, 0, ARRAY_SIZE(int_array4), 13) == 0);
    assert(binary_search_recursion(int_array4, 0, ARRAY_SIZE(int_array4), 79) == 1);
    assert(binary_search_recursion(int_array4, 0, ARRAY_SIZE(int_array4), 80) == -1);

    printf("All success\n");
}