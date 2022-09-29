#ifndef _BINARY_SEARH_TREE_H_
#define _BINARY_SEARH_TREE_H_

#include <stdbool.h>
#include <math.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))


typedef struct BST_Node {
    struct BST_Node *parent;
    struct BST_Node *left;
    struct BST_Node *right;
    int data;
}
BST_Node;

typedef struct BST_BinarySearchTree {
    struct BST_Node *root;
}
BST_BinarySearchTree;


BST_BinarySearchTree BST_make_bst(void);
void BST_insert(BST_BinarySearchTree *bst, int data);
int BST_get_node_count(BST_BinarySearchTree *bst);
void BST_print_values(BST_BinarySearchTree *bst);
void BST_delete_tree(BST_BinarySearchTree *bst);
bool BST_is_in_tree(BST_BinarySearchTree *bst, int data);
int BST_get_max(BST_BinarySearchTree *bst);
int BST_get_min(BST_BinarySearchTree *bst);
bool BST_is_binary_search_tree(BST_BinarySearchTree *bst);
void BST_delete_value(BST_BinarySearchTree *bst, int value);
int BST_get_successor(BST_BinarySearchTree *bst, int value);

#endif