#include "hash_table.c"

#include <assert.h>
#include <stdio.h>

void test_hash_table(void)
{
    // QueueLinkedList queue = make_queue_linked_list();
    HashTable table = make_hash_table(8);
    add(&table, 4, 2093);
    add(&table, 5, 786);
    add(&table, 6, 93);

    printf("Hash of 4 is %d\n", hash(4, 8));
    printf("Hash of 5 is %d\n", hash(5, 8));
    printf("Hash of 6 is %d\n", hash(6, 8));

    // Test exist
    assert(exists(&table, 4));
    assert(exists(&table, 5));
    assert(exists(&table, 6));
    assert(!exists(&table, 3874));
    assert(!exists(&table, 7));
    assert(!exists(&table, 3274));

    // Test get
    assert(get(&table, 4) == 2093);
    assert(get(&table, 5) == 786);
    assert(get(&table, 6) == 93);

    // Test remove
    my_remove(&table, 4);
    my_remove(&table, 5);

    assert(!exists(&table, 4));
    assert(!exists(&table, 5));
    printf("Table size now is %d\n", table.size);
    assert(exists(&table, 6));
}

void test(void)
{
    test_hash_table();
    printf("All success\n");
}