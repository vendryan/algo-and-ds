#ifndef _BINARY_SEARCH_H_
#define _BINARY_SEARCH_H_

// Handle the size 0 array case using ternary
// Not sure why need to cast to int. Maybe because sizeof return unsigned integer so cast it to int
// To avoid overflow
#define ARRAY_SIZE(arr) ((int)sizeof(arr) ? (int)(sizeof(arr) / sizeof((arr)[0])) : 0)

int binary_search_loop(int arr[], int low, int high, int target);
int binary_search_recursion(int arr[], int low, int high, int target);

#endif