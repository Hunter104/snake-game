#pragma once
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 10

typedef struct VectorQueue {
  size_t capacity;
  Vector2 *array;
  size_t front, rear;
} VectorQueue;

VectorQueue *VectorQueueInitialize(void); 
void VectorQueueFree(VectorQueue *queue); 
bool isEmpty(VectorQueue *queue); 
void push(VectorQueue *queue, Vector2 vector); 
Vector2 pop(VectorQueue *queue); 
