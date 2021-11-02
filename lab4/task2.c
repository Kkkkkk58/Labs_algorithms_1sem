#include <stdio.h>
#include <stdlib.h>
#define TAIL_INIT 0
#define HEAD_INIT 0

struct Queue {
    long *array;
    long head;
    long tail;
    long length;
};

void enqueue(struct Queue *queue, long value);
long dequeue(struct Queue *queue);

int main() {
    FILE *fin = fopen("queue.in", "r");
    FILE *fout = fopen("queue.out", "w");
    long m;
    fscanf(fin, "%ld", &m);
    fgetc(fin);

    struct Queue queue;
    queue.array = (long *)malloc(m * sizeof(long));
    queue.head = HEAD_INIT;
    queue.tail = TAIL_INIT;
    queue.length = m;

    int operation;
    while ((operation = fgetc(fin)) != EOF) {
        fgetc(fin);
        
        if (operation == '-') {
            fprintf(fout, "%ld\n", dequeue(&queue));
        }
        else {
            long value;
            fscanf(fin, "%ld", &value);
            enqueue(&queue, value);
            fgetc(fin);
        }
    }

    free(queue.array);
    fclose(fin);
    fclose(fout);
    return 0;
}


void enqueue(struct Queue *queue, long value) {
    queue->array[queue->tail] = value;
    if (queue->tail == queue->length) {
        queue->tail = 0;
    }
    else {
        queue->tail = queue->tail + 1;
    }
}


long dequeue(struct Queue *queue) {
    long value = queue->array[queue->head];
    if (queue->head == queue->length) {
        queue->head = 0;
    }
    else {
        queue->head = queue->head + 1;
    }
    return value;
}