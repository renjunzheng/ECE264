#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"
#include <string.h>
int main ( int argc , char ** argv )
{
  //Check argc, print error message if the number of arguments are not correct
  if (argc != 3)
    {
      printf("usage: ./pa09 <input file> <output file>\n");
      return EXIT_FAILURE;
    }

  //Open the input file, check if the file has been opened correctly, if not, print error message
  FILE * fptr = NULL;
  fptr = fopen(argv[1], "r");
  if (fptr == NULL)
    {
      printf("File error!\n");
      return EXIT_FAILURE;
    }
  
  //Call a function to create Huffman Tree, return the head of the tree
  HuffNode * array = NULL;
  const char * f = argv[1];
  int len = strlen(f);
  if(len >= 3)
    {
      if(strcmp(f + (len - 3),"bit") != 0)
	{
	  array = HuffNode_build(fptr);
	}
      else
	{
	  array = Bit_build(fptr);
	}
    }

  //Open an output file, use your own modified function postOrderPrint to print the traverse of the tree
  fptr = fopen(argv[2], "w");
  HuffNode_print(fptr, array);
  if (fptr == NULL)
    {
      printf("output file error\n");
      return EXIT_FAILURE;
    }

  HuffNode_destroy(array);
  fclose(fptr);
}
