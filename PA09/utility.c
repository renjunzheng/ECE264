
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pa09.h"

/*Write a function that can create Huffman Tree based on input
(You will need to check if the input is char-based or bit-based,
they are different, so your create Huffman Tree should be able
to handle both cases)
*/
int isLeaf(HuffNode * tn)
{
  if (tn == NULL) { return 1; }
  if ((tn -> left) == NULL)
    {
      if ((tn -> right) == NULL)
	{
	  return 1;
	}
    }
  return 0;
}

HuffNode * HuffNode_create(int value)
{
  HuffNode * array = NULL;
  array = malloc(sizeof(Huffnode));
  while()
    {
      
    }
}




//Write functions to perform push and pop to maintain the Stack
Stack * Stack_push(Stack * st, HuffNode * t)
{
  Stack * stnew = malloc(sizeof(Stack));
  stnew -> node = t;
  stnew -> next = st;
  return stnew;
}

/*use your own modified function postOrderPrint to print the traverse 
of the tree
 */
void HuffNode_print(File * fptr, HuffNode * array)
{
  // Base case: empty subtree
    if(array == NULL)
      {
	return;
      }

    // Recursive case: post-order traversal

    // Visit left
    fprintf(fptr,"Left\n");
    Huff_postOrderPrint(tree->left);
    fprintf(fptr,"Back\n");
    // Visit right
    fprintf(fptr,"Right\n");
    Huff_postOrderPrint(tree->right);
    fprintf(fptr,"Back\n");
    // Visit node itself (only if leaf)
    if (tree->left == NULL && tree->right == NULL)
      {
	fprintf(fptr,"Leaf: %c\n", tree->value);
      }
}
