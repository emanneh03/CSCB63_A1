/*
 AVL tree implementation.
 
 Author: A. Tafliovich
 Based heavily on materials developed by F. Estrada.
 */

#include "AVL_tree.h"

/*************************************************************************
 ** Suggested helper functions
 *************************************************************************/

//int max(int a, int b) {
//
//    return (a > b)? a : b;
//
//}


int height(AVL_Node* node) {
    /* Returns the height (number of nodes on the longest root-to-leaf path) of
     * the tree rooted at node 'node'. Returns 0 if 'node' is NULL.
     */
    
    if (node == NULL) return 0;
    
    int left_height = 0, right_height = 0;
    if (node->left != NULL) left_height = height(node->left);
    if (node->right != NULL) right_height = height(node->right);
    
    return right_height > left_height ? ++right_height: ++left_height;
}


void update_height(AVL_Node* node) {
    /* Updates the height of the tree rooted at node 'node' based on the heights
     * of its children. Note: this should be an O(1) operation.
     */

    int left_height = 0, right_height = 0;

    if (node->left != NULL) left_height = node->left->height;
    if (node->right != NULL) right_height = node->right->height;

    node->height = right_height > left_height ? ++right_height: ++left_height;
}


int balance_factor(AVL_Node* node) {
    /* Returns the balance factor (height of left subtree - height of right
     * subtree) of node 'node'. Returns 0 of node is NULL.
     */
    
    if (node == NULL) return 0;
    
    return height(node->left) - height(node->right);
}


AVL_Node* right_rotation(AVL_Node* node) {
    /* Returns the result of performing a right/clockwise rotation in the AVL
     * tree rooted at 'node'.
     */
    
    if (node == NULL) return NULL;
    
    AVL_Node* x = node->left;
    AVL_Node* s = x->right;
    
    x->right = node;
    node->left = s;
    
    update_height(node);
    update_height(x);
    
    return x;
}


AVL_Node* left_rotation(AVL_Node* node) {
    /* Returns the result of performing a left/counter-clockwise rotation in the AVL
     * tree rooted at 'node'.
     */
    
    if (node == NULL) return NULL;
    
    AVL_Node* x = node->right;
    AVL_Node* s = x->left;
    
    x->left = node;
    node->right = s;
    
    update_height(node);
    update_height(x);
    
    return x;
}

AVL_Node* right_left_rotation(AVL_Node* node);
//AVL_Node* right_left_rotation(AVL_Node* node) {
    
    /* Returns the result of performing a right/clockwise then left/counter-clockwise rotation in the AVL
     * tree rooted at 'node'.
     */
    
//    if (node == NULL) return NULL;
//
//    node->right = right_rotation(node->right);
//    node = left_rotation(node);
//    return node;
    
//}

AVL_Node* left_right_rotation(AVL_Node* node);
//AVL_Node* left_right_rotation(AVL_Node* node) {
    
    /* Returns the result of performing a left/counter-clockwise then right/clockwise rotation in the AVL
     * tree rooted at 'node'.
     */
    
//    if (node == NULL) return NULL;
//
//    node->left = left_rotation(node->left);
//    node = right_rotation(node);
//    return node;
    
//}


AVL_Node* successor(AVL_Node* node) {
    /* Returns the successor node of 'node'.
     */
    
    if (node == NULL || node->right == NULL) return NULL;
    AVL_Node* temp = node->right;
    
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}


AVL_Node* create_node(int key, void* value) {
    /* Creates and returns an AVL tree node with key 'key', value 'value', height
     * of 1, and left and right subtrees NULL.
     */
    
    AVL_Node* new_node = (AVL_Node *)malloc(sizeof(AVL_Node));
    
    if (new_node == NULL) return NULL;
    new_node->key = key;
    new_node->value = value;
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node;
}

AVL_Node* rebalance(AVL_Node* node) {
    /* Rebalances the tree rooted at node 'node'.
     */
    
//    int balance = balance_factor(node);
//
//        // If this node becomes unbalanced, then
//        // there are 4 cases
//
//        // Left Left Case
//        if (balance > 1 && node->key < node->left->key)
//            return right_rotation(node);
//
//        // Right Right Case
//        if (balance < -1 && node->key > node->right->key)
//            return left_rotation(node);
//
//        // Left Right Case
//        if (balance > 1 && node->key > node->left->key)
//        {
//            node->left =  left_rotation(node->left);
//            return right_rotation(node);
//        }
//
//        // Right Left Case
//        if (balance < -1 && node->key < node->right->key)
//        {
//            node->right = right_rotation(node->right);
//            return left_rotation(node);
//        }
//
//        /* return the (unchanged) node pointer */
//        return node;
//
//
//    int balance = balance_factor(node);
//
//    if (balance > 1) {
//
//        AVL_Node* temp = node->left;
//
//        if (balance >= 0) {
//
//            return right_rotation(node);
//
//        } else {
//
//            node->left = left_rotation(node->left);
//            return right_rotation(node);
//
//        }
//
//    } else if (balance < -1) {
//
//        AVL_Node* temp = node->right;
//
//        if (balance <= 0) {
//
//            return left_rotation(node);
//
//        } else {
//
//            node->right = right_rotation(node->right);
//            return left_rotation(node);
//
//        }
//    }
//
//    return node;
    
    if (height(node->left) - height(node->right) > 1) {
        AVL_Node* temp = node->left;
        if (height(temp->left) >= height(temp->right)) {
            return right_rotation(node);
        }
        else {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
    }
    
    else if (height(node->right) - height(node->left) > 1) {
        AVL_Node* temp = node->right;
        if (height(temp->left) <= height(temp->right)) {
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
            return temp;
            
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
            update_height(node);
            
            node->right = delete(node->right, key);
            
        }
        
    }
    
    node = rebalance(node);
    return node;
    
}
