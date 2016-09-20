#ifndef BINHEAP_H
# define BINHEAP_H

# ifdef __cplusplus
extern "C" {
# endif

# include <stdint.h>

struct binheap_hode;
//typedef struct binheap_node binheap_node_t;
typedef struct binheap_node heap_node_t;

typedef struct binheap {
  heap_node_t **array;
  uint32_t size;
  uint32_t array_size;
  int32_t (*compare)(const void *key, const void *with);
  void (*datum_delete)(void *);
} heap_t;
int heap_decrease_key_no_replace(heap_t *h, heap_node_t *n);
void binheap_init(heap_t *h,
                  int32_t (*compare)(const void *key, const void *with),
                  void (*datum_delete)(void *));
void binheap_init_from_array(heap_t *h,
                             void *array,
                             uint32_t size,
                             uint32_t nmemb,
                             int32_t (*compare)(const void *key,
                                                const void *with),
                             void (*datum_delete)(void *));
void binheap_delete(heap_t *h);
heap_node_t *binheap_insert(heap_t *h, void *v);
void *binheap_peek_min(heap_t *h);
void *binheap_remove_min(heap_t *h);
void binheap_decrease_key(heap_t *h, heap_node_t *n);
uint32_t binheap_is_empty(heap_t *h);

# ifdef __cplusplus
}
# endif

#endif