#include <stdio.h>
#include <math.h>

int num, a[5], sol;

int check(int atual, int fim)
{
  int i;
  for (i = 0; i < fim; i ++)
  {
    if (a[i] == atual)
    {
      return(0);
    }
  }
  return(1);
}

int end = 0;

void bt(int i)
{
  if (end == 1)
  {
    return;
  }
  if (i == 5)
  {
    int k; int n = 0, divi = 0, decay = 10000;
    for (k = 0; k < 5; k ++)
    {
      divi += (a[k] * decay);
      decay /= 10;
    }
    n = divi * num; decay = 10000;
    if (n > 98765)
    {
      end = 1;
      return;
    }
    int aux = n, test[5], x;
    for (k = 0; k < 5; k ++)
    {
      aux = (n / decay) % 10;
      test[k] = aux;
      if (check(aux, 5) == 0)
      {
        return;
      }
      decay /= 10;
    }
    for (k = 0; k < 5; k ++)
    {
      for (x = 0; x < 5; x ++)
      {
        if (test[k] == test[x] && x != k)
        {
          return;
        }
      }
    }
    sol = 1;
    if (divi < 10000)
    {
      printf("%d / 0%d = %d\n", n, divi, num);
    }
    else
    {
      printf("%d / %d = %d\n", n, divi, num);
    }
    return;
  }
  int j;
  for (j = 0; j < 10; j ++)
  {
    if (check(j, i) == 1)
    {
      a[i] = j;
      bt(i + 1);
    }
  }
}

int main()
{
  int run = 0;
  while (scanf("%d", &num) && num != 0)
  {
    if (run > 0)
    {
      printf("\n");
    }
    run ++;
    sol = 0; end = 0;
    bt(0);
    if (sol == 0)
    {
      printf("There are no solutions for %d.\n", num);
    }
  }
  return(0);
}
