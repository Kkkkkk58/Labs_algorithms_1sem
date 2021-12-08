#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 60
#define MAP_SIZE 100000
#define MULT_VALUE 31
#define MAX_PARAM_SIZE 21
 
struct Node {
    struct Node *left, *right, *parent;
    char value[MAX_PARAM_SIZE];
};
  
struct Tree {
    struct Node *root;
    char key[MAX_PARAM_SIZE];
    struct Tree *next_root, *prev_root;
    int size;
};
 
struct Head {
    struct Tree *head;
};
 
unsigned int hash(char *key);
void put(struct Head *hash_map, char *key, char *value);
void delete(struct Head *hash_map, char *key, char *value);
void deleteall(struct Head *hash_map, char *key);
void get(struct Head *hash_map, char *key, FILE *fout);
void free_map(struct Head **hash_map);
struct Node *tree_insert(struct Node *tree, struct Node *new_node);
struct Node *tree_delete(struct Node *tree, char *value);
struct Node *tree_exists(struct Node *tree, char *value);
struct Node *tree_next(struct Node *tree, char *value);
void tree_inorderwalk(struct Node *tree, FILE *fout);
void free_tree(struct Node **tree);
 

int main() {
    FILE *fin = fopen("multimap.in", "r");
    FILE *fout = fopen("multimap.out", "w");
    struct Head **hash_map = (struct Head **)malloc(MAP_SIZE * sizeof(struct Head *));
    for (int i = 0; i < MAP_SIZE; ++i) {
        hash_map[i] = (struct Head *)malloc(sizeof(struct Head));
        hash_map[i]->head = NULL;
    }
    int i = 0;
    char input_line[MAX_LINE_SIZE];
    while (fgets(input_line, MAX_LINE_SIZE - 1, fin)) {
        if (input_line[0] == 'p' || input_line[0] == 'd' && input_line[6] == ' ') {
            char *save_ptr = strpbrk(input_line, " ") + 1;
            char *key = strtok_r(save_ptr, " ", &save_ptr);
            char *value = save_ptr;
            value[strcspn(value, " \r\n")] = '\0';
            unsigned int hash_value = hash(key);
            if (input_line[0] == 'p') {
                put(hash_map[hash_value], key, value);
            }
            else {
                delete(hash_map[hash_value], key, value);
            }
        }
        else {
            char *key = strchr(input_line, ' ') + 1;
            key[strcspn(key, " \r\n")] = '\0';
            unsigned int hash_value = hash(key);
            if (input_line[0] == 'd') {
                deleteall(hash_map[hash_value], key);
            }
            else {
                get(hash_map[hash_value], key, fout);
            }
        }
    }
    for (int i = 0; i < MAP_SIZE; ++i) {
        free_map(&hash_map[i]);
    }
    free(hash_map);
    fclose(fin);
    fclose(fout);
    return 0;
}
 
 
unsigned int hash(char *key) {
    unsigned int hash_value = 0;
    unsigned int multiplier = 1;
    for (int i = 0; i < strlen(key); ++i) {
        if (key[i] == '\n' || key[i] == '\r' || key[i] == ' ') {
            break;
        }
        hash_value += (key[i] - 'A' + 1) * multiplier;
        multiplier *= MULT_VALUE;
    }
    return hash_value % MAP_SIZE;
}
 
 
void put(struct Head *hash_map, char *key, char *value) {
    struct Tree *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next_root;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
        if (tree_exists(curr->root, value) == NULL) {
            struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
            strncpy(new_node->value, value, MAX_PARAM_SIZE);
            new_node->left = new_node->right = new_node->parent = NULL;
            if (curr->size == 0) {
                curr->root = new_node;
            }
            else {
                curr->root = tree_insert(curr->root, new_node);
            }
            curr->size += 1;
        }
    }
    else {
        struct Tree *new_tree = (struct Tree *)malloc(sizeof(struct Tree));
        new_tree->next_root = hash_map->head;
        if (hash_map->head != NULL) {
            hash_map->head->prev_root = new_tree;
        }
        new_tree->prev_root = NULL;
        strncpy(new_tree->key, key, MAX_PARAM_SIZE);
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        strncpy(new_node->value, value, MAX_PARAM_SIZE);
        new_node->left = new_node->right = new_node->parent = NULL;
        new_tree->root = new_node;
        new_tree->size = 1;
        hash_map->head = new_tree;
    }
}
 
 
void delete(struct Head *hash_map, char *key, char *value) {
    struct Tree *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next_root;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
        if (tree_exists(curr->root, value) != NULL) {
            curr->root = tree_delete(curr->root, value);
            curr->size -= 1;
        }
    }
}
 
 
void deleteall(struct Head *hash_map, char *key) {
    struct Tree *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next_root;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
        if (curr->next_root != NULL) {
            curr->next_root->prev_root = curr->prev_root;
        }
        if (curr->prev_root != NULL) {
            curr->prev_root->next_root = curr->next_root;
        }
        free_tree(&(curr->root));
        curr->size = 0;
    }
}
 
 
void get(struct Head *hash_map, char *key, FILE *fout) {
    struct Tree *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next_root;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
        if (curr->size > 0) {
            fprintf(fout, "%d ", curr->size);
            tree_inorderwalk(curr->root, fout);
            fprintf(fout, "\n");
        }
        else {
            fprintf(fout, "0\n");
        }
    }
    else {
        fprintf(fout, "0\n");
    }
}
 
 
struct Node *tree_insert(struct Node *tree, struct Node *new_node) {
    if (tree == NULL) {
        return new_node;
    }
    else if (strcmp(new_node->value, tree->value) < 0) {
        new_node->parent = tree;
        tree->left = tree_insert(tree->left, new_node);
    }
    else if (strcmp(new_node->value, tree->value) > 0) {
        new_node->parent = tree;
        tree->right = tree_insert(tree->right, new_node);
    }
    else {
        free(new_node);
        new_node = NULL;
    }
    return tree;    
}
 
 
struct Node *tree_delete(struct Node *tree, char *value) {
    struct Node *element = tree_exists(tree, value);
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
        element = NULL;
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
        element = NULL;
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
        element = NULL;
    }
    else {
        struct Node *successor = tree_next(element, value);
        strncpy(element->value, successor->value, MAX_PARAM_SIZE);
        tree_delete(element->right, successor->value);
    }
    return tree;
}
  
  
struct Node *tree_exists(struct Node *tree, char *value) {
    while (tree != NULL && strcmp(value, tree->value) != 0) {
        if (strcmp(value, tree->value) < 0) {
            tree = tree->left;
        }
        else {
            tree = tree->right;
        }
    }
    return tree;
}
 

struct Node *tree_next(struct Node *tree, char *value) {
    struct Node *successor = NULL;
    while (tree != NULL) {
        if (strcmp(tree->value, value) > 0) {
            successor = tree;
            tree = tree->left;
        }
        else {
            tree = tree->right;
        }
    }
    return successor;
}
 
 
void tree_inorderwalk(struct Node *tree, FILE *fout) {
    if (tree != NULL) {
        tree_inorderwalk(tree->left, fout);
        fprintf(fout, "%s ", tree->value);
        tree_inorderwalk(tree->right, fout);
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
 
 
void free_map(struct Head **hash_map) {
    struct Tree *current = (*hash_map)->head;
    struct Tree *next = NULL;
    while (current != NULL) {
        next = current->next_root;
        free_tree(&(current->root));
        free(current);
        current = next;
    }
    free(*hash_map);
    *hash_map = NULL;
}