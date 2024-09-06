#pragma once
#include <stdlib.h>

void *safe_malloc(size_t n);
void *safe_realloc(void *ptr, unsigned long size);
