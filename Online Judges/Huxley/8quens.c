#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int solutions;

int check(int array[], int y, int x, int fim)
{
  int i;
  for (i = 1; i < fim; i ++)
  {
    if (abs(y - array[i]) == abs(i - x) || array[i] == y)
    {
      return(0);
    }
  }
  return(1);
}

int checkSol(int array[])
{
  int i, j, all;
  for (i = 1; i < 9; i ++)
  {
    for (j = i + 1, all = 1; all < 8; j ++, all ++)
    {
      j %= 9;
      if (j == 0)
      {
        j = 1;
      }
      if (abs(array[i] - array[j]) == abs(j - i) || array[j] == array[i])
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
    findsol(array, i + 1, nope, nopeX);
    return;
  }
  if (i == 9)
  {
    if (checkSol(array) == 1)
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
    }
    return;
  }
  int j;
  for (j = 1; j < 9; j ++)
  {
    if (j != nopeX)
    {
      if (check(array, j, i, i) == 1)
      {
        array[i] = j;
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
