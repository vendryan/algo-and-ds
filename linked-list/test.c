#include "linked_list.c"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

void test_size(void)
{
    LinkedList list = make_linked_list();

    assert(size(&list) == 0);
}

void test_empty(void)
{
    LinkedList list = make_linked_list();
    
    assert(empty(&list) == true);

    push_front(&list, 5);

    assert(empty(&list) == false);
}

void test_value_at(void)
{
    LinkedList list = make_linked_list();
    push_front(&list, 6);
    
    assert(value_at(&list, 0) == 6);
}

void test_push_front(void)
{
    LinkedList list = make_linked_list();
    push_front(&list, 6);
    push_front(&list, 5);

    assert(value_at(&list, 0) == 5);
    assert(value_at(&list, 1) == 6);
}

void test_pop_front(void)
{
    LinkedList list = make_linked_list();
    push_front(&list, 6);
    push_front(&list, 5);

    assert(pop_front(&list) == 5);
    assert(pop_front(&list) == 6);
    assert(empty(&list));
}

void test_push_back(void)
{
    LinkedList list = make_linked_list();

    push_back(&list, 6);
    push_back(&list, 5);

    assert(value_at(&list, 0) == 6);
    assert(value_at(&list, 1) == 5);
}

void test_pop_back(void)
{
    LinkedList list = make_linked_list();
    push_front(&list, 6);
    push_front(&list, 5);

    assert(pop_back(&list) == 6);
    assert(pop_back(&list) == 5);
    assert(empty(&list));
}

void test_front(void)
{
    LinkedList list = make_linked_list();
    push_front(&list, 6);
    push_front(&list, 5);

    assert(front(&list) == 5);
}

void test_back(void)
{
    LinkedList list = make_linked_list();
    push_back(&list, 6);
    push_back(&list, 5);

    assert(back(&list) == 5);
}

void test_insert(void)
{
    LinkedList list = make_linked_list();

    push_back(&list, 6);
    push_back(&list, 5);
    insert(&list, 1, 7);

    assert(value_at(&list, 0) == 6);
    assert(value_at(&list, 1) == 7);
}

void test_remove()
{
    LinkedList list = make_linked_list();

    push_back(&list, 6);
    push_back(&list, 5);
    push_back(&list, 7);

    my_remove(&list, 1);

    assert(value_at(&list, 0) == 6);
    assert(value_at(&list, 1) == 7);
}

void test_n_value_from_end(void)
{
    LinkedList list = make_linked_list();

    push_back(&list, 6);
    push_back(&list, 5);
    push_back(&list, 7);

    assert(value_n_from_end(&list, 0) == 7);
    assert(value_n_from_end(&list, 1) == 5);
    assert(value_n_from_end(&list, 2) == 6);
}

void test_reverse(void)
{
    LinkedList list = make_linked_list();

    push_back(&list, 6);
    push_back(&list, 5);
    push_back(&list, 7);

    reverse(&list);
    assert(front(&list) == 7);
    assert(back(&list) == 6);
}

void test_remove_value(void)
{
    LinkedList list = make_linked_list();

    push_back(&list, 6);
    push_back(&list, 5);
    push_back(&list, 7);

    remove_value(&list, 5);
    assert(value_at(&list, 1) == 7);
}

void test(void)
{
    test_size();
    test_empty();
    test_value_at();
    test_push_front();
    test_pop_front();
    test_push_back();
    test_pop_front();
    test_front();
    test_back();
    test_insert();
    test_remove();
    test_n_value_from_end();
    test_reverse();
    test_remove_value();

    printf("All success");
}