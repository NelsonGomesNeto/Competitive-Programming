#include <stdio.h>

int main()
{
  int circ, azei; scanf("%d %d", &circ, &azei);
  int i, j, pizza[azei + 1], rate = circ / azei, will;
  for (i = 0; i < azei; i ++)
  {
    scanf("%d", &pizza[i]);
  } pizza[azei] = pizza[0] + circ;
  for (i = pizza[0]; i < pizza[1]; i ++)
  {
    int place = i; will = 1;
    for (j = 1; j <= azei; j ++)
    {
      if (place < pizza[j] && pizza[j] - place <= rate)
      {
        place += rate;
      }
      else
      {
        will = 0; break;
      }
    }
    if (will)
    {
      printf("S\n");
      return(0);
    }
  }
  printf("N\n");
  return(0);
}
/*12 3
2 8 11
12 3
0 8 9*/
