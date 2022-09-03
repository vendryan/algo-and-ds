#ifndef QUEUE_LINKED_LIST_C
#define QUEUE_LINKED_LIST_C

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

typedef struct QueueLinkedList
{
    int size;
    Node *head;
    Node *tail;
} QueueLinkedList;

int size(QueueLinkedList *list)
{
    return list->size;
}

void push_front(QueueLinkedList *list, int val)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->value = val;

    // Pointer changing ;)
    new_node->next = list->head;
    if (list->head == NULL)
    {
        list->tail = new_node;
    }
    list->head = new_node;
    ++list->size;
}

int pop_back(QueueLinkedList *list)
{
    if (list->tail == NULL)
    {
        printf("***ERROR: Linked list is empty");
        assert(1 == 0);
    }

    Node *to_be_popped = list->tail;
    int val = to_be_popped->value;

    --list->size;
    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        for (Node *ptr = list->head; ptr != NULL; ptr = ptr->next)
        {
            if (ptr->next == list->tail)
            {
                ptr->next = NULL;
                list->tail = ptr;
                break;
            }
        }
    }
    free(to_be_popped);

    return val;
}

QueueLinkedList make_queue_linked_list(void)
{
    QueueLinkedList new_list;
    new_list.size = 0;
    new_list.head = NULL;
    new_list.tail = NULL;

    return new_list;
}

bool empty(QueueLinkedList *queue)
{
    return queue->head == NULL;
}

void enqueue(QueueLinkedList *queue, int val)
{
    push_front(queue, val);
    return;
}

int dequeue(QueueLinkedList *queue)
{
    return pop_back(queue);
}

#endif