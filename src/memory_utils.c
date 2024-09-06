#include <stdio.h>
#include <stdlib.h>

void *safeMalloc(size_t n) {
  void *p = malloc(n);
  if (p == NULL) {
    fprintf(stderr, "Fatal: faile to allocate %zu bytes.\n", n);
    abort();
  }
  return p;
}

void *safeRealloc(void *ptr, unsigned long size) {
  void *p = realloc(ptr, size);
  if (p == NULL) {
    fprintf(stderr, "Fatal: faile to allocate %zu bytes.\n", size);
    abort();
  }
  return p;
}
