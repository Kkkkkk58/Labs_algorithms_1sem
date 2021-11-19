#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 18

struct Node {
    long value;
    struct Node *left, *right;
};

struct Node *insert(struct Node *tree, long value);
struct Node *delete(struct Node *tree, long value);
struct Node *exists(struct Node *tree, long value);
struct Node *next(struct Node *tree, long value);
struct Node *prev(struct Node *tree, long value);
struct Node *tree_min(struct Node *tree);
struct Node *parent(struct Node *tree, long value);
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
    if (tree == NULL) {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->value = value;
        new_node->left = new_node->right = NULL;
        return new_node;
    }
    else if (value < tree->value) {
        tree->left = insert(tree->left, value);
    }
    else if (value > tree->value) {
        tree->right = insert(tree->right, value);
    }
    return tree;
}


struct Node *delete(struct Node *tree, long value) {
    struct Node *p = parent(tree, value);
    if (p == NULL && tree->value != value) {
        return tree;
    }
    
    int right_c = 0, left_c = 0;
    struct Node *element;
    if (tree->value == value) {
        element = tree;
        p = tree;
    }
    else if (p->left != NULL && p->left->value == value) {
        left_c = 1;
        element = p->left;
    } 
    else {
        right_c = 1;
        element = p->right;
    }
    if (element->right == NULL && element->left == NULL) {
        if (element != p) {
            if (right_c) {
                p->right = NULL;
            }
            else {
                p->left = NULL;
            }
        }
        else {
            tree = NULL;
        }
    }
    else if (element->right == NULL && element->left != NULL) {
        if (element != p) {
            if (right_c) {
                p->right = element->left;
            }
            else {
                p->left = element->left;
            }
        }
        else {
            return tree->left;
        }
    }
    else if (element->left == NULL && element->right != NULL) {
        if (element != p) {
            if (right_c) {
                p->right = element->right;
            }
            else {
                p->left = element->right;
            }
        }
        else {
            return tree->right;
        }
    }
    else {
        struct Node *successor = next(element, value);
        if (successor == NULL) {
            successor = prev(element, value);
        }
        long tmp_value = successor->value;
        delete(element, tmp_value);
        element->value = tmp_value;
        element = NULL;
    }
    if (element != tree) {
        free(element);
    }
    return tree;
}


struct Node *exists(struct Node *tree, long value) {
    struct Node *tmp = tree;
    while (tmp != NULL && value != tmp->value) {
        if (value < tmp->value) {
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right;
        }
    }
    return tmp;
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


struct Node *prev (struct Node *tree, long value) {
    struct Node *curr = tree;
    struct Node *predecessor = NULL;
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


struct Node *tree_min(struct Node *tree) {
    struct Node *min;
    while (min->left != NULL) {
        min = min->left;
    }
    return min; 
}


struct Node *parent(struct Node *tree, long value) {
    struct Node *tmp = tree;
    struct Node *pa;
  while(tmp != NULL && tmp->value != value) {
       pa = tmp;
       if (tmp->value > value) {
         tmp = tmp->left;
       }
       else {
         tmp = tmp->right; 
       }
    }
    if (tmp == NULL) {
        return NULL;
    }
    return pa;
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
