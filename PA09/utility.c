
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
int isLeaf(HuffNode * array)
{
  if(array == NULL)
    {
      return 1;
    }
  if(array -> left == NULL)
    {
      if(array -> right == NULL)
	{
	  return 1;
	}
    }
  return 0;
}

HuffNode * HuffNode_create(int value)
{
  HuffNode * array = malloc(sizeof(HuffNode));
  array -> value = value;
  array -> left = NULL;
  array -> righ = NULL;
  return array;
}

Stack * Stack_create(HuffNode * array)
{
  Stack * st;
  st = malloc(sizeof(Stack));
  st -> node = array;
  st -> next = NULL;
  return st;
}

//Write functions to perform push and pop to maintain the Stack
Stack * Stack_push(Stack * st, HuffNode * array)
{
  Stack * stnew = malloc(sizeof(Stack));
  stnew -> node = array;
  stnew -> next = st;
  return stnew;
}//need to check

Stack * Stack_pop(Stack * st)
{
  if (st == NULL)
    {
      return NULL;
    }
  Stack * next = st -> next
  free (st);
  return next;
}

Stack * Stack_build(File * fptr);
{
  Stack * st = NULL; // create an empty stack
  int done = 0;
  while(done == 0)//check if the tree is build, how?
    {
      command = fgetc(fptr);
      if(command == 1)
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
	      return A;
	    }
	  else
	    {
	      HuffNode * B = st -> node;
	      st = Stack_pop(st);
	      HuffNode * parent = malloc(sizeof(HuffNode));
	      parent -> value = ' '; // doesn't matter
	      parent -> right = A;
	      parent -> left = B;
	      st = Stack_push(st, parent);
	    }
	}
    }
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
    HuffNode_print(array -> left);
    fprintf(fptr,"Back\n");
    // Visit right
    fprintf(fptr,"Right\n");
    HuffNode_print(array -> right);
    fprintf(fptr,"Back\n");
    // Visit node itself (only if leaf)
    if (array -> left == NULL && array -> right == NULL)
      {
	fprintf(fptr,"Leaf: %c\n", arrat -> value);
      }
}
