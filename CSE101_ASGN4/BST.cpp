#include "BST.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

BST::BST() {
    root = NULL;
}

void BST::insert(const char* word) {
    Node* to_insert = new Node(word);
    if (root == NULL) {
        root = to_insert;
    } else {
        insert(root, to_insert);
    }
}

Node* BST::insert(Node* start, Node* to_insert) {
    if (start == NULL) {
        return to_insert;
    }

    if (to_insert->key <= start->key) {
        start->left = insert(start->left, to_insert);
        start->left->parent = start;
    } else {
        start->right = insert(start->right, to_insert);
        start->right->parent = start;
    }

    start = update(start, to_insert);
    return start;
}

int BST::find_range(const char* str1, const char* str2) {
    CustomString s1(str1), s2(str2);
    return root->subtree - minLeaf(s1, root) - maxleaf(s2, root);
}

int BST::minLeaf(const CustomString& str1, Node* curr) {
    if (curr && curr->left == NULL && curr->right == NULL) {
        if (curr->key >= str1) {
            return 0;
        } else {
            return 1;
        }
    }

    int remove = 0;
    if (curr && curr->key >= str1 && curr->left) {
        remove = minLeaf(str1, curr->left);
    } else if (curr && curr->key < str1) {
        int toss = 0;
        if (curr->left) {
            toss = curr->left->subtree;
        }
        remove = minLeaf(str1, curr->right) + 1 + toss;
    }
    return remove;
}

int BST::maxleaf(const CustomString& str2, Node* curr) {
    if (curr && curr->left == NULL && curr->right == NULL) {
        if (curr->key <= str2) {
            return 0;
        } else {
            return 1;
        }
    }

    int remove = 0;
    if (curr && curr->key <= str2 && curr->right) {
        remove = maxleaf(str2, curr->right);
    } else if (curr && curr->key > str2) {
        int toss = 0;
        if (curr->right) {
            toss = curr->right->subtree;
        }
        remove = maxleaf(str2, curr->left) + 1 + toss;
    }
    return remove;
}

Node* BST::update(Node* curr, Node* to_insert) {
    if (curr == NULL) {
        return NULL;
    }
    int left = 0;
    int right = 0;
    int left_childs = 0;
    int right_childs = 0;

    if (curr->left) {
        left = curr->left->height + 1;
        left_childs = curr->left->subtree;
    }

    if (curr->right) {
        right = curr->right->height + 1;
        right_childs = curr->right->subtree;
    }
    curr->subtree = left_childs + right_childs + 1;
    curr->height = max(left, right);

    int diff = left - right;

    if (diff > 1) {
        if (curr->left->key < to_insert->key) {
            rLeft(curr->left);
        }
        return rRight(curr);
    } else if (diff < -1) {
        if (curr->right->key > to_insert->key) {
            rRight(curr->right);
        }
        return rLeft(curr);
    }
    return curr;
}

Node* BST::rLeft(Node* old) {
    Node* new_root = old->right;
    new_root->parent = old->parent;

    if (old->key != root->key && old->parent->left && old->parent->left->key == old->key) {
        old->parent->left = new_root;
    }
    if (old->key != root->key && old->parent->right && old->parent->right->key == old->key) {
        old->parent->right = new_root;
    }

    Node* temp = new_root->left;

    if (old->key == root->key) {
        root = new_root;
    }

    new_root->left = old;
    old->parent = new_root;

    old->right = temp;
    if (temp) {
        temp->parent = old;
    }

    int x = 0;
    int y = 0;
    int x_subtree = 0;
    int y_subtree = 0;

    if (old->left) {
        x = old->left->height + 1;
        x_subtree = old->left->subtree;
    }
    if (temp) {
        y = temp->height + 1;
        y_subtree = temp->subtree;
    }

    old->height = max(x, y);
    old->subtree = x_subtree + y_subtree + 1;
    x = 0;
    y = 0;
    x_subtree = 0;
    y_subtree = 0;

    if (new_root->left) {
        x = new_root->left->height + 1;
        x_subtree = new_root->left->subtree;
    }

    if (new_root->right) {
        y = new_root->right->height + 1;
        y_subtree = new_root->right->subtree;
    }

    new_root->height = max(x, y);
    new_root->subtree = x_subtree + y_subtree + 1;
    return new_root;
}

