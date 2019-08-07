#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int begin, end;

int valid(int a[], int fim)
{
  int i, beg = 0;
  for (i = 0; i < fim; i ++)
  {
    if (a[i] > a[i - 1])
    {
      if (beg < begin)
      {
        return(0);
      }
    }
    else
    {
      beg ++;
    }
    if (beg > begin)
    {
      return(0);
    }
  }
  return(1);
}

int check(int a[], int atual, int fim)
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

int possivel;

void BT(int a[], int i, int fim)
{
  if (i == fim)
  {
    possivel ++;
    return;
  }
  int numeros;
  for (numeros = 1; numeros <= fim; numeros ++)
  {
    if (check(a, numeros, i) == 1)// && valid(a, i) == 1)
    {
      a[i] = numeros;
      BT(a, i + 1, fim);
    }
  }
}


int main()
{
  int tests; scanf("%d", &tests);
  while (tests > 0)
  {
    int pessoas; scanf("%d", &pessoas);
    scanf("%d %d", &begin, &end);
    int p[pessoas], i;
    for (i = 0; i < pessoas; i ++)
    {
      p[i] = i;
    }
    possivel = 0; int beg, en, j, stB, stE;
    while (next_permutation(p, p + pessoas))
    {
      beg = 1; en = 1; stB = 0; stE = 0;
      for (i = 0, j = pessoas - 1; i < pessoas - 1; i ++, j --)
      {
        if (i == j)
        {
          break;
        }
        if (p[i] < p[i + 1])
        {
          if (stB == 0)
          {
            beg ++;
          }
        }
        else
        {
          stB = 1;
        }
        if (p[j] < p[j - 1])
        {
          if (stE == 0)
          {
            en ++;
          }
        }
        else
        {
          stE = 1;
        }
      }
      //printf("%d %d\n", beg, en);
      if (beg == begin && en == end)
      {
        possivel ++;
      }
    }
    //BT(p, 0, pessoas);
    printf("%d\n", possivel);
    tests --;
  }
  return(0);
}
