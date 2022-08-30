#ifndef LINKED_LIST_C
#define LINKED_LIST_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    int size;
    Node *head;
    Node *tail;
} LinkedList;

LinkedList make_linked_list(void)
{
    LinkedList new_list;
    new_list.size = 0;
    new_list.head = NULL;
    new_list.tail = NULL;

    return new_list;
}

int size(LinkedList *list)
{
    return list->size;
}

bool empty(LinkedList *list)
{
    return list->head == NULL;
}

int value_at(LinkedList *list, int index)
{
    Node *cur_node = list->head;
    while (cur_node != NULL && index != 0)
    {
        cur_node = cur_node->next;
        --index;
    }

    return cur_node->value;
}

void push_front(LinkedList *list, int val)
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

int pop_front(LinkedList *list)
{
    Node *to_be_popped = list->head;
    list->head = to_be_popped->next;
    if (list->head == NULL)
    {
        list->tail = NULL;
    }

    int val = to_be_popped->value;
    free(to_be_popped);
    --list->size;

    return val;
}

void push_back(LinkedList *list, int val)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->value = val;
    new_node->next = NULL;

    ++list->size;
    // Pointer changing ;)
    if (list->head != NULL)
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    else
    {
        list->head = new_node;
        list->tail = new_node;
    }
}

int pop_back(LinkedList *list)
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
        Node *ptr = list->head;
        while (ptr == list->tail)
        {
            ptr->next = NULL;
            break;
        }
    }
    free(to_be_popped);

    return val;
}

int front(LinkedList *list)
{
    if (list->head == NULL)
    {
        printf("The list is empty");
        assert(0);
    }

    return list->head->value;
}

int back(LinkedList *list)
{
    if (list->tail == NULL)
    {
        printf("The list is empty");
        assert(0);
    }

    return list->tail->value;
}

void insert(LinkedList *list, int index, int val)
{
    // Error checking as always
    if (index > list->size)
    {
        printf("***ERROR: Index is bigger than the Linked List size");
        assert(0);
    }

    if (index == 0)
    {
        push_front(list, val);
    }
    else if (index == list->size)
    {
        push_back(list, val);
    }
    else
    {
        Node *new_node = malloc(sizeof(Node));
        new_node->value = val;

        Node *ptr = list->head;
        ++list->size;
        while (index != 0)
        {
            // Insert after this node!
            if (index - 1 == 0)
            {
                new_node->next = ptr->next;
                ptr->next = new_node;
                break;
            }
            else
            {
                --index;
                ptr = ptr->next;
            }
        }
    }
}

void my_remove(LinkedList *list, int index)
{
    // Error checking as always
    if (index >= list->size)
    {
        printf("***ERROR: Index is bigger than the Linked List size");
        assert(0);
    }

    if (index == 0)
    {
        pop_front(list);
    }
    else if (index == list->size - 1)
    {
        pop_back(list);
    }
    else
    {
        Node *ptr = list->head;
        --list->size;
        while (index != 0)
        {
            if (index - 1 == 0)
            {
                Node *to_be_freed = ptr->next;
                ptr->next = ptr->next->next;
                free(to_be_freed);
                break;
            }
            else
            {
                --index;
                ptr = ptr->next;
            }
        }
    }
}

int value_n_from_end(LinkedList *list, int index)
{
    // Error checking as always
    if (index >= list->size)
    {
        printf("***ERROR: Index is bigger than the Linked List size");
        assert(0);
    }

    return value_at(list, (list->size - 1) - index);
}

void reverse(LinkedList *list)
{
    // if length is less or equal to one do nothing
    // Only do soemthing when the size is bigger than one
    if (list->size > 1)
    {
        Node *cur_node = list->head;
        Node *next_node = cur_node->next;
        Node *next_next_node = next_node == NULL ? NULL : next_node->next;

        cur_node->next = NULL;
        /**
         *   ___         ___          ___
         *  | x |------>| x |------->| x | ...
         *   ---         ---          ---
         *    ^           ^            ^
         * cur_node    next_node    next_next_node
         */
        while (next_node != NULL)
        {
            // Point the next_node to the current_node
            next_node->next = cur_node;
            // The next_node become current node
            cur_node = next_node;
            // The next_next_node become next_node
            next_node = next_next_node;
            // Get the next_next_node so that we don't lost the pointer
            // It can be NULL so need to check first
            next_next_node = next_node == NULL ? NULL : next_node->next;
        }
        Node *old_head = list->head;
        list->head = list->tail;
        list->tail = old_head;
    }
}

void remove_value(LinkedList *list, int val)
{
    if (list->head->value == val)
    {
        pop_front(list);
        return;
    }

    for (Node *cur_node = list->head; 
         cur_node != NULL && cur_node->next != NULL;
         cur_node = cur_node->next)
    {
        if (cur_node->next->value == val)
        {
            Node *to_be_freed = cur_node->next;
            if (to_be_freed->next == NULL)
            {
                cur_node->next = NULL;
                list->tail = cur_node;
                free(to_be_freed);
            }
            else
            {
                cur_node->next = to_be_freed->next;
                free(to_be_freed);
            }
            --list->size;
            return;
        }
    }
}

void print_list(LinkedList *list)
{
    Node *cur_node = list->head;
    while (cur_node != NULL)
    {
        printf("%d\n", cur_node->value);
        cur_node = cur_node->next;
    }
}


#endif