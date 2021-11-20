#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 20

struct Node {
    long value;
    struct Node *left, *right, *parent;
};

struct Node *insert(struct Node *tree, struct Node *new_node);
struct Node *delete(struct Node *tree, long value);
struct Node *exists(struct Node *tree, long value);
struct Node *next(struct Node *tree, long value);
struct Node *prev(struct Node *tree, long value);
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
            struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
            new_node->value = value;
            new_node->left = new_node->right = new_node->parent = NULL;
            tree = insert(tree, new_node);
        }
        else if (line[0] == 'd') {
            tree = delete(tree, value);
        }
        else if (line[0] == 'e') {
            if (exists(tree, value)) {
                fprintf(fout, "true\n");
            }
            else {
                fprintf(fout, "false\n");
            }            
        }
        else if (line[0] == 'n') {
            struct Node *successor = next(tree, value);
            if (successor != NULL) {
                fprintf(fout, "%ld\n", successor->value);
            }
            else {
                fprintf(fout, "none\n");
            }            
        }
        else if (line[0] == 'p') {
            struct Node *predecessor = prev(tree, value);
            if (predecessor != NULL) {
                fprintf(fout, "%ld\n", predecessor->value);
            }
            else {
                fprintf(fout, "none\n");
            }
        }
    }
    free_tree(&tree);
    return 0;
}


struct Node *insert(struct Node *tree, struct Node *new_node) {
    if (tree == NULL) {
        return new_node;
    }
    else if (new_node->value < tree->value) {
        new_node->parent = tree;
        tree->left = insert(tree->left, new_node);
    }
    else if (new_node->value > tree->value) {
        new_node->parent = tree;
        tree->right = insert(tree->right, new_node);
    }
    else if (new_node->value == tree->value) {
        free(new_node);
    }
    return tree;    
}


struct Node *delete(struct Node *tree, long value) {
    struct Node *element = exists(tree, value);
    if (element == NULL) {
        return tree;
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
        else {
            tree = NULL;
        }
        free(element);
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
        delete(element->right, successor->value);
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
    struct Node *successor = NULL;
    while (tree != NULL) {
        if (tree->value > value) {
            successor = tree;
            tree = tree->left;
        }
        else {
            tree = tree->right;
        }
    }
    return successor;
}


struct Node *prev(struct Node *tree, long value) {
    struct Node *predecessor = NULL;
    while (tree != NULL) {
        if (tree->value < value) {
            predecessor = tree;
            tree = tree->right;
        }
        else {
            tree = tree->left;
        }
    }
    return predecessor;
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

