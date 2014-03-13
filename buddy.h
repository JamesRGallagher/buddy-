#include <stddef.h>

typedef struct block
{
    int size;
    int position;
    int flag; //0 = free, 1 = allocated
    struct block* next;
}Block;
