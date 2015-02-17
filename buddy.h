#include <stddef.h>

typedef struct block
{
    int init;
    int size;
    int flag; //0 = free, 1 = allocated
    int addr;
    struct block  *parent;
    struct block  *left;
    struct block  *right;

}Block;
