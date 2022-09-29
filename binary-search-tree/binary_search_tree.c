#include "binary_search_tree.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

static BST_Node *BST_insert_node(BST_Node *parent, BST_Node *node, int data);
static BST_Node *BST_make_new_node(void);
static int BST_get_node_count_root(BST_Node *node);
static void BST_print_values_node(BST_Node *node);
static void BST_delete_tree_node(BST_Node *node);
static bool BST_search(BST_Node *node, int data);
static int BST_get_height_node(BST_Node *node);
static bool BST_is_binary_search_tree_node(BST_Node *node);
static int BST_get_min_node(BST_Node *node);
static int BST_get_max_node(BST_Node *node);
static void BST_delete_value_node(BST_Node *node, int value);
static void BST_swap_node_value(BST_Node *node1, BST_Node *node2);
static BST_Node *BST_predecessor_node(BST_Node *node);
static void BST_delete_tree_node(BST_Node *node);
static int BST_get_succesor_value(BST_Node *node, int value);

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

void BST_print_values(BST_BinarySearchTree *bst)
{
    BST_print_values_node(bst->root);
}

static void BST_print_values_node(BST_Node *node)
{
    if (node == NULL) return;
    BST_print_values_node(node->left);
    printf("%d, ", node->data);
    BST_print_values_node(node->right);
}

void BST_delete_tree(BST_BinarySearchTree *bst)
{
    BST_delete_tree_node(bst->root);
    bst->root = NULL;
}

static void BST_delete_tree_node(BST_Node *node)
{
    if (node != NULL)
    {
        BST_delete_tree_node(node->left);
        BST_delete_tree_node(node->right);
        free(node);
    }
}

bool BST_is_in_tree(BST_BinarySearchTree *bst, int data)
{
    return BST_search(bst->root, data);
}

static bool BST_search(BST_Node *node, int data)
{
    if (node != NULL)
    {
        if (node->data == data)
        {
            return true;
        }
        else if (node->data > data) 
        {
            return BST_search(node->left, data);
        }
        else
        {
            return BST_search(node->right, data);
        }
    }
    return false;
}

int BST_get_height(BST_BinarySearchTree *bst)
{
    return BST_get_height_node(bst->root);
}

static int BST_get_height_node(BST_Node *node)
{
    if (node != NULL)
    {
        return 1 + max(BST_get_height_node(node->left), BST_get_height_node(node->right));
    }
    return 0;
}

int BST_get_min(BST_BinarySearchTree *bst)
{
    return BST_get_min_node(bst->root);
}

static int BST_get_min_node(BST_Node *node)
{
    if (node == NULL)
    {
        printf("Your BST is empty");
        assert(0);
    }
    while (node->left != NULL)
        node = node->left;
    return node->data;
}

int BST_get_max(BST_BinarySearchTree *bst)
{
    return BST_get_max_node(bst->root);
}

static int BST_get_max_node(BST_Node *node)
{
    if (node == NULL)
    {
        printf("Your BST is empty");
        assert(0);
    }
    while (node->right != NULL)
        node = node->right;
    return node->data;
}

bool BST_is_binary_search_tree(BST_BinarySearchTree *bst)
{
    if (bst->root == NULL)
    {
        printf("The BST is empty");
        assert(0);
    }
    return BST_is_binary_search_tree_node(bst->root);
}

static bool BST_is_binary_search_tree_node(BST_Node *node)
{
    if (node->left != NULL && node->right != NULL)
    {
        return (node->left->data < node->data && node->right->data >= node->data) &&
            BST_is_binary_search_tree_node(node->left) && BST_is_binary_search_tree_node(node->right);
    }
    else if (node->left != NULL)
    {
        return (node->left->data < node->data) && BST_is_binary_search_tree_node(node->left);
    }
    else if (node->right != NULL)
    {
        return (node->right->data >= node->data) && BST_is_binary_search_tree_node(node->left);
    }
    else
    {
        return true;
    }
}

void BST_delete_value(BST_BinarySearchTree *bst, int value)
{
    if (bst->root == NULL)
    {
        printf("The BST is empty");
        assert(0);
    }
    BST_delete_value_node(bst->root, value);
}

static void BST_swap_node_value(BST_Node *node1, BST_Node *node2)
{
    int temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}

static BST_Node *BST_predecessor_node(BST_Node *node)
{
    // If node->left then walk to the left and right till fall off the tree
    if (node->left)
    {
        BST_Node *walk_node = node->left;
        while (walk_node->right != NULL)
            walk_node = walk_node->right;
        return walk_node;
    }
    // Walk up the tree until the child of the parent is the right side
    else
    {
        BST_Node *parent_node = node->parent;
        BST_Node *current_node = node;
        while (!(parent_node->right && parent_node->right == current_node))
        {
            parent_node = parent_node->parent;
            current_node = parent_node;
        }
        return parent_node;
    }
}

static void BST_delete_value_node(BST_Node *node, int value)
{
    // Case if the node is null or not exist
    if (node == NULL)
    {
        return;
    }
    else if (node->data == value)
    {
        // First check if its a leaf or not: simple case just simply delete it
        if (node->left == NULL && node->right == NULL)
        {
            // Make the pointer from parent NULL
            if (node->parent->left == node)
                node->parent->left = NULL;
            else
                node->parent->right = NULL;
            free(node);
        }
        else
        {
            BST_Node *predecessor = BST_predecessor_node(node);
            BST_swap_node_value(predecessor, node);
            BST_delete_value_node(predecessor, value);
        }
    }
    else if (value >= node->data)
    {
        BST_delete_value_node(node->right, value);
    }
    else
    {
        BST_delete_value_node(node->left, value);
    }
}

int BST_get_successor(BST_BinarySearchTree *bst, int value)
{
    return BST_get_succesor_value(bst->root, value);
}

static int BST_get_succesor_value(BST_Node *node, int value)
{
    int succesor = -1;
    while (node != NULL)
    {
        if (value < node->data)
        {
            succesor = node->data;
            node = node->left;
        }
        else if (value >= node->data)
        {
            node = node->right;
        }
    }
    return succesor;
}