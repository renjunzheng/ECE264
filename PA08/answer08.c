#include "pa08.h"
#include <stdio.h>
#include <stdlib.h>

SparseNode * SparseArray_help(SparseNode *, int,int);
SparseNode * SparseArray_merge2(SparseNode *, SparseNode *);
/* 
 * Create a single instance of a sparse array tree node with a specific
 * index and value. This Sparse array will be implemented by a binary tree.
 *
 * Arguments:
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the node just constructed
 *
 * This is a constructor function that allocates
 * memory for a sparse array tree node, and it copies the integer values, and sets the 
 * subtree pointers to NULL. 
 */

SparseNode * SparseNode_create(int index, int value)
{
  SparseNode * node = malloc(sizeof(SparseNode));
  node -> index = index;
  node -> value = value;
  node -> left = NULL;
  node -> right = NULL;
  return node;
}

/* Add a particular value into a sparse array tree on a particular index.
 *
 * Arguments:
 * *array        the root node of the sparse array tree
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the root node of the modified sparse 
 *               array tree
 *
 * The sparse array tree uses the index as a key in a binary search tree.
 * If the index does not exist, create it. 
 * If the index exists, REPLACE the value to the new one. Use the index to
 * determine whether to go left or right in the tree (smaller index
 * values than the current one go left, larger ones go right).
 */

SparseNode * SparseArray_insert(SparseNode * array, int index, int value)
{
  if(value == 0)
    {
      return array;
    }
  if(array == NULL)
    {
      return SparseNode_create(index, value);
    }
  if(array -> index == index)
    {
      array -> value = value;
      return array;
    }
  if(array -> index > index)
    {
      array -> left = SparseArray_insert(array -> left, index, value);
    }
  else
    {
      array -> right = SparseArray_insert(array -> right, index, value);
    }  
  return array;
}

/* Build a sparse array tree from given indices and values with specific length.
 *
 * Arguments:
 * index*         a pointer points to the start position of the index array
 * value*         a pointer points to the start position of the value array
 * length         the size of both array
 * 
 * returns:
 * SparseNode *   the pointer points to the root node of sparse array tree
 *                just constructed
 *
 * It returns a sparse array tree. 
 * You need to insert tree nodes in order
 *
 * (the first sparse array node contains indices[0] and values[0], second node
 * contains indices[1] and values[1]. Basically, each tree node is constructed
 * with each pair in indices and values array. In other words, elements of 
 * indices and values with the same index should go into the same node.)
 */

SparseNode * SparseArray_build(int * indicies, int * values, int length)
{
  int i;
  SparseNode * node = NULL;
  for(i = 0; i < length; i++)
    {
      node = SparseArray_insert(node, indicies[i], values[i]);
    }
  return node;
}

/* Destroy an entire sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * void
 *
 * traversing the binary tree in postorder. Use the
 * SparseNode_destroy () function to destroy each node by itself.
 */
void SparseArray_destroy (SparseNode * array )
{
  if(array == NULL)
    {
      return;
    }
  SparseArray_destroy(array -> left);
  SparseArray_destroy(array -> right);
  free(array);
}

/* Retrieve the smallest index in the sparse array tree.
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the smallest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMin ( SparseNode * array )
{
  while(array -> left != NULL)
    {
      array = array -> left;
    }
  return array->index;
}

/* Retrieve the largest index in the sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the largest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMax ( SparseNode * array )
{ 
  while(array -> right != NULL)
    {
      array = array -> right;
    }
  return array->index;
}


/* Retrieve the node associated with a specific index in a sparse
 * array tree.  
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to search
 * 
 * returns:
 * SparseNode*    the node with the index that you searched from the tree.
 *                If no node found, NULL should be returned. 
 *                
 * Hint: If the given index is smaller than the current
 * node, search left ; if it is larger, search right.
 */
SparseNode * SparseArray_getNode(SparseNode * array, int index )
{
  if(array == NULL)
    {
      return NULL;
    }
  if(array -> index == index)
    {
      return array;
    }
  if(array -> index > index)
    {
      return SparseArray_getNode(array -> left, index);
    }
  return SparseArray_getNode(array -> right, index);
}

