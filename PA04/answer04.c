/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>
void partAllMemo(int);
void partAll(int *, int, int);
void partPrint(int *, int);
void partOddMemo(int);
void partOdd(int *, int, int);
void partEvenMemo(int);
void partEven(int *, int, int);
void partPrime(int *, int, int);
void partPrimeMemo(int);
void partIncrease(int *, int, int);
void partIncreaseMemo(int);
void partDecrease(int *, int, int);
void partDecreaseMemo(int);
void partOddEven(int *, int, int);
int isPrime(int);
void partOddEvenMemo(int);

/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */


void partitionAll(int value)
{
  printf("partitionAll %d\n", value);
  partAllMemo(value);

}

void partAllMemo(int n)
{
  int * buffer = malloc(n * sizeof(int));
  partAll(buffer,0,n);
  free(buffer);
}

void partAll(int * arr, int pos, int n)
{
  int i;

  if(n <= 0)
    {
      partPrint(arr,pos);
    }

  for(i = 1; i <= n; i++)
    {
      arr[pos] = i;
      partAll(arr, pos + 1, n - i);
    }
}

void partPrint(int * arr, int len)
{
  int i;
  
  printf("= ");
  if(len > 0)
    {
      printf("%d", arr[0]);
    }
  for(i = 1; i < len; i++)
    {
      printf(" + %d", arr[i]);
    }
  printf("\n");
}

/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */

void partitionIncreasing(int value)
{
  printf("partitionIncreasing %d\n", value);
  partIncreaseMemo(value);
}

void partIncreaseMemo(int n)
{
  int *buffer = malloc(n * sizeof(int));
  partIncrease(buffer,0,n);
  free(buffer);
}

void partIncrease(int * arr, int pos, int n)
{
  int i;

  if(n <= 0)
    {
      partPrint(arr,pos);
    }

  for(i = 1; i <= n; i++)
    {
      arr[pos] = i;
      if(pos > 0 && arr[pos - 1] < arr[pos])
	{
	  partIncrease(arr, pos + 1, n - i);
	}
      if(pos == 0)
	{
	  partIncrease(arr, pos + 1, n - i);
	}
    }
}


/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionDecreasing(int value)
{
  printf("partitionDecreasing %d\n", value);
  partDecreaseMemo(value);
}

void partDecreaseMemo(int n)
{
  int *buffer = malloc(n * sizeof(int));
  partDecrease(buffer,0,n);
  free(buffer);
}

void partDecrease(int * arr, int pos, int n)
{
  int i;

  if(n <= 0)
    {
      partPrint(arr,pos);
    }

  for(i = 1; i <= n; i++)
    {
      arr[pos] = i;
      if(pos > 0 && arr[pos - 1] > arr[pos])
	{
	  partDecrease(arr, pos + 1, n - i);
	}
      if(pos == 0)
	{
	  partDecrease(arr, pos + 1, n - i);
	}
    }
}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOdd(int value)
{
  printf("partitionOdd %d\n", value);
  partOddMemo(value);
}

void partOddMemo(int n)
{
  int * buffer = malloc(n * sizeof(int));
  partOdd(buffer,0,n);
  free(buffer);
}

void partOdd(int * arr, int pos, int n)
{
  int i;

  if(n <= 0)
    {
      partPrint(arr,pos);
    }

  for(i = 1; i <= n; i++)
    {
      if(i % 2 == 1)
	{
	  arr[pos] = i;
	  partOdd(arr, pos + 1, n - i);
	}
    }
}

/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionEven(int value)
{
  printf("partitionEven %d\n", value);
  partEvenMemo(value);
}

void partEvenMemo(int n)
{
  int *buffer = malloc(n * sizeof(int));
  partEven(buffer,0,n);
  free(buffer);
}

void partEven(int * arr, int pos, int n)
{
  int i;

  if(n <= 0)
    {
      partPrint(arr,pos);
    }

  for(i = 1; i <= n; i++)
    {
      if(i % 2 == 0)
	{
	  arr[pos] = i;
	  partEven(arr, pos + 1, n - i);
	}
    }
}

/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOddAndEven(int value)
{
  printf("partitionOddAndEven %d\n", value);
  partOddEvenMemo(value);
}

void partOddEvenMemo(int n)
{
  int *buffer = malloc(n * sizeof(int));
  partOddEven(buffer,0,n);
  free(buffer);
}

void partOddEven(int * arr, int pos, int n)
{
  int i;

  if(n <= 0)
    {
      partPrint(arr,pos);
    }

  for(i = 1; i <= n; i++)
    {
      if((pos % 2) != (i % 2))
	{  
	  arr[pos] = i;   
	  partOddEven(arr, pos + 1, n - i);
	}
    }
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */



void partitionPrime(int value)
{
  printf("partitionPrime %d\n", value);
  partPrimeMemo(value);
}

void partPrimeMemo(int n)
{
  int *buffer = malloc(n * sizeof(int));
  partPrime(buffer,0,n);
  free(buffer);
}

void partPrime(int * arr, int pos, int n)
{
  int i;
  int index = 0;

  if(n <= 0)
    {
      partPrint(arr,pos);
    }

  for(i = 1; i <= n; i++)
    {
      index = isPrime(i);
      if(index == 1)
	{
	  arr[pos] = i;
	  partPrime(arr, pos + 1, n - i);
	}
    }
}

int isPrime(int n)
{
  int ind;
  
  if(n == 1)
    return 0;
  if(n == 2)
    return 1;
  for(ind = 2; ind < n; ind++)
    {
      if(n % ind == 0)
	return 0;
    }
  return 1;
}
