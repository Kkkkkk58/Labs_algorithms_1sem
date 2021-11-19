#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 18

struct Node {
    long value;
    struct Node *left, *right, *parent;
};

struct Node *insert(struct Node *tree, long value);
struct Node *delete(struct Node *tree, long value);
struct Node *exists(struct Node *tree, long value);
struct Node *next(struct Node *tree, long value);
struct Node *prev(struct Node *tree, long value);
void inorderwalk(struct Node *tree);
void free_tree(struct Node **tree);


int main() {
    FILE *fin = fopen("bstsimple.in", "r");
    FILE *fout = fopen("bstsimple.out", "w");
    struct Node *tree = NULL;
    char line[MAXLEN];
    while (fgets(line, MAXLEN - 1, fin)) {
        char *digit_ptr = strchr(line, ' ') + 1;
        long value = atol(digit_ptr);
        if (line[0] == 'i') {
            tree = insert(tree, value);
        }
        else if (line[0] == 'd') {
            tree = delete(tree, value);
        }
        else if (line[0] == 'e') {
            if (exists(tree, value)) {
                printf("true\n");
            }
            else {
                printf("false\n");
            }            
        }
        else if (line[0] == 'n') {
            struct Node *n = next(tree, value);
            if (n) {
                printf("%ld\n", n->value);
            }
            else {
                printf("none\n");
            }            
        }
        else if (line[0] == 'p') {
            
            struct Node *p = prev(tree, value);
            if (p) {
                printf("%ld\n", p->value);
            }
            else {
                printf("none\n");
            }
        }

    }
    free_tree(&tree);
    return 0;
}


struct Node *insert(struct Node *tree, long value) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (tree == NULL) {
        new_node->value = value;
        new_node->left = new_node->right = new_node->parent = NULL;
        return new_node;
    }
    else if (value < tree->value) {
        tree->left = insert(tree->left, value);
        new_node->parent = tree->left;
    }
    else if (value > tree->value) {
        tree->right = insert(tree->right, value);
        new_node->parent = tree->right;
    }
    else if (value == tree->value) {
        free(new_node);
    }
    return tree;    
}


struct Node *delete(struct Node *tree, long value) {
    struct Node *element = exists(tree, value);
    if (element == NULL) {
        return NULL;
    }
    int left_child = 0;
    int right_child = 0;
    if (element->parent != NULL) {
        if (element->parent->left == element) {
            left_child = 1;
        }
        else {
            right_child = 1;
        }
    }
    if (element->left == NULL && element->right == NULL) {
        if (element->parent != NULL) {
            if (left_child) {
                element->parent->left = NULL;
            }
            else {
                element->parent->right = NULL;
            }
        }
        free(element);
        tree = NULL;
    }
    else if (element->left == NULL && element->right != NULL) {
        if (element->parent != NULL) {
            element->right->parent = element->parent;
            if (left_child) {
                element->parent->left = element->right;
            }
            else {
                element->parent->right = element->right;
            }
        }
        else {
            element->right->parent = NULL;
            tree = element->right;
        }
        free(element);
    }
    else if (element->right == NULL && element->left != NULL) {
        if (element->parent != NULL) {
            element->left->parent = element->parent;
            if (left_child) {
                element->parent->left = element->left;
            }
            else {
                element->parent->right = element->left;
            }
        }
        else {
            element->left->parent = NULL;
            tree = element->left;
        }
        free(element);
    }
    else {
        struct Node *successor = next(element, value);
        element->value = successor->value;
        element->right = delete(element->right, successor->value);
    }
    return tree;
}


struct Node *exists(struct Node *tree, long value) {
    while (tree != NULL && value != tree->value) {
        if (value < tree->value) {
            tree = tree->left;
        }
        else {
            tree = tree->right;
        }
    }
    return tree;
}


struct Node *next(struct Node *tree, long value) {
    struct Node *curr = tree;
    struct Node *successor = NULL;
    while (curr != NULL) {
        if (curr->value > value) {
            successor = curr;
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return successor;
}


struct Node *prev(struct Node *tree, long value) {
    struct Node *curr = tree;
    struct Node *predecessor = NULL;
    //printf("GAVNO %ld SINA %ld", curr->value, curr->left);
    while (curr != NULL) {
        if (curr->value < value) {
            predecessor = curr;
            curr = curr->right;
        }
        else {
            curr = curr->left;
        }
    }
    return predecessor;
}


void inorderwalk(struct Node *tree) {
    if (tree != NULL) {
        inorderwalk(tree->left);
        printf("%ld ", tree->value);
        inorderwalk(tree->right);
    }
}


void free_tree(struct Node **tree) {
    while (*tree != NULL) {
        if ((*tree)->left != NULL) {
            free_tree(&((*tree)->left));
        }
        if ((*tree)->right != NULL) {
            free_tree(&((*tree)->right));
        }
        else {
            free(*tree);
            (*tree) = NULL;
        }
    }
}