/* Remove a value associated with a particular index from the sparse
 * array. It returns the new
 * sparse array tree ( binary tree root ). 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to remove
 * 
 * returns:
 * SparseNode*    the root node of the sparse array tree that you just modified
 *          
 *    
 * HINT : First, you need to find that node. Then, you will need to isolate
 * several different cases here :
 * - If the array is empty ( NULL ), return NULL
 * - Go left or right if the current node index is different.

 * - If both subtrees are empty, you can just remove the node.

 * - If one subtree is empty, you can just remove the current and
 * replace it with the non - empty child.

 * - If both children exist, you must find the immediate successor of
 * the current node ( leftmost of right branch ), swap its values with
 * the current node ( BOTH index and value ), and then delete the
 * index in the right subtree.
*/
SparseNode * SparseArray_remove ( SparseNode * array, int index )
{
  if(array == NULL)
    {
      return NULL;
    }
  if(array -> index > index)
    {
      array -> left = SparseArray_remove(array -> left, index);
      return array;
    }
  if(array -> index < index)
    {
      array -> right = SparseArray_remove(array -> right, index);
      return array;
    }
  if((array -> left == NULL) && (array -> right == NULL))
    {
      free(array);
      return NULL;
    }
  if(array -> left == NULL)
    {
      SparseNode * temp = array -> right;
      free(array);
      return temp;
    }
  if(array -> right == NULL)
    {
      SparseNode * temp = array -> left;
      free(array);
      return temp;
    }
  SparseNode * successor = array -> right;
  while((successor -> left) != NULL)
    {
      successor = successor -> left;
    }
  array -> index = successor -> index;
  successor -> index = index;
  int value = array -> value;
  array -> value = successor -> value;
  successor -> value = value;
  array -> right = SparseArray_remove(array -> right, index);
  return array;
}

/* The function makes a copy of the input sparse array tree
 * and it returns a new copy. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                copied from the input sparse array tree.
 *       
 */

SparseNode * SparseArray_copy(SparseNode * array)
{
  if(array == NULL)
    return NULL;
  SparseNode * node = malloc(sizeof(SparseNode));
  node -> index = array -> index;
  node -> value = array -> value;
  node -> left = SparseArray_copy(array -> left);
  node -> right = SparseArray_copy(array -> right);
  return node;
}

/* Merge array_1 and array_2, and return the result array. 
 * This function WILL NOT CHANGE the contents in array_1 and array_2.
 *
 * Arguments:
 * *array_1         the root node of the first sparse array tree
 * *array_2         the root node of the second sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                merged from the two input sparse array tree
 *     
 * When merging two sparse array tree:
 * 1. The contents in array_1 and array_2 should not be changed. You should make
 *    a copy of array_1, and do merging in this copy.
 * 2. array_2 will be merged to array_1. This means you need to read nodes in 
 *    array_2 and insert them into array_1.
 * 3. You need to use POST-ORDER to traverse the array_2 tree. 
 * 4. Values of two nodes need to be added only when the indices are the same.
 * 5. A node with value of 0 should be removed.
 * 6. if array_2 has nodes with index different than any nodes in array_1, you
 *    should insert those nodes into array_1.
 * 
 * Hint: you may write new functions
 */

 SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
  SparseNode * node = SparseArray_copy(array_1);
  node = SparseArray_merge2(node, array_2);
  return node;
}

SparseNode * SparseArray_merge2(SparseNode * node, SparseNode * temp)
{
  if(temp == NULL)
  {
    return node;
  }
  node = SparseArray_merge2(node, temp -> left);
  node = SparseArray_merge2(node, temp -> right);
  node = SparseArray_help(node, temp -> index, temp -> value);

  return node;
}

SparseNode * SparseArray_help(SparseNode * array, int index, int value)
{
  if(value == 0)
    {
      return array;
    }
  if(array == NULL)
    {
      return SparseNode_create(index, value);
    }
  if(array -> index == index)
    {
      array -> value += value;
      if(array -> value == 0)
	{
	  array = SparseArray_remove(array,array->index);
	}
      return array;
    }
  if(array -> index > index)
    {
      array -> left = SparseArray_help(array -> left, index, value);
    }
  else
    {
      array -> right = SparseArray_help(array -> right, index, value);
    }
  return array;
}

 
