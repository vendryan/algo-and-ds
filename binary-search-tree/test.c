#include "binary_search_tree.h"

#include <stdio.h>
#include <assert.h>

void test_insert_print(void)
{
    BST_BinarySearchTree bst = BST_make_bst();
    BST_insert(&bst, 5);
    BST_insert(&bst, 3);
    BST_insert(&bst, 4);
    BST_insert(&bst, 2);
    BST_insert(&bst, 6);

    assert((bst.root)->data == 5);

    print_values(&bst);
    printf("\n");
}

void test(void)
{
    test_insert_print();
    printf("All success !!\n");
}