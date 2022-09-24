#include <stdio.h>

int set_bit(int x, int position)
{
    int mask = 1 << position;
    return x | mask;
}

int clear_bit(int x, int position)
{
    // int mask = 0xFFFFFFFF ^ (1 << position);
    int mask = 1 << position;
    return x & ~mask;
}

int flip_bit(int x, int position)
{
    int mask = 1 << position;
    return x ^ mask;
}

int is_bit_set(int x, int position)
{
    return (x >> position) & 1;
}

int modify_bit(int x, int position, int state)
{
    int mask = 1 << position;
    return (mask & ~mask) | (-state & mask);
}

int popcnt32(int x)
{
    int a = (x & 0x55555555) + ((x >> 1)  & 0x55555555);  // count of each 2 bit into each 2 bit
    int b = (a & 0x33333333) + ((a >> 2)  & 0x33333333);  // count of each 4 bit into each 4 bit
    int c = (b & 0x0F0F0F0F) + ((b >> 4)  & 0x0F0F0F0F);  // count of each 8 bit into each 8 bit
    int d = (c & 0x00FF00FF) + ((c >> 8)  & 0x00FF00FF);   // count of each 16 bit into each 16 bit
    int e = (d & 0x0000FFFF) + ((d >> 16) & 0x0000FFFF); // count of each 32 bit into each 32 bit
    return e;
}

// Write the function to count the number of bits that are different between 2 numbers
int different_bit(int x, int y)
{
    return popcnt(x ^ y);
}

int main(void)
{
    printf("sum bit 1: %d\n", popcnt32(1));
    printf("sum bit 2: %d\n", popcnt32(2));
    printf("sum bit 3: %d\n", popcnt32(3));
    printf("sum bit 4: %d\n", popcnt32(4));
    printf("sizeof(int): %d\n", sizeof(int));
    return 0;
}