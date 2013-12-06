struct Heap_
{
    int size;
    int (*compare)(const void *key1, const void *key2);
    void (*destory)(void *data);
    void **tree;
};
typedef struct Heap_ Heap;

void heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2), void (*destory)(void *data));
void heap_destory(Heap *heap);
int heap_insert(Heap *heap, const void *data);
int heap_extract(Heap *heap, void **data);

#define HEAP_SIZE(heap) ((heap)->size)
