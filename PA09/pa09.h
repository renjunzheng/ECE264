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


Stack * Stack_pop(Stack * st);
Stack * Stack_push(Stack * st, HuffNode * array);
Stack * Stack_create(HuffNode * array);
HuffNode * HuffNode_build(FILE * fptr);
HuffNode * HuffNode_create(int value);
void HuffNode_destroy(HuffNode * array);
void HuffNode_print(FILE * fptr, HuffNode * array);
int isLeaf(HuffNode * array);
#endif

