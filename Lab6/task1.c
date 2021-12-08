#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define GOLDEN_RATIO_DECIMAL 0.618033f
#define MAP_SIZE 999983
#define MAXLINE 21
 
 
struct Node {
    struct Node *prev, *next;
    int key;
};
 
struct List {
    struct Node *head;
};
 
int hash(int key);
void free_list(struct List **list);
void insert(struct List *hash_map, int value);
void delete(struct List *hash_map, int value);
int exists(struct List *hash_map, int value);
 
 
int main() {
    FILE *fin = fopen("set.in", "r");
    FILE *fout = fopen("set.out", "w");
    struct List **hash_map = (struct List **)malloc(MAP_SIZE * sizeof(struct List *));
    for (int i = 0; i < MAP_SIZE; ++i) {
        hash_map[i] = (struct List *)malloc(sizeof(struct List));
        hash_map[i]->head = NULL;
    }
    char input_line[MAXLINE];
    while (fgets(input_line, MAXLINE - 1, fin)) {
        int value = atoi(strchr(input_line, ' ') + 1);
        int hash_value = hash(value);
        if (input_line[0] == 'i') {
            insert(hash_map[hash_value], value);
        }
        else if (input_line[0] == 'd') {
            delete(hash_map[hash_value], value);
        }
        else if (exists(hash_map[hash_value], value)) {
            fprintf(fout, "true\n");
        }
        else {
            fprintf(fout, "false\n");
        }
    }
    for (int i = 0; i < MAP_SIZE; ++i) {
        free_list(&hash_map[i]);
    }
    free(hash_map);
    fclose(fin);
    fclose(fout);
}
 
 
int hash(int key) {
    return abs((int)(MAP_SIZE * (remainder(key * GOLDEN_RATIO_DECIMAL, 1))));
}
 
 
void insert(struct List *hash_map, int value) {
    if (exists(hash_map, value) == 0) {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->prev = NULL;
        new_node->key = value;
        new_node->next = hash_map->head;
        if (hash_map->head != NULL) {
            hash_map->head->prev = new_node;
        }
        hash_map->head = new_node;
    }
}
 
 
void delete(struct List *hash_map, int value) {
    struct Node *curr = hash_map->head;
    while (curr != NULL && curr->key != value) {
        curr = curr->next;
    }
    if (curr != NULL && curr->key == value) {
        if (curr->next != NULL) {
            curr->next->prev = curr->prev;
        }
        if (curr->prev != NULL) {
            curr->prev->next = curr->next;
        }
        else {
            hash_map->head = curr->next;
        }
        free(curr);
        curr = NULL;
    }
}
 
 
int exists(struct List *hash_map, int value) {
    struct Node *curr = hash_map->head;
    while (curr != NULL && curr->key != value) {
        curr = curr->next;
    }
    if (curr != NULL && curr->key == value) {
        return 1;
    }
    else {
        return 0;
    }
}
 
 
void free_list(struct List **list) {
    struct Node *current = (*list)->head;
    struct Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(*list);
    *list = NULL;
}