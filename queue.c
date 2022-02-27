#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "queue.h"

void resize(queue* q);

// new_queue returns a new queue with an allocated array of size capacity.
    // Make the queue
queue* new_queue(uint capacity) {
    queue* q = (queue *)malloc((sizeof *q));

    q->head = 0; // Items are dequeued from the head
    q->tail = 0; // and enqueued from the tail   

    // Allocate array
    q->cap = capacity;  // capacity is the 
    q->arr = (uint*)calloc(capacity, (sizeof(uint)));

    return q;
}

// resize increases 
void resize(queue* q) {
    int i;

    // reallocate array
    q->arr = (uint*)reallocarray(q->arr, q->cap*2, sizeof (uint));

    // move the head and everything after the head to the back
    for (i = q->head; i < q->cap; i++) {
        q->arr[i + q->cap] = q->arr[i];
    }
    q->head += q->cap;

    // double capacity
    q->cap *= 2;
}

// enqueue adds a new element at the tail, and then resizes if necessary.
void enqueue(queue* q, uint elem) {
    // The tail necessarily points to 
    q->arr[q->tail] = elem;
    q->tail++;

    if (q->tail == q->cap)      q->tail = 0; 
    if (q->tail == q->head)     resize(q);
}

// dequeue removes an element at the head, unless the queue is empty.
int dequeue(queue* q, uint* elem) {
    if (is_empty(q)) return 1;

    *elem = q->arr[q->head];
    q->head++;
    
    if (q->head == q->cap)      q->head = 0;
    return 0;
}

bool is_empty(queue* q) {
    return q->tail == q->head;
}

uint length(queue* q) {
    if (q->tail > q->head)
        return q->tail - q->head;
    return (q->cap - q->head) + q->tail;
}

void print_queue(queue* q) {
    printf("queue with head at %d and tail at %d: [", q->head, q->tail);
    for (int i = 0; i < q->cap; i++) {
        printf("%d, ", q->arr[i]);
    }
    printf("]\n");
}

void destroy_queue(queue* q) {
    free(q->arr);
    free(q);
}
