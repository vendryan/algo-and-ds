#ifndef QUEUE_ARRAY_C
#define QUEUE_ARRAY_C

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct CircularBuffer
{
    int front_ptr;
    int back_ptr;
    int size;
    int *array;
} CircularBuffer;

static CircularBuffer make_circular_buffer(int size)
{
    CircularBuffer buffer;
    buffer.front_ptr = 0;
    buffer.back_ptr = 0;
    buffer.size = size;
    buffer.array = malloc(sizeof(int) * size);

    return buffer;
}

static bool c_empty(CircularBuffer *buffer)
{
    return buffer->front_ptr == buffer->back_ptr;
}

static bool c_full(CircularBuffer *buffer)
{
    return (buffer->front_ptr - buffer->back_ptr == 1) ||
            (buffer->front_ptr == 0 && buffer->back_ptr == (buffer->size - 1));
            // ^ the case where the front_ptr is at the beginning and back_ptr at the end
}

static void push(CircularBuffer *buffer, int val)
{
    if (c_full(buffer))
    {
        printf("The size is full\n");
        assert(1 == 0);
    }

    *(buffer->array + buffer->back_ptr) = val;
    buffer->back_ptr = (buffer->back_ptr + 1) % buffer->size;
}

static int pop(CircularBuffer *buffer)
{
    if (c_empty(buffer))
    {
        printf("There is no element inside the buffer\n");
        assert(1 == 0);
    }

    int val = *(buffer->array + buffer->front_ptr);
    buffer->front_ptr = (buffer->front_ptr + 1) % buffer->size;

    return val;
}

typedef CircularBuffer QueueArray;

// O(1)
QueueArray make_queue_array(int size)
{
    return make_circular_buffer(size);
}

// O(1)
void enqueue(QueueArray *queue, int val)
{
    push(queue, val);
}

// O(1)
int dequeue(QueueArray *queue)
{
    return pop(queue);
}

bool empty(CircularBuffer *queue)
{
    return c_empty(queue);
}

#endif