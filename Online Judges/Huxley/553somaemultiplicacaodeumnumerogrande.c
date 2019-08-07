#include <stdio.h>

void printNum(int a[])
{
  int i = 0, printed = 0;
  while (a[i] == 0) i ++;

  while (i < 100000)
  {
    printf("%d", a[i ++]);
    printed = 1;
  }

  if (printed == 0)
    printf("0");

  printf("\n");
}

int readNum(int a[])
{
  int i; char lineBreak;

  i = 0;
  while (scanf("%c", &lineBreak) != EOF && lineBreak != '\n')
  {
    a[i] = lineBreak - 48;
    i ++;
  }
  return(i);
}

void sum(int a[], int sizeA, int b[], int sizeB)
{
  int i, j, new[100000], k, m;
  for (i = 0; i < 100000; i ++)
    new[i] = 0;

  for (i = sizeB - 1, j = sizeA - 1, m = 100000 - 1; i >= 0 || j >= 0; i --, j --, m --)
  {
    if (j < 0)
      new[m] += b[i];
    else if (i < 0)
      new[m] += a[j];
    else
      new[m] += (a[j] + b[i]);

    k = m;
    while (new[k] > 9) // Sums carry
    {
      new[k - 1] += (new[k] / 10);
      new[k] %= 10;
      k --;
    }
  }

  printNum(new);
}

void multiply(int a[], int sizeA, int b[], int sizeB)
{
  int i, j, new[100000], k, m;
  for (i = 0; i < 100000; i ++)
    new[i] = 0;

  for (i = sizeB - 1; i >= 0; i --)
  {
    for (j = sizeA - 1, m = 100000 - (sizeB - i); j >= 0; j --, m --)
    {
      new[m] += (a[j] * b[i]);
      k = m;
      while (new[k] > 9) // Sums carry
      {
        new[k - 1] += (new[k] / 10);
        new[k] %= 10;
        k --;
      }
    }
  }

  printNum(new);
}

int main()
{
  int numA[100000], numB[100000], sizeA, sizeB;

  sizeA = readNum(numA); sizeB = readNum(numB);
  //printNum(numA); printNum(numB);

  sum(numA, sizeA, numB, sizeB);
  multiply(numA, sizeA, numB, sizeB);

  return(0);
}
