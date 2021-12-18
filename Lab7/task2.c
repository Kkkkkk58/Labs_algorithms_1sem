#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(x,y) (x > y ? x : y)

struct Node {
    long value;
    struct Node *left, *right;
};

static int **tree_arr;
void get_height(int *node);
void postorder_balance_check(int *node);
struct Node *little_left_rotation(struct Node *tree);
struct Node *big_left_rotation(struct Node *tree);
struct Node *insert(struct Node *tree, struct Node *new_node);
void bfs_based_output(int n, struct Node *tree, FILE *fout);
void free_tree(struct Node **tree);


int main() {
    FILE *fin = fopen("rotation.in", "r");
    FILE *fout = fopen("rotation.out", "w");
    int n;
    fscanf(fin, "%d", &n);
    fprintf(fout, "%d\n", n);

    tree_arr = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        tree_arr[i] = (int *)malloc(4 * sizeof(int));
        tree_arr[i][2] = 1;
        tree_arr[i][3] = 0;
    }

    struct Node *tree = NULL;
    for (int i = 0; i < n; ++i) {
        int value;
        fscanf(fin, "%d", &value);
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->value = value;
        new_node->right = new_node->left = NULL;
        tree = insert(tree, new_node);
        fscanf(fin, "%d %d", &(tree_arr[i][0]), &(tree_arr[i][1]));
    }

    postorder_balance_check(tree_arr[tree_arr[0][1] - 1]);
    if (tree_arr[tree_arr[0][1] - 1][3] == -1) {
        tree = big_left_rotation(tree);
    }
    else {
        tree = little_left_rotation(tree);
    }
    bfs_based_output(n, tree, fout);
    
    for (int i = 0; i < n; ++i) {
        free(tree_arr[i]);
    }
    free_tree(&tree);
    fclose(fin);
    fclose(fout);
    return 0;
}


void get_height(int *node) {
    int r_height = 0;
    int l_height = 0;

    if (node[0] != 0) {
        l_height = tree_arr[node[0] - 1][2];
    }
    if (node[1] != 0) {
        r_height = tree_arr[node[1] - 1][2];
    }

    node[2] = MAX(l_height, r_height) + 1;
    node[3] = r_height - l_height;
}


void postorder_balance_check(int *node) {
    if (node[0] != 0) {
        postorder_balance_check(tree_arr[node[0] - 1]);
    }
    if (node[1] != 0) {
        postorder_balance_check(tree_arr[node[1] - 1]);
    }
    if (node[0] != node[1]) {
        get_height(node);
    }
}


struct Node *insert(struct Node *tree, struct Node *new_node) {
    if (tree == NULL) {
        return new_node;
    }
    else if (new_node->value < tree->value) {
        tree->left = insert(tree->left, new_node);
    }
    else if (new_node->value > tree->value) {
        tree->right = insert(tree->right, new_node);
    }
    else if (new_node->value == tree->value) {
        free(new_node);
    }
    return tree;    
}


struct Node *big_left_rotation(struct Node *tree) {
    struct Node *root = tree;
    struct Node *right_elem = tree->right;
    struct Node *imbalanced_chain = right_elem->left;
    struct Node *subchain_right = imbalanced_chain->right;
    struct Node *subchain_left = imbalanced_chain->left;
    root->right = subchain_left;
    right_elem->left = subchain_right;
    imbalanced_chain->right = right_elem;
    imbalanced_chain->left = root;
    tree = imbalanced_chain;
    return tree;
}


struct Node *little_left_rotation(struct Node *tree) {
    struct Node *root = tree;
    struct Node *right_elem = tree->right;
    struct Node *elem_left_chain = right_elem->left;
    right_elem->left = root;
    root->right = elem_left_chain;
    tree = right_elem;
    return tree;
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
            *tree = NULL;
        }
    }
}


void bfs_based_output(int n, struct Node *tree, FILE *fout) {
    struct Node **nodes_list = (struct Node **)malloc(n * sizeof(struct Node *));
    for (int i =0; i < n; ++i) {
        nodes_list[i] = NULL;
    }
    int head_pos = 0, tail_pos = 1, size = 1;
    struct Node *root = tree;
    nodes_list[0] = root;
    while (size != 0) {
        struct Node *curr = nodes_list[head_pos];
        ++head_pos;
        --size;
        int left = 0, right = 0;
        if (curr->left != NULL) {
            nodes_list[tail_pos] = curr->left;
            ++tail_pos;
            ++size;
            left = tail_pos;
        }
        if (curr->right != NULL) {
            nodes_list[tail_pos] = curr->right;
            ++tail_pos;
            ++size;
            right = tail_pos;
        }
        fprintf(fout, "%d %d %d\n", curr->value, left, right);
    }  
    free(nodes_list);
}