
#include "pa10.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
Stack * Stack_delete(Stack * stack);

/**
 * Returns a pointer to a new empty stack.
 */
Stack * Stack_create()
{
  Stack * st = malloc(sizeof(Stack));
  st -> list = NULL;
  return st;
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you _must_ free the entire contained linked-list.
 * Also, you must safely to _nothing_ if stack == NULL. 
 */
void Stack_destroy(Stack * stack)
{
  if(Stack_isEmpty(stack))
    {
        return;
    }
    else
    {
      Stack * temp = NULL;
      temp = stack -> list;
      stack = stack -> list -> next;
      free(temp);
      Stack_destroy(stack);
    }
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
  if(stack -> next != NULL)
    {
      return TRUE;
    }
  if(stack -> list != NULL)
    {
      return TRUE;
    }
    return FALSE;
}

/**
 * Pop the front 'value' from the stack.
 *
 * More precisely, this function must do two things:
 * (1) Return the value of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 */
int Stack_pop(Stack * stack)
{
    if(Stack_isEmpty(stack))
        return -1;
    else
    {
        int value = stack -> list -> value;
	stack = Stack_delet(stack);
	return value;
    }
}

Stack * Stack_delete(Stack * stack)
{
  Stack * temp = NULL;
  temp = stack -> list -> next;
  free(stack);
  return temp;
}


/**
 * Push an 'value' onto the front of the stack.
 *
 * More precisely, this function must:
 * (1) Create a new ListNode with 'value' for it's value.
 * (2) Push that new ListNode onto the front of the stack's list.
 */
void Stack_push(Stack * stack, int value)
{
    if(Stack_isEmpty(stack))
    {
        ListNode * ln = malloc(sizeof(ListNode));
        ln -> value = value;
        ln -> next = NULL;
        stack -> list = ln;
    }
    else
    {
        ListNode * ln = malloc(sizeof(ListNode));
        ln -> value = value;
        ln -> next = stack -> list;
        stack -> list = ln;
    }
}

/**
 * Sort 'array' of length 'len' using Donald Knuth's "StackSort"
 *
 * To do this, you must implement the following pseudo-code:
 * (1) Maintain a 'write_index'. This is where you'll write values to
 *     as you sort them. It starts off as zero.
 * (2) Initialize an empty stack
 * (3) For each input value 'x':
 *     (3.a) While the stack is nonempty and 'x' is larger than the 
 *           front 'value' on the stack, pop 'value' and:
 *           (3.a.i) Write 'value' to array[write_index], and 
 *                   increment write_index.
 *     (3.b) Push x onto the stack.
 * (4) While the stack is nonempty, pop the front 'value' and follow
 *     step (3.a.i).
 *
 * The output should be a sorted array if, and only if, the array
 * is stack-sortable. You can find files full of stack-sortable and
 * stack-unsortable arrays in the 'expected' folder.
 */
void stackSort(int * array, int len)
{

}

/**
 * Return TRUE (1) if the 'array' of length 'len' is stack-sortable.
 *
 * To do this you must:
 * (1) If 'len' is less than 3, return TRUE.
 * (2) Find the maximum value in 'array'.
 * (3) Partition array into two parts: left of max, and right of max.
 * (4) The maximum value in left must be smaller than the minimum
 *     value in right. (Otherwise return FALSE.)
 * (5) Return TRUE if both left and right are stack-sortable.
 *
 * The 'expected' directory contains files for all sortable and 
 * unsortable sequences of length len. You must return TRUE for every
 * sequence in the sortable files, and you must return FALSE for every
 * sequence in the unsortable files.
 */
int isStackSortable(int * array, int len)
{
    if(len < 3)
    {
        return TRUE;
    }
    int max = array[0];
    int i;
    int loc = 0;
    for(i = 0; i < len; i++)
    {
        if(array[i] > max)
        {
            max = array[i];
            loc = i;
        }
    }
    int * left = NULL;
    int * right = NULL;
    if(loc != 0)//if there are no left part, the biggest number is in the leftmost
    {
        for(i = 0; i < loc; i++)
        {
            left[i] = array[i];
        }
    }
    if(loc != len - 1)//if there are no right part, the biggest number is the rightmost
    {
        for(i = loc + 1; i < len; i++)
        {
            right[i - loc - 1] = array[i];
        }
    }
    if((loc != 0) && (loc != len - 1))
      {
	int leftMax = get_Max(left, loc + 1);
	int rightMin = get_Min(right, len - loc - 1);
    
	if(leftMax < rightMIn)
	  {
	    if((isStackSortable(left, loc + 1)) && (isStackSortable(right, len - loc -1)))
	      {
		return TRUE;
	      }
	    else
	      {
		return FALSE;
	      }
	  }
	else//not necessary
	  {
	    return FALSE;
	  }
      }
    else if(loc == 0)
      {
	if(isStackSortable(right, len - 1))
	  {
	    return TRUE;
	  }
      }
    else if(loc == len - 1)
      {
	if(isStackSortable(left, len - 1))
	  {
	    return TRUE;
	  }
      }
    return FASLE;
}

int get_Max(int * array)
{
    int max = array[0];
    int i;
    for(i = 0; i < len; i++)
    {
        if(array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

int get_Min(int * array)
{
    int i;
    min = array[0];
    for(i = 0; i < len; i++)
    {
        if(array[i] < min)
        {
            min = array[i];
        }
    }
    return min;
}
/**
 * Generates (and prints) all the unique binary tree shapes of size k
 *
 * To do this, you must:
 * (1) Create an array with the elements [1..k] inclusive.
 * (2) Find all the permutations of this array.
 * (3) In the base-case of your permute function, you must test if the
 *     permutation is "stack-sortable"
 * (4) If the permutation is "stack-sortable", then build a binary
 *     tree, and print it using the "Tree_printShape(...)" function.
 *
 * Your genShapes() function must NOT produce duplicate tree shapes.
 * The correct outputs for sizes [1..9] are in the 'expected' 
 * directory.
 */
void genShapes(int k)
{

}




