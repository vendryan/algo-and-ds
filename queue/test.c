// #include "queue_linked_list.c"
#include "queue_array.c"

#include <assert.h>
#include <stdio.h>

void test_empty(void)
{
    // QueueLinkedList queue = make_queue_linked_list();
    QueueArray queue = make_queue_array(3);
    assert(empty(&queue));

    enqueue(&queue, 7);

    assert(!empty(&queue));
}

void test_enqueue_dequeue(void)
{
    // QueueLinkedList queue = make_queue_linked_list();
    QueueArray queue = make_queue_array(4);

    enqueue(&queue, 5);
    enqueue(&queue, 6);
    enqueue(&queue, 7);

    // printf("%d", dequeue(&queue));

    assert(dequeue(&queue) == 5);
    assert(dequeue(&queue) == 6);
    assert(dequeue(&queue) == 7);
    // assert(empty(&queue));
}

void test(void)
{
    test_empty();
    test_enqueue_dequeue();

    printf("All success");
}