
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct {
    uint cap;
    uint len;
    int head;
    int tail;
    uint* arr;
} queue;

queue* new_queue(uint cap);

void enqueue(queue* q, uint elem);
int dequeue(queue* q, uint* res);

void print_queue();
bool is_empty(queue* q);
uint length(queue* q);

void destroy_queue(queue* q);