Node* BST::rRight(Node* old) {
    Node* new_root = old->left;
    new_root->parent = old->parent;

    if (old->key != root->key && old->parent->left && old->parent->left->key == old->key) {
        old->parent->left = new_root;
    }

    if (old->key != root->key && old->parent->right && old->parent->right->key == old->key) {
        old->parent->right = new_root;
    }

    Node* temp = new_root->right;

    if (old->key == root->key) {
        root = new_root;
    }

    new_root->right = old;
    old->parent = new_root;

    old->left = temp;
    if (temp) {
        temp->parent = old;
    }

    int x = 0;
    int y = 0;
    int x_subtree = 0;
    int y_subtree = 0;

    if (temp) {
        x = temp->height + 1;
        x_subtree = temp->subtree;
    }
    if (old->right) {
        y = old->right->height + 1;
        y_subtree = old->right->subtree;
    }

    old->height = max(x, y);
    old->subtree = x_subtree + y_subtree + 1;
    x = 0;
    y = 0;
    x_subtree = 0;
    y_subtree = 0;

    if (new_root->left) {
        x = new_root->left->height + 1;
        x_subtree = new_root->left->subtree;
    }

    if (new_root->right) {
        y = new_root->right->height + 1;
        y_subtree = new_root->right->subtree;
    }

    new_root->height = max(x, y);
    new_root->subtree = x_subtree + y_subtree + 1;
    return new_root;
}

Node* BST::find(const char* word) {
    CustomString s(word);
    return find(root, s);
}

Node* BST::find(Node* start, const CustomString& word) {
    if (start == NULL || start->key == word) {
        return start;
    }
    if (word < start->key) {
        return find(start->left, word);
    } else {
        return find(start->right, word);
    }
}

Node* BST::minNode(Node* start) {
    if (start == NULL) {
        return NULL;
    }
    if (start->left == NULL) {
        return start;
    } else {
        return minNode(start->left);
    }
}

Node* BST::maxNode(Node* start) {
    if (start == NULL) {
        return NULL;
    }
    if (start->right == NULL) {
        return start;
    } else {
        return maxNode(start->right);
    }
}

Node* BST::deleteKey(const char* word) {
    return deleteNode(find(word));
}

Node* BST::deleteNode(Node* to_delete) {
    if (to_delete == NULL) {
        return NULL;
    }

    bool isRoot = (to_delete == root) ? true : false;
    bool isLeftChild = false;
    if (!isRoot) {
        isLeftChild = (to_delete->parent->left == to_delete) ? true : false;
    }
    bool isDeleted = false;

    if (to_delete->left == NULL) {
        if (isRoot) {
            root = to_delete->right;
            if (root != NULL) {
                root->parent = NULL;
            }
        } else {
            if (isLeftChild) {
                to_delete->parent->left = to_delete->right;
            } else {
                to_delete->parent->right = to_delete->right;
            }
            if (to_delete->right != NULL) {
                to_delete->right->parent = to_delete->parent;
            }
            isDeleted = true;
        }
    }

    if (!isDeleted && to_delete->right == NULL) {
        if (isRoot) {
            root = to_delete->left;
            if (root != NULL) {
                root->parent = NULL;
            }
        } else {
            if (isLeftChild) {
                to_delete->parent->left = to_delete->left;
            } else {
                to_delete->parent->right = to_delete->left;
            }
            if (to_delete->left != NULL) {
                to_delete->left->parent = to_delete->parent;
            }
        }
        isDeleted = true;
    }

    if (isDeleted) {
        to_delete->left = to_delete->right = NULL;
        return to_delete;
    }

    Node* succ = minNode(to_delete->right);
    to_delete->key = succ->key;
    return deleteNode(succ);
}

void BST::deleteBST() {
    deleteBST(root);
}

void BST::deleteBST(Node* start) {
    if (start == NULL) {
        return;
    }
    deleteBST(start->left);
    deleteBST(start->right);
    delete start;
}

void BST::printInOrder(Node* start, CustomString& result) {
    if (start == NULL) {
        return;
    }
    printInOrder(start->left, result);
    if (result.str[0] != '\0') {
        result.append(" ");
    }
    result.append(start->key.str);
    printInOrder(start->right, result);
}

CustomString BST::printInOrder() {
    CustomString result("");
    printInOrder(root, result);
    return result;
}

void BST::printPreOrder(Node* start, CustomString& result) {
    if (start == NULL) {
        return;
    }
    if (result.str[0] != '\0') {
        result.append(" ");
    }
    result.append(start->key.str);
    printPreOrder(start->left, result);
    printPreOrder(start->right, result);
}

CustomString BST::printPreOrder() {
    CustomString result("");
    printPreOrder(root, result);
    return result;
}

void BST::printPostOrder(Node* start, CustomString& result) {
    if (start == NULL) {
        return;
    }
    printPostOrder(start->left, result);
    printPostOrder(start->right, result);
    if (result.str[0] != '\0') {
        result.append(" ");
    }
    result.append(start->key.str);
}

CustomString BST::printPostOrder() {
    CustomString result("");
    printPostOrder(root, result);
    return result;
}
