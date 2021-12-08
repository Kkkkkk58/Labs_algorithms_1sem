#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 60
#define MAP_SIZE 100000
#define MULT_VALUE 31
#define MAX_PARAM_SIZE 20

enum Deletion_status {
    NOT_DELETED,
    DELETED
};

struct Node {
    struct Node *prev_node, *next_node, *prev_added, *next_added;
    char key[MAX_PARAM_SIZE + 1], value[MAX_PARAM_SIZE + 1];
};
 
struct List {
    struct Node *head;
};

unsigned int hash(char *key);
void free_list(struct List **list);
struct Node *put(struct List *hash_map, char *key, char *value, struct Node *last_added);
int delete(struct List *hash_map, char *key);
char *get(struct List *hash_map, char *key);
char *prev(struct List *hash_map, char *key);
char *next(struct List *hash_map, char *key);


int main() {
    FILE *fin = fopen("linkedmap.in", "r");
    FILE *fout = fopen("linkedmap.out", "w");
    struct List **hash_map = (struct List **)malloc(MAP_SIZE * sizeof(struct List *));
    for (int i = 0; i < MAP_SIZE; ++i) {
        hash_map[i] = (struct List *)malloc(sizeof(struct List));
        hash_map[i]->head = NULL;
    }
    char input_line[MAX_LINE_SIZE];
    struct Node *last_added = NULL;
    while (fgets(input_line, MAX_LINE_SIZE - 1, fin)) {
        if (input_line[1] == 'u') {
            char *save_ptr = strpbrk(input_line, " ") + 1;
            char *key = strtok_r(save_ptr, " ", &save_ptr);
            char *value = save_ptr;
            value[strcspn(value, " \r\n")] = '\0';
            unsigned int hash_value = hash(key);
            struct Node *new_node = put(hash_map[hash_value], key, value, last_added);
            if (last_added != NULL && new_node != NULL) {
                last_added->next_added = new_node;
            }
            if (new_node != NULL) {
                last_added = new_node;
            }
        }
        else {
            char *key = strchr(input_line, ' ') + 1;
            key[strcspn(key, " \r\n")] = '\0';
            unsigned int hash_value = hash(key);
            if (input_line[0] == 'd') {
                int is_deleted = delete(hash_map[hash_value], key);
                if (is_deleted == DELETED && last_added != NULL && strcmp(last_added->key, key) == 0) {
                    last_added = last_added->prev_added;
                }
            }
            else if (input_line[0] == 'g') {
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
            else if (input_line[0] == 'n') {
                char *next_value = next(hash_map[hash_value], key);
                if (next_value == NULL) {
                    fprintf(fout, "none\n");
                }
                else {
                    fprintf(fout, "%s", next_value);
                    if (strchr(next_value, '\n') == NULL) {
                        fprintf(fout, "\n");
                    }
                }                  
            }
            else {
                char *prev_value = prev(hash_map[hash_value], key);
                if (prev_value == NULL) {
                    fprintf(fout, "none\n");
                }
                else {
                    fprintf(fout, "%s", prev_value);
                    if (strchr(prev_value, '\n') == NULL) {
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

struct Node *put(struct List *hash_map, char *key, char *value, struct Node *last_added) {
    struct Node *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next_node;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
        strncpy(curr->value, value, MAX_PARAM_SIZE);
    }
    else {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->prev_node = NULL;
        strncpy(new_node->key, key, MAX_PARAM_SIZE);
        strncpy(new_node->value, value, MAX_PARAM_SIZE);
        new_node->next_node = hash_map->head;
        new_node->prev_added = last_added;
        new_node->next_added = NULL;
        if (hash_map->head != NULL) {
            hash_map->head->prev_node = new_node;
        }
        hash_map->head = new_node;
        return new_node;
    }
    return NULL;
}


int delete(struct List *hash_map, char *key) {
    struct Node *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next_node;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
        if (curr->prev_added != NULL) {
            curr->prev_added->next_added = curr->next_added;
        }
        if (curr->next_added != NULL) {
            curr->next_added->prev_added = curr->prev_added;
        }
        if (curr->next_node != NULL) {
            curr->next_node->prev_node = curr->prev_node;
        }
        if (curr->prev_node != NULL) {
            curr->prev_node->next_node = curr->next_node;
        }
        else {
            hash_map->head = curr->next_node;
        }
        free(curr);
        curr = NULL;
        return DELETED;
    }
    return NOT_DELETED;
}


char *get(struct List *hash_map, char *key) {
    struct Node *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next_node;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
        return curr->value;
    }
    return NULL;
}


char *prev(struct List *hash_map, char *key) {
    struct Node *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next_node;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
        if (curr->prev_added != NULL) {
            return curr->prev_added->value;
        }
    }
    return NULL;
}


char *next(struct List *hash_map, char *key) {
    struct Node *curr = hash_map->head;
    while (curr != NULL && strcmp(curr->key, key) != 0) {
        curr = curr->next_node;
    }
    if (curr != NULL && strcmp(curr->key, key) == 0) {
        if (curr->next_added != NULL) {
            return curr->next_added->value;
        }
    }
    return NULL;
}


void free_list(struct List **list) {
    struct Node *current = (*list)->head;
    struct Node *next = NULL;
    while (current != NULL) {
        next = current->next_node;
        free(current);
        current = next;
    }
    free(*list);
    *list = NULL;
}