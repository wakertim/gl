#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "umalloc.h"

#define X(name, num) #name ,
char *memory_tag_strings[] = {
	MEMORY_TAG_NAMES
};
#undef X

typedef struct {
	u64 total_size;
	u64 tag_size[MEMORY_STATS_TAG_MAX];
} memory_stats_t;
static memory_stats_t stats;

void* 
umalloc(u64 s, memory_stats_tag_t tag, const char *file, u64 line)
{
	void *ptr = malloc(s);
	stats.total_size += s;
	stats.tag_size[tag] += s;

	return ptr;
}

void
ufree(void *p, u64 s, memory_stats_tag_t tag)
{
	free(p);
	stats.total_size -= s;
	stats.tag_size[tag] -= s;
}

void
uprint() 
{
	printf("Memory usage;\n");
	printf("Total = %llu\n",stats.total_size); 
	for (int i = 0; i < MEMORY_STATS_TAG_MAX; ++i ) {
		printf("%s = %llu \n", memory_tag_strings[i], stats.tag_size[i]);
	}
}


