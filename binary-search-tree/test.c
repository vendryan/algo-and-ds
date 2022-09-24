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

    BST_print_values(&bst);
    printf("\n");
}

void test_delete_tree(void)
{
    BST_BinarySearchTree bst = BST_make_bst();
    BST_insert(&bst, 5);
    BST_insert(&bst, 3);
    BST_insert(&bst, 4);
    BST_insert(&bst, 2);
    BST_insert(&bst, 6);

    BST_delete_tree(&bst);

    assert(bst.root == NULL);
    assert(BST_get_node_count(&bst) == 0);

    BST_print_values(&bst);


    printf("\n");
}

void test_get_node_count(void)
{
    BST_BinarySearchTree bst = BST_make_bst();
    BST_insert(&bst, 5);
    BST_insert(&bst, 3);
    BST_insert(&bst, 4);
    BST_insert(&bst, 2);
    BST_insert(&bst, 6);

    assert(BST_get_node_count(&bst) == 5);

    BST_insert(&bst, 7);

    assert(BST_get_node_count(&bst) == 6);
}

void test_in_tree(void)
{
    BST_BinarySearchTree bst = BST_make_bst();
    BST_insert(&bst, 5);
    BST_insert(&bst, 3);
    BST_insert(&bst, 4);
    BST_insert(&bst, 2);
    BST_insert(&bst, 6);

    assert(BST_is_in_tree(&bst, 5));
    assert(BST_is_in_tree(&bst, 3));
    assert(BST_is_in_tree(&bst, 4));
    assert(BST_is_in_tree(&bst, 2));
    assert(BST_is_in_tree(&bst, 6));
    assert(!BST_is_in_tree(&bst, 17));
    assert(!BST_is_in_tree(&bst, 7));
    assert(!BST_is_in_tree(&bst, 1));
}

void test(void)
{
    test_insert_print();
    test_get_node_count();
    test_in_tree();
    test_delete_tree();
    printf("All success !!\n");
}