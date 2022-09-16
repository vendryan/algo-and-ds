#include <stdio.h>

#include "binary_search.h"


int binary_search_loop(int arr[], int low, int high, int target)
{
    while (low < high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] > target)
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }

    return -1;
}

int binary_search_recursion(int arr[], int low, int high, int target)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] > target)
        {
            return binary_search_recursion(arr, low, mid, target);
        }
        else
        {
            return binary_search_recursion(arr, mid + 1, high, target);
        }
    }

    return -1;
}