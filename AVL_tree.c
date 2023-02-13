/*
 AVL tree implementation.
 
 Author: A. Tafliovich
 Based heavily on materials developed by F. Estrada.
 */

#include "AVL_tree.h"

/*************************************************************************
 ** Suggested helper functions
 *************************************************************************/

/* Returns max of two integers
 */
int max(int a, int b) {
    
    return a > b ? ++a: ++b;
}

/* Returns the height (number of nodes on the longest root-to-leaf path) of
 * the tree rooted at node 'node'. Returns 0 if 'node' is NULL.
 */
int height(AVL_Node* node) {
    
    if (node == NULL) return 0;
    
    int left_height = 0, right_height = 0;
    if (node->left != NULL) left_height = height(node->left);
    if (node->right != NULL) right_height = height(node->right);
    
    return max(right_height, left_height);
}

/* Updates the height of the tree rooted at node 'node' based on the heights
 * of its children. Note: this should be an O(1) operation.
 */
void update_height(AVL_Node* node) {
    
    int left_height = 0, right_height = 0;
    
    if (node->left != NULL) left_height = node->left->height;
    if (node->right != NULL) right_height = node->right->height;
    
    node->height = max(right_height, left_height);
}

/*Updates the height of two nodes in their respective order
 */
void update_heights(AVL_Node* node, AVL_Node* x) {
    
    update_height(node);
    update_height(x);
}

/* Returns the balance factor (height of left subtree - height of right
 * subtree) of node 'node'. Returns 0 of node is NULL.
 */
int balance_factor(AVL_Node* node) {
    
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

/* Returns the result of performing a right/clockwise rotation in the AVL
 * tree rooted at 'node'.
 */
AVL_Node* right_rotation(AVL_Node* node) {
    
    if (node == NULL) return NULL;
    
    AVL_Node* x = node->left;
    AVL_Node* s = x->right;
    
    x->right = node;
    node->left = s;
    
    update_heights(node, x);
    return x;
}

/* Returns the result of performing a left/counter-clockwise rotation in the AVL
 * tree rooted at 'node'.
 */
AVL_Node* left_rotation(AVL_Node* node) {
    
    if (node == NULL) return NULL;
    
    AVL_Node* x = node->right;
    AVL_Node* s = x->left;
    
    x->left = node;
    node->right = s;
    
    update_heights(node, x);
    return x;
}

// Implemented in 'rebalance'
AVL_Node* right_left_rotation(AVL_Node* node);

// Implemented in 'rebalance'
AVL_Node* left_right_rotation(AVL_Node* node);

/* Returns the successor node of 'node'.
 */
AVL_Node* successor(AVL_Node* node) {
    
    if (node == NULL || node->right == NULL) return NULL;
    AVL_Node* temp = node->right;
    
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

/* Creates and returns an AVL tree node with key 'key', value 'value', height
 * of 1, and left and right subtrees NULL.
 */
AVL_Node* create_node(int key, void* value) {
    
    AVL_Node* new_node = (AVL_Node *)malloc(sizeof(AVL_Node));
    
    if (new_node == NULL) return NULL;
    new_node->key = key;
    new_node->value = value;
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node;
}

/* Rebalances the tree rooted at node 'node'.
 */
AVL_Node* rebalance(AVL_Node* node) {
    
    int balance = balance_factor(node);
    
    if (balance > 1) {
        AVL_Node* temp = node->left;
        int temp_balance = balance_factor(temp);
        if (temp_balance >= 0) {
            return right_rotation(node);
        }
        else {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
    }
    
    else if (balance < -1) {
        AVL_Node* temp = node->right;
        int temp_balance = balance_factor(temp);
        if (temp_balance <= 0) {
            return left_rotation(node);
        } else {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }
    }
    
    return node;
}

/*************************************************************************
 ** Provided functions
 *************************************************************************/
void print_tree_inorder_(AVL_Node* node, int offset) {
    if (node == NULL) return;
    print_tree_inorder_(node->right, offset + 1);
    printf("%*s %d [%d]\n", offset, "", node->key, node->height);
    print_tree_inorder_(node->left, offset + 1);
}

void print_tree_inorder(AVL_Node* node) {
    print_tree_inorder_(node, 0);
}

void delete_tree(AVL_Node* node) {
    if (node == NULL) return;
    delete_tree(node->left);
    delete_tree(node->right);
    free(node);
}

/*************************************************************************
 ** Required functions
 ** Must run in O(log n) where n is the number of nodes in a tree rooted
 **  at 'node'.
 *************************************************************************/

AVL_Node* search(AVL_Node* node, int key) {
    
    if (node == NULL) return NULL;
    if (node->key == key) return node;
    
    if (node->key < key) {
        return search(node->right, key);
        
    } else {
        return search(node->left, key);
    }
    return node;
}

AVL_Node* insert(AVL_Node* node, int key, void* value) {
    
    if (node == NULL) return create_node(key, value);
    
    if (key < node->key) {
        node->left = insert(node->left, key, value);
        
    } else if (key > node->key) {
        node->right = insert(node->right, key, value);
        
    } else {
        node->value = value;
        return node;
    }
    
    update_height(node);
    return rebalance(node);
}

AVL_Node* delete(AVL_Node* node, int key) {
    
    if (node == NULL) return NULL;
    
    AVL_Node *temp = node;
    
    if (node->key > key) {
        node->left = delete(node->left, key);
        
    } else if (node->key < key) {
        node->right = delete(node->right, key);
        
    } else {
        
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
            
        } else if (node->left == NULL) {
            temp = node->right;
            free(node);
            return temp;
            
        } else if (node->right == NULL) {
            temp = node->left;
            free(node);
            return temp;
            
        } else {
            temp = successor(node);
            node->key = temp->key;
            node->value = temp->value;
            node->right = delete(node->right, temp->key);
        }
    }
    update_height(node);
    return rebalance(node);
}

