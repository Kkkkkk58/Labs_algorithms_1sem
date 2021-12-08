#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 60
#define MAP_SIZE 100000
#define MULT_VALUE 31
#define MAX_PARAM_SIZE 20

struct Node {
    struct Node *prev, *next;
    char key[MAX_PARAM_SIZE + 1], value[MAX_PARAM_SIZE + 1];
};
 
struct List {
    struct Node *head;
};

unsigned int hash(char *key);
void free_list(struct List **list);
void put(struct List *hash_map, char *key, char *value);
void delete(struct List *hash_map, char *key);
char *get(struct List *hash_map, char *key);


int main() {
    FILE *fin = fopen("map.in", "r");
    FILE *fout = fopen("map.out", "w");
    struct List **hash_map = (struct List **)malloc(MAP_SIZE * sizeof(struct List *));
    for (int i = 0; i < MAP_SIZE; ++i) {
        hash_map[i] = (struct List *)malloc(sizeof(struct List));
        hash_map[i]->head = NULL;
    }
    char input_line[MAX_LINE_SIZE];
    while (fgets(input_line, MAX_LINE_SIZE - 1, fin)) {
        if (input_line[0] == 'p') {
            char *save_ptr = strpbrk(input_line, " ") + 1;
            char *key = strtok_r(save_ptr, " ", &save_ptr);
            char *value = save_ptr;
            value[strcspn(value, " \r\n")] = '\0';
            unsigned int hash_value = hash(key);
            put(hash_map[hash_value], key, value);
        }
        else {
            char *key = strchr(input_line, ' ') + 1;
            key[strcspn(key, " \r\n")] = '\0';
            unsigned int hash_value = hash(key);
            if (input_line[0] == 'd') {
                delete(hash_map[hash_value], key);
            }
            else {
                char *value = get(hash_map[hash_value], key);
                if (value == NULL) {
                    fprintf(fout, "none\n");
                }
                else {
                    fprintf(fout, "%s", value);
                    if (strchr(value, '\n') == NULL) {
                        fprintf(fout, "\n");
                    }
                }
            }
        }
    }
    for (int i = 0; i < MAP_SIZE; ++i) {
        free_list(&hash_map[i]);
    }
    free(hash_map);
    fclose(fin);
    fclose(fout);
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

void put(struct List *hash_map, char *key, char *value) {
    struct Node *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
        strncpy(curr->value, value, MAX_PARAM_SIZE);
    }
    else {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->prev = NULL;
        strncpy(new_node->key, key, MAX_PARAM_SIZE);
        strncpy(new_node->value, value, MAX_PARAM_SIZE);
        new_node->next = hash_map->head;
        if (hash_map->head != NULL) {
            hash_map->head->prev = new_node;
        }
        hash_map->head = new_node;
    }
}


void delete(struct List *hash_map, char *key) {
    struct Node *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
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


char *get(struct List *hash_map, char *key) {
    struct Node *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
        return curr->value;
    }
    return NULL;
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