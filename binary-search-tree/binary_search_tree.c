#include "binary_search_tree.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

static BST_Node *BST_insert_node(BST_Node *parent, BST_Node *node, int data);
static BST_Node *BST_make_new_node(void);
static int BST_get_node_count_root(BST_Node *node);
static void print_values_node(BST_Node *node);
static void delete_tree_node(BST_Node *node);
static void search(BST_Node *node, int data);

BST_BinarySearchTree BST_make_bst(void)
{
    BST_BinarySearchTree new_bst = { .root = NULL };
    return new_bst;
}

static BST_Node *BST_make_new_node(void)
{
    BST_Node *new_node = malloc(sizeof(BST_Node));
    return new_node;
}

void BST_insert(BST_BinarySearchTree *bst, int data)
{
    if (bst->root == NULL)
    {
        bst->root = BST_make_new_node();
        bst->root->left = NULL;
        bst->root->right = NULL;
        bst->root->parent = NULL;
        bst->root->data = data;
    }
    else 
    {
        BST_insert_node(NULL, bst->root, data);
    }
}

static BST_Node *BST_insert_node(BST_Node *parent, BST_Node *node, int data)
{
    if (node == NULL)
    {
        BST_Node *new_node = BST_make_new_node();
        new_node->parent = parent;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->data = data;

        return new_node;
    }
    else if (data < node->data)
    {
        node->left = BST_insert_node(node, node->left, data);
    }
    else
    {
        node->right = BST_insert_node(node, node->right, data);
    }

    return node;
}

int BST_get_node_count(BST_BinarySearchTree *bst)
{
    return BST_get_node_count_root(bst->root);
}

static int BST_get_node_count_root(BST_Node *node)
{
    if (node == NULL) return 0;
    return 1 + BST_get_node_count_root(node->left) + BST_get_node_count_root(node->right);
}

void print_values(BST_BinarySearchTree *bst)
{
    print_values_node(bst->root);
}

static void print_values_node(BST_Node *node)
{
    if (node == NULL) return;
    print_values_node(node->left);
    printf("%d, ", node->data);
    print_values_node(node->right);
}

void delete_tree(BST_BinarySearchTree *bst)
{
    delete_tree_node(bst->root);
    bst->root = NULL;
}

static void delete_tree_node(BST_Node *node)
{
    if (node != NULL)
    {
        delete_tree_node(node->left);
        delete_tree_node(node->right);
        free(node);
    }
}

bool is_in_tree(BST_BinarySearchTree *bst, int data)
{
    return search(bst->root, data);
}

static bool search(BST_Node *node, int data)
{
    if (node != NULL)
    {
        if (node->data == data)
        {
            return true;
        }
        else if (node->data > data) 
        {
            return search(node->left, data);
        }
        else
        {
            return search(node->right, data);
        }
    }
    return false;
}