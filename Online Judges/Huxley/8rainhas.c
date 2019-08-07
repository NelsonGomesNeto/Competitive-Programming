#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int solutions;

int check(int array[], int fim)
{
  int i, j, all;
  for (i = 1; i < fim; i ++)
  {
    for (j = i + 1; j <= fim; j ++)
    {
      if ((i != j) && (abs(array[i] - array[j]) == abs(j - i) || array[j] == array[i]))
      {
        return(0);
      }
    }
  }
  return(1);
}

void findsol(int array[], int i, int nope, int nopeX)
{
  if (i == nope)
  {
    if (check(array, i) == 1)
    {
      findsol(array, i + 1, nope, nopeX);
    }
    return;
  }
  if (i == 9)
  {
    solutions ++;
    int k;
    if (solutions < 10)
    {
      printf(" ");
    }
    printf("%d      ", solutions);
    for (k = 1; k < 8; k ++)
    {
      printf("%d ", array[k]);
    } printf("%d\n", array[k]);
    return;
  }
  int j;
  for (j = 1; j < 9; j ++)
  {
    if (j != nopeX)
    {
      array[i] = j;
      if (check(array, i) == 1)
      {
        findsol(array, i + 1, nope, nopeX);
      }
    }
  }
}

int main()
{
  int testes, run = 0;
  scanf("%d", &testes);
  while (testes > 0)
  {
    if (run > 0)
    {
      printf("\n");
    }
    run ++;
    int y, x; scanf("%d %d", &x, &y);
    int array[9];
    solutions = 0;
    array[y] = x;
    printf("SOLN       COLUMN\n");
    printf(" #      1 2 3 4 5 6 7 8\n");
    printf("\n");
    findsol(array, 1, y, x);
    testes --;
  }
  return(0);
}
