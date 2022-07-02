#include <assert.h>
#include <stdbool.h>

#include "dynamic_array.c"

static void test_size(void)
{
    DynamicArray test = dynamic_array();
    assert(size(&test) == 0);

    push(&test, 8);
    assert(size(&test) == 1);

    push(&test, 9);
    assert(size(&test) == 2);
}

static void test_is_empty(void)
{
    DynamicArray test = dynamic_array();
    assert(is_empty(&test) == 1);

    push(&test, 6);
    assert(is_empty(&test) == 0);
}

static void test_at(void)
{
    DynamicArray test = dynamic_array();
    push(&test, 7);
    push(&test, 8);

    assert(at(&test, 0) == 7);
    assert(at(&test, 1) == 8);
}

static void test_insert(void)
{
    DynamicArray test = dynamic_array();
    insert(&test, 0, 4);
    insert(&test, 0, 5);

    assert(at(&test, 0) == 5);
    assert(at(&test, 1) == 4);
}

static void test_delete(void)
{
    DynamicArray test = dynamic_array();
    push(&test, 4);
    push(&test, 5);
    push(&test, 6);

    delete(&test, 0);

    assert(at(&test, 0) == 5);

    push(&test, 7);
    delete(&test, 1);

    assert(at(&test, 0) == 5);
    assert(at(&test, 1) == 7);
}

static void test_remove(void)
{
    DynamicArray test = dynamic_array();
    push(&test, 4);
    push(&test, 5);
    push(&test, 6);

    my_remove(&test, 4);
    assert(size(&test) == 2);
    assert(at(&test, 0) == 5);

    push(&test, 5);
    push(&test, 5);
    push(&test, 5);

    my_remove(&test, 5);

    assert(size(&test) == 1);
    assert(at(&test, 0) == 6);
}

static void test_pop(void)
{
    DynamicArray test = dynamic_array();
    push(&test, 5);
    push(&test, 6);

    assert(pop(&test) == 6);
    assert(pop(&test) == 5);
    assert(size(&test) == 0);
}

static void test_find(void)
{
    DynamicArray test = dynamic_array();
    push(&test, 5);
    push(&test, 6);

    assert(find(&test, 5) == 0);
    assert(find(&test, 6) == 1);
    assert(find(&test, 789745) == -1);
}

void test(void)
{
    DynamicArray test = dynamic_array();
    
    test_size();
    test_is_empty();
    test_at();
    test_insert();
    test_delete();
    test_remove();
    test_find();
    test_pop();
}