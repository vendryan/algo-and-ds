#ifndef DYNAMIC_ARRAY_C
#define DYNAMIC_ARRAY_C
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

typedef struct
{
    int size;
    int capacity;
    int *array;
} DynamicArray;

DynamicArray dynamic_array(void)
{
    DynamicArray d_array;
    d_array.size = 0;
    d_array.capacity = 2;
    d_array.array = malloc(sizeof(int) * d_array.capacity);
    if (d_array.array == NULL)
    {
        printf("Malloc error");
        assert(1 == 0);
    }

    return d_array;
}

int size(DynamicArray *d_array)
{
    return d_array->size;
}

int capacity(DynamicArray *d_array)
{
    return d_array->capacity;
}

bool is_empty(DynamicArray *d_array)
{
    return d_array->size == 0;
}

int at(DynamicArray *d_array, int index)
{
    if (index >= d_array->size) 
    {
        printf("Index out of bound\n");
        assert(1 == 0);
    }
    return *(d_array->array + index);
}

static void resize(DynamicArray *d_array, int new_size)
{
    // Make new array
    int *new_array = malloc(sizeof(int) * new_size);
    if (new_array == NULL)
    {
        printf("Allocating memory error");
        assert(1 == 0);
    }

    // Size to copy depend on which size is bigger
    int size_to_copy = new_size > d_array->size ? d_array->size : new_size;
    
    // Fill in the element from old array
    for (int i = 0; i < size_to_copy; ++i)
    {
        new_array[i] = d_array->array[i];
    }
    free(d_array->array);
    d_array->array = new_array;
    d_array->capacity = new_size;
    d_array->size = size_to_copy;
}

void push(DynamicArray *d_array, int item)
{
    if (d_array->size == d_array->capacity)
    {
        resize(d_array, d_array->capacity * 2);
    }

    d_array->array[d_array->size] = item;
    ++d_array->size;
}

void insert(DynamicArray *d_array, int index, int item)
{
    if (index > d_array->size) 
    {
        printf("Index is bigger than size\n");
        assert(1 == 0);
    }
    if (d_array->size == d_array->capacity)
    {
        resize(d_array, d_array->capacity * 2);
    }

    for (int i = d_array->size; i != index; --i)
    {
        d_array->array[i] = d_array->array[i - 1];
    }
    d_array->array[index] = item;
    ++d_array->size;
}

void prepend(DynamicArray *d_array, int item)
{
    insert(d_array, 0, item);
}

int pop(DynamicArray *d_array)
{
    int elem = d_array->array[d_array->size - 1];
    --d_array->size;

    // Resize to half if size is 1/4 capacity
    if (d_array->size / (float)d_array->capacity <= 0.25f)
    {
        resize(d_array, d_array->capacity / 2);
    }
    return elem;
}

void delete(DynamicArray *d_array, int index)
{
    for (int i = index; i != d_array->size; ++i)
    {
        d_array->array[i] = d_array->array[i + 1];
    }
    --d_array->size;
}

void my_remove(DynamicArray *d_array, int item)
{
    int i = 0;

    while (i < d_array->size)
    {
        if (d_array->array[i] == item)
        {
            delete(d_array, i);
        }
        else
        {
            ++i;
        }
    }
}

int find(DynamicArray *d_array, int item)
{
    for (int i = 0; i < d_array->size; ++i)
    {
        if (d_array->array[i] == item)
        {
            return i;
        }
    }
    return -1;
}
#endif