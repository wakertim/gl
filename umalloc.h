#ifndef UMALLOC_H
#define UMALLOC_H

#include "types.h"


#define MEMORY_TAG_NAMES							\
	X(MEMORY_STATS_TAG_STRING,		0)				\
	X(MEMORY_STATS_TAG_SHADER,		1)				\
	X(MEMORY_STATS_TAG_RENDERER,	2)				\
	X(MEMORY_STATS_TAG_MAX,			3)				\

typedef enum memory_stats_tag_t {

	#define X(name, num) name = num, 

	MEMORY_TAG_NAMES
	#undef X
} memory_stats_tag_t;


#define ALLOC(size, tag) umalloc(size, tag, __FILE__, __LINE__)
#define FREE(ptr, size, tag) ufree(ptr, size, tag)

void* umalloc(u64 s, enum memory_stats_tag_t tag, const char *file, u64 line);
void ufree(void *p, u64 s, enum memory_stats_tag_t tag);

void uprint(); 

#endif // UMALLOC_H
