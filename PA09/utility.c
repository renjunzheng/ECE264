
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

//If the input is char
HuffNode * HuffNode_create(int value)
{
  HuffNode * array = malloc(sizeof(HuffNode));
  array -> value = value;
  array -> left = NULL;
  array -> right = NULL;
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
}

Stack * Stack_pop(Stack * st)
{
  if (st == NULL)
    {
      return NULL;
    }
  Stack * next = st -> next;
  free(st);
  return next;
}

HuffNode * HuffNode_build(FILE * fptr)
{
  Stack * st = NULL;
  int done = 0;
  HuffNode * A = NULL;
  while(done == 0)
    {
      int command = fgetc(fptr);
      if(command == '1')//ASCII value here
	{
	  int value = fgetc(fptr);
	  HuffNode * temp = HuffNode_create(value);
	  st = Stack_push(st, temp);
	}
      if (command == '0')
	{
	  A = st -> node;
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
	      parent -> value = 0;
	      parent -> right = A;
	      parent -> left = B;
	      st = Stack_push(st, parent);
	    }
	}
    }
  return NULL;
}

//if input is bit
HuffNode * Bit_build(FILE * fptr)
{
  Stack * st = NULL;
  HuffNode * A = NULL;
  int done = 0;
  int cmdloc = 0;
  unsigned char onebyte = fgetc(fptr);
  unsigned char masks[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
  while(done == 0)
    {
      unsigned char command = (onebyte & masks[cmdloc]);
      if(command != 0)
	{
	  unsigned char upbits = onebyte << (cmdloc + 1);
	  unsigned char anotherbyte = fgetc(fptr);
	  unsigned char lowbits = anotherbyte >> (7 - cmdloc);
	  unsigned char data = upbits | lowbits;
	  onebyte = anotherbyte;
	  HuffNode * temp = HuffNode_create(data);
	  st = Stack_push(st, temp);
	}
      else
	{
	  A = st -> node;
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
	      parent -> value = 0;
	      parent -> right = A;
	      parent -> left = B;
	      st = Stack_push(st, parent);
	    }
	}
      if(cmdloc == 7)
	{
	  onebyte = fgetc(fptr);
	}
      cmdloc = (cmdloc + 1) % 8;
    }
  return NULL;
}


/*use your own modified function postOrderPrint to print the traverse 
of the tree
 */
void HuffNode_print(FILE * fptr, HuffNode * array)
{
  // Base case: empty subtree
    if(array == NULL)
      {
	return;
      }

    // Recursive case: post-order traversal

    // Visit left
    fprintf(fptr,"Left\n");
    HuffNode_print(fptr,array -> left);
    fprintf(fptr,"Back\n");
    // Visit right
    fprintf(fptr,"Right\n");
    HuffNode_print(fptr,array -> right);
    fprintf(fptr,"Back\n");
    // Visit node itself (only if leaf)
    if (array -> left == NULL && array -> right == NULL)
      {
	fprintf(fptr,"Leaf: %c\n", array -> value);
      }
}

void HuffNode_destroy(HuffNode * array)
{
  if(array == NULL)
    {
      return;
    }
  HuffNode_destroy(array -> left);
  HuffNode_destroy(array -> right);
  free(array);
}


