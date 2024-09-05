#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"

VectorQueue *VectorQueueInitialize(void) {
  VectorQueue *queue = malloc(sizeof *queue);
  if (!queue)
    abort();
  queue->capacity = INITIAL_CAPACITY*sizeof(Vector2);
  queue->array = malloc(queue->capacity);
  if (!queue->array)
    abort();

  return queue;
}

void VectorQueueFree(VectorQueue *queue) {
  free(queue->array);
  free(queue);
}

static bool isFull(VectorQueue *queue) {
  return (queue->rear+1) % queue->capacity == queue->front;
}

bool isEmpty(VectorQueue *queue) {
  return queue->front == queue->rear;
}

void push(VectorQueue *queue, Vector2 vector) {
  if (isFull(queue)) {
    int size = queue->capacity;
    queue->capacity *= 2;
    queue->array = realloc(queue->array, queue->capacity);
    if (!queue->array)
      abort();

    // Queue is wrapped around
    if (queue->rear < queue->front) {
      for (int i = 0; i<queue->front; i++) {
        queue->array[i + size] = queue->array[i];
      }
      queue->rear = queue->rear + size;
    }
  }
  queue->array[queue->rear++] = vector;
}

Vector2 pop(VectorQueue *queue) {
  return queue->array[queue->front++];
}
