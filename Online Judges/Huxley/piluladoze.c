#include <stdio.h>

int i, h[3], m[3];

int passado(int from, int to)
{
  int mEnd, minutos = 0;
  while (h[from] != h[to])
  {
    while (m[from] < 60)
    {
      m[from] ++;
      minutos ++;
    }
    m[from] = 0;
    h[from] ++;
    if (h[from] == 24)
    {
      h[from] = 0;
    }
  }
  while (m[from] < m[to])
  {
    m[from] ++;
    minutos ++;
  }
  return(minutos);
}

int main()
{
  int fail = 0;
  for (i = 0; i < 3; i ++)
  {
    scanf("%d %d", &h[i], &m[i]);
    if (i == 0)
    {
      if (h[i] < 12 || (h[i] == 12 || m[i] == 0))
      {
        printf("v\n");
      }
      else
      {
        printf("f\n"); fail ++;
      }
    }
    else if (i == 1)
    {
      if (passado(0, 1) == 192)
      {
        printf("v\n");
      }
      else
      {
        printf("f\n"); fail ++;
      }
    }
    else
    {
      if (passado(1, 2) == 1380)
      {
        printf("v\n");
      }
      else
      {
        printf("f\n"); fail ++;
      }
    }
  }
  if (fail == 0)
  {
    printf("sucesso\n");
  }
  else
  {
    printf("falha\n");
  }
  return(0);
}
//192
//1380
