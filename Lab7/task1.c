#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX(x,y) (x > y ? x : y)

static int **tree;
void get_height(int *node);
void postorder_balance_check(int *node);

int main() {
    FILE *fin = fopen("balance.in", "r");
    FILE *fout = fopen("balance.out", "w");
    int n;
    fscanf(fin, "%d", &n);

    tree = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        tree[i] = (int *)malloc(4 * sizeof(int));
        tree[i][2] = 1;
        tree[i][3] = 0;
    }

    for (int i = 0; i < n; ++i) {
        int value;
        fscanf(fin, "%d", &value);
        fscanf(fin, "%d %d", &(tree[i][0]), &(tree[i][1]));
    }

    postorder_balance_check(tree[0]);
    for (int i = 0; i < n; ++i) {
        fprintf(fout, "%d\n", tree[i][3]);
    }

    for (int i = 0; i < n; ++i) {
        free(tree[i]);
    }
    free(tree);
    fclose(fin);
    fclose(fout);
    return 0;
}


void get_height(int *node) {
    int r_height = 0;
    int l_height = 0;

    if (node[0] != 0) {
        l_height = tree[node[0] - 1][2];
    }
    if (node[1] != 0) {
        r_height = tree[node[1] - 1][2];
    }

    node[2] = MAX(l_height, r_height) + 1;
    node[3] = r_height - l_height;
}


void postorder_balance_check(int *node) {
    if (node[0] != 0) {
        postorder_balance_check(tree[node[0] - 1]);
    }
    if (node[1] != 0) {
        postorder_balance_check(tree[node[1] - 1]);
    }
    if (node[0] != node[1]) {
        get_height(node);
    }
}
