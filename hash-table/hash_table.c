#ifndef HASH_TABLE_C_LINEAR_PROBING
#define HASH_TABLE_C_LINEAR_PROBING

#include <stdint.h> /* uint32_t uint64_t */
#include <stdlib.h> /* malloc free */
#include <string.h> /* strlen */
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "murmur_hash.c"

typedef struct
{
    int key;
    int value;
    bool is_deleted;
    bool initialized;
} 
KeyValuePair;

// HashTable Struct
typedef struct
{
    int capacity;
    int size;
    KeyValuePair *kvs;
} 
HashTable;

// This is multiplicative hashing
static uint32_t hash_int(uint32_t val, uint32_t m)
{
    uint32_t a = 3131955893;
    uint32_t w = 32;
    // See https://stackoverflow.com/questions/1835976/what-is-a-sensible-prime-for-hashcode-calculation/2816747#2816747
    // Big odd number
    return (a * val) >> (w - m);
}

// Using fnv hash
// See https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1_hash
static uint64_t hash_string_fnv(char *string)
{
    uint64_t hash = 14695981039346656037LLU;
    uint64_t fnv_prime = 1099511628211LLU;

    for (int i = 0; i < strlen(string); ++i)
    {
        hash ^= (uint64_t)string[i];
        hash *= fnv_prime;
    }

    return hash;
}

static int hash(int key, int m)
{
    return hash_int(key, m / 2) % m;
}  

HashTable make_hash_table(int capacity)
{
    HashTable new_hash_table;
    new_hash_table.capacity = capacity;
    new_hash_table.size = 0;
    // Calloc initialize memory to 0
    new_hash_table.kvs = calloc(new_hash_table.capacity, sizeof(KeyValuePair));

    return new_hash_table;
}

void add(HashTable *table, int key, int value)
{
    if (table->size == table->capacity)
    {
        printf("Hash table is full");
        assert(0);
    }

    int index = hash(key, table->capacity);
    printf("hashing %d into %d\n", key, index);

    KeyValuePair pair = { 
        .key=key, 
        .value=value, 
        .is_deleted=false, 
        .initialized=true
    };
    
    // Linear probing.
    // When initialized and not deleted, don't hash into that position
    while ((*(table->kvs + index)).initialized && !(*(table->kvs + index)).is_deleted)
    {
        index = (index + 1) % table->capacity;
    }
    *(table->kvs + index) = pair;
    ++table->size;
}

bool exists(HashTable *table, int key)
{
    int index = hash(key, table->capacity);
    int count = 0;
    KeyValuePair current_kv = *(table->kvs + index);
    while (current_kv.initialized)
    {
        // It exist
        if (!current_kv.is_deleted && current_kv.key == key)
        {
            return true;
        }
        // Already search through all of the hash
        if (count++ >= table->size)
        {
            break;
        }

        index = (index + 1) % table->capacity;
        current_kv = *(table->kvs + index);
    }

    return false;
}

int get(HashTable *table, int key)
{
    int index = hash(key, table->capacity);
    int count = 0;
    KeyValuePair current_kv = *(table->kvs + index);

    while (current_kv.initialized)
    {
        // It exist
        if (!current_kv.is_deleted && current_kv.key == key)
        {
            return current_kv.value;
        }
        // Already search through all of the hash
        if (count++ >= table->size)
        {
            break;
        }

        index = (index + 1) % table->capacity;
        current_kv = *(table->kvs + index);
    }

    printf("Given key not exist inside hash table\n");
    assert(0);
}

void my_remove(HashTable *table, int key)
{
    int index = hash(key, table->capacity);
    int count = 0;
    // KeyValuePair kv = *(table->kvs + index);
    while ((*(table->kvs + index)).initialized)
    {
        // It exist
        if (!(*(table->kvs + index)).is_deleted && (*(table->kvs + index)).key == key)
        {
            printf("Removing key %d in index %d\n", key, index);
            (*(table->kvs + index)).is_deleted = true;
            --table->size;
            return;
        }
        // Already search through all of the hash
        if (count++ >= table->size)
        {
            return;
        }

        index = (index + 1) % table->capacity;
    }
}

// int main(void)
// {
//     printf("%u\n", hash(0, 8));
//     printf("%u\n", hash(1, 8));
//     printf("%u\n", hash(2, 8));
//     printf("%u\n", hash(3, 8));
//     printf("%u\n", hash(4, 8));
//     printf("%u\n", hash(5, 8));
//     printf("%u\n", hash(6, 8));
//     printf("%u\n", hash(7, 8));
//     printf("%llu\n", murmur_hash_string("Butet", 0) % 32);
//     printf("%llu\n", murmur_hash_string("What", 0) % 32);
//     printf("%llu\n", murmur_hash_string("Biba", 0) % 32);
//     printf("%llu\n", murmur_hash_string("Bobi", 0) % 32);
//     printf("%llu\n", murmur_hash_string("Babi", 0) % 32);
//     return 0;
// }

#endif