#include "pa07.h"
#include <stdio.h>
#include <stdlib.h>
Node * Node_insert(Node *, int, int);
/**
 * Prints a linked-list "head" into the output fie "out"
 *
 * NOTE: we have given the code for this function
 */
void List_print(FILE * out, Node * head)
{
 while(head != NULL)
	{
	    fprintf(out, "%5d: %6d\n", head -> index, head -> value);
	    head = head -> next;
	}
 printf("\n");
}


/**
 * Please fill in the code below
 */

/**
 * Destroys a linked list.
 * Arguments:
 * head    A pointer pointing to the first element of the linked list.
 *
 * Returns:
 * void
 *
 * Destroys (frees memory for) the whole linked list. 
 * You can either use recursion or a while loop.
 */
void List_destroy(Node * head)
{
  Node * temp;
  while(head != NULL)
  {
    temp = head -> next;
    free(head);
    head = temp;
  }
}

/**
 * Create and initialize a linked list. 
 *
 * Arguments:
 * value     The "value" of the new node
 * index     The "index" of the new node
 *
 * Returns:
 * Returns a newly constructed node. The node can be the head of a
 * linked list.
 * 
 * You should allocate memory in this function. 
 */
Node * List_create(int value, int index)
{
  Node * node;
  node = malloc(sizeof(Node));
  node -> next = NULL;
  node -> value = value;
  node -> index = index;
  return node;
}

/**
 * Build a sparse array from the given indices and values with 
 * specific length.
 *
 * Arguments:
 * value    Array of values
 * index    Array of indices
 * length   Length of the above arrays
 *
 * Returns:
 * A sparse array.
 *
 * If a sparse array node has { value = 1000, index = 2 }, then that means that
 * the index "2" caries the value "1000". This is meant to convey an array of 1000 
 * "2s", but instead of creating 1000 nodes in your linked list, you only create
 * 1 node, and that note conceptually has 1000 "copies" of it. Hence 
 * each node in a sparse array has a "value" in addition to its "index".
 *
 * Note that an index can never carry the value of "0", because this would not make
 * any sense; however, negative values are fine. A negative value may seem odd
 * at first blush; however, this is like substraction, and makes sense for certain
 * cases.
 *
 * You need to insert nodes in ascending order by index.
 * See the notes to "List_insert_ascend"
 */
Node * List_build(int * value, int * index, int length)
{
  Node * node = NULL;
  int i = 0;
  for(i = 0; i < length; i++)
    {
      if(value[i] != 0)
	{
	  node = List_insert_ascend(node, value[i], index[i]);
	}
    }
    return node;
}


/**
 * Inserting "value" and "index" into the correct location in the 
 * sparse array "head"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the linked list.
 * value     The "value" of the value
 * index     The "value" of the index
 *
 * Returns:
 * A sparse array
 *
 * This function inserts the node ["value", "index"] into the sparse
 * array "head", and ensures that the nodes remain in ascending order
 * by their "index".
 *
 * Before and after the call to this function, "head" must be in
 * ASCENDING order by the "index" of each node.
 */
Node * List_insert_ascend(Node * head, int value, int index)
{
  if(head == NULL)
    {
      return List_create(value, index);
    }
  if((head -> index) == index)
    {
      return head;
    }
  if((head -> index) > index)
    {
      Node * temp = List_create(value, index);
      temp -> next = head;
      return temp;
    }

  head -> next = List_insert_ascend(head -> next, value, index);
  return head;
}


/**
 * This function deletes the node with the passed "index"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the sparse array.
 * index     The index to be deleted
 *
 * Returns: 
 * A sparse array with the node removed (the one with index)
 */
Node * List_delete(Node * head, int index)
{
  Node * temp = head;
  if(temp == NULL)
    {
      return temp;
    }
  if(temp -> index == index)
    {
      temp = temp -> next;
      free(head);
      return temp;
    }
  Node * temp2 = temp -> next;
  while((temp2 != NULL) && (temp2 -> index != index))
    {
      temp = temp -> next;
      temp2 = temp2 -> next;
    }
  if(temp2 != NULL)
    {
      temp -> next = temp2 -> next;
      free(temp2);
    }
  return head;
}

/**
 * Copy a list
 *
 * Arguments:
 * head      A pointer pointing to the first element of the sparse array
 *
 * Returns:
 * A copy sparse array
 *
 * This function will copy the sparse array that is passed to it. The
 * copy will be made into new memory. 
 *
 * This is useful, for example, when we want to merge
 * two linked lists together. We can make a copy of one of the linked
 * lists, and then merge the second into the copy. In this way the
 * original copy of the list is not "mutated".
 */
Node * List_copy(Node * head)
{
  if(head == NULL)
    {
      return head;
    }
  Node * temp = malloc(sizeof(Node));
  temp -> next = NULL;
  temp -> value = head -> value;
  temp -> index = head -> index;
  temp -> next = List_copy(head -> next);

  return temp;
}


/**
 * Merged two linked list together
 * 
 * Arguments:
 * head1      A pointer pointing to linked list 1
 * head2      A pointer pointing to linked list 2
 *
 * Returns:
 * A merged sparse array
 *
 * This function will merge two linked lists. Before merging, you 
 * should make a copy of "head1" so that you will still have the 
 * original array while modifying (merging) the second linked list. 
 *
 * Please refer to the README file for detailed instructions on how to
 * merge two lists.
 *
 * This function should not modify either "head1" or "head2". You only
 * need to make a clone of "head1".
 */
Node * List_merge(Node * head1, Node * head2)
{
  Node * temp = List_copy(head1);
  while(head2 != NULL)
	{
	  temp = Node_insert(temp, head2 -> value, head2 -> index);
	  head2 = head2 -> next;
	}
  return temp;
}

Node * Node_insert(Node * head1, int value, int index)
{
  if(head1 == NULL)
    {
      return List_create(value, index);
    }
  if((head1 -> index) == index)
    {
      if(head1 -> value + value == 0)
	{
	  Node * temp = head1 -> next;
	  free(head1);
	  return temp;
	}
      head1 -> value += value;
      return head1;
    }
  if(head1 -> index > index)
    {
      Node * temp = List_create(value, index);
      temp -> next = head1;
      return temp;
    }
  head1 -> next = Node_insert(head1 -> next, value, index);
  return head1;
}
