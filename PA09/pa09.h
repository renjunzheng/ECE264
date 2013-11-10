#ifndef PA09_H
#define PA09_H

typedef struct _huffnode {
    int value; 
    struct _huffnode * left;
    struct _huffnode * right;
} HuffNode;

typedef struct _stack {
    struct _stack * next;
    HuffNode * node;
} Stack;

HuffNode * HuffNode_create(int value);
void HuffNode_destroy(HuffNode * array);
void HuffNode_print(File * fptr, HuffNode * array);

#endif

