#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(x,y) (x > y ? x : y)

struct Node {
    int value, height, balance;
    struct Node *left, *right;
};

void get_height(struct Node **tree);
void postorder_balance_check(struct Node **tree);
struct Node *little_left_rotation(struct Node *tree);
struct Node *little_right_rotation(struct Node *tree);
struct Node *insert(struct Node *tree, struct Node *new_node);
struct Node *avl_insert(struct Node *tree, struct Node *new_node);
void bfs_based_output(int n, struct Node *tree, FILE *fout);
void free_tree(struct Node **tree);


int main() {
    FILE *fin = fopen("addition.in", "r");
    FILE *fout = fopen("addition.out", "w");
    int n;
    fscanf(fin, "%d", &n);
    fprintf(fout, "%d\n", n + 1);

    struct Node *tree = NULL;
    for (int i = 0; i < n; ++i) {        
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        fscanf(fin, "%d", &(new_node->value));
        new_node->right = new_node->left = NULL;
        new_node->height = 1;
        new_node->balance = 0;
        tree = insert(tree, new_node);
        int index_left, index_right;
        fscanf(fin, "%d %d", &index_left, &index_right);
    }

    if (n > 0) {
        postorder_balance_check(&tree);
    }

    struct Node *node_to_add = (struct Node *)malloc(sizeof(struct Node));
    fscanf(fin, "%d", &(node_to_add->value));
    node_to_add->left = node_to_add->right = NULL;
    node_to_add->balance = 0;
    node_to_add->height = 1;

    tree = avl_insert(tree, node_to_add);
    bfs_based_output(n + 1, tree, fout);

    free_tree(&tree);
    fclose(fin);
    fclose(fout);
    return 0;
}


void get_height(struct Node **tree) {
    int r_height = 0;
    int l_height = 0;

    if ((*tree)->left != NULL) {
        l_height = (*tree)->left->height;
    }
    if ((*tree)->right != NULL) {
        r_height = (*tree)->right->height;
    }

    (*tree)->height = MAX(l_height, r_height) + 1;
    (*tree)->balance = r_height - l_height;
}


void postorder_balance_check(struct Node **tree) {
    if ((*tree)->left != NULL) {
        postorder_balance_check(&((*tree)->left));
    }
    if ((*tree)->right != NULL) {
        postorder_balance_check(&((*tree)->right));
    }
    if ((*tree)->left != NULL || (*tree)->right != NULL) {
        get_height(tree);
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
    return tree;    
}


struct Node *avl_insert(struct Node *tree, struct Node *new_node) {
    if (tree == NULL) {
        return new_node;
    }
    else if (new_node->value < tree->value) {
        tree->left = avl_insert(tree->left, new_node);
    }
    else if (new_node->value > tree->value) {
        tree->right = avl_insert(tree->right, new_node);
    }

    get_height(&tree);
    if (tree->balance == 2) {

        if (tree->right != NULL && tree->right->balance < 0) {
            tree->right = little_right_rotation(tree->right);
        }

        return little_left_rotation(tree);
    }
    
    else if (tree->balance == -2) {

        if (tree->left != NULL && tree->left->balance > 0) {
            tree->left = little_left_rotation(tree->left);
        }

        return little_right_rotation(tree);
    }
    return tree;
}


struct Node *little_left_rotation(struct Node *tree) {
    struct Node *root = tree;
    struct Node *right_elem = tree->right;
    struct Node *elem_left_chain = right_elem->left;

    right_elem->left = root;
    root->right = elem_left_chain;
    get_height(&root);
    get_height(&right_elem);
    tree = right_elem;
    return tree;
}


struct Node *little_right_rotation(struct Node *tree) {
    struct Node *root = tree;
    struct Node *left_elem = tree->left;
    struct Node *elem_right_chain = left_elem->right;

    left_elem->right = root;
    root->left = elem_right_chain;
    get_height(&root);
    get_height(&left_elem);
    tree = left_elem;
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
            (*tree) = NULL;
        }
    }
}


void bfs_based_output(int n, struct Node *tree, FILE *fout) {
    struct Node **nodes_list = (struct Node **)malloc(n * sizeof(struct Node *));
    for (int i = 0; i < n; ++i) {
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
