#include <stdlib.h>

#include "tree.h"

/* DO NOT MODIFY THIS FUNCTION!!! */
void Huff_postOrderPrint(HuffNode *tree)
{
    // Base case: empty subtree
    if (tree == NULL) {
		return;
    }

    // Recursive case: post-order traversal

    // Visit left
    printf("Left\n");
    Huff_postOrderPrint(tree->left);
	printf("Back\n");
    // Visit right
    printf("Right\n");
    Huff_postOrderPrint(tree->right);
	printf("Back\n");
    // Visit node itself (only if leaf)
    if (tree->left == NULL && tree->right == NULL) {
		printf("Leaf: %c\n", tree->value);
    }
    

}









Stack * Stack(File * fptr);
{
  Stack * st = NULL; // create an empty stack
  command = fgetc(fptr);
  if (command == 1)
    {
      int value = fgetc(fptr);
      HuffNode * temp = HuffNode_create(value);
      st = Stack_push(st, temp);
    }
  if (command == 0)
    {
      HuffNode * A = st -> array;
      st = Stack_pop(st);
      if (st == NULL)
	{
	  done = 1;
	  // A is the root;
	  return A;
	}
      else
	{
	  HuffNode * B = st -> tn;
	  st = Stack_pop(st);
	  HuffNode * par = malloc(sizeof(HuffNode));
	  par -> value = ' '; // doesn't matter
	  par -> right = A;
	  par -> left = B;
	  st = Stack_push(st, par);
      }
  }
}
