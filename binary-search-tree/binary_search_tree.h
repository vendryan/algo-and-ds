#ifndef _BINARY_SEARH_TREE_H_
#define _BINARY_SEARH_TREE_H_

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
void print_values(BST_BinarySearchTree *bst);

#endif