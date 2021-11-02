#include <stdio.h>
#include <stdlib.h>
#define INIT_TOP -1

struct Stack {
    long *array;
    long top;
};

void push_in(struct Stack *stack, long value);
long pop_out(struct Stack *stack);


int main() {
    FILE *fin = fopen("stack.in", "r");
    FILE *fout = fopen("stack.out", "w");
    long m;
    fscanf(fin, "%ld", &m);
    fgetc(fin);

    struct Stack stack;
    stack.top = INIT_TOP;
    stack.array = (long *)malloc(m * sizeof(long));

    int operation;
    while ((operation = fgetc(fin)) != EOF) {
        fgetc(fin);

        if (operation == '-') {
            fprintf(fout, "%ld\n", pop_out(&stack));
        }
        else {
            long value;
            fscanf(fin, "%ld", &value);
            push_in(&stack, value);
            fgetc(fin);
        }
    }

    free(stack.array);
    fclose(fin);
    fclose(fout);
    return 0;
}


void push_in(struct Stack *stack, long value) {
    stack->top = stack->top + 1;
    stack->array[stack->top] = value;
}


long pop_out(struct Stack *stack) {
    long value = stack->array[stack->top];
    stack->top = stack->top - 1;
    return value;
}