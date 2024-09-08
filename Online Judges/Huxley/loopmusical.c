#include <stdio.h>

int main()
{
  int mag;
  while (scanf("%d", &mag) && mag != 0)
  {
    int song[mag], i, j;
    for (i = 0; i < mag; i ++)
      scanf("%d", &song[i]);

    int peaks = 0, upDown = 2, end;
    for (i = 0, j = 1, end = 0; end <= mag; i ++, j ++, end ++)
    {
      i %= mag; j %= mag;
      if (song[i] > song[j] && (upDown == 1 || upDown == 2))
      {
        if (end != 0)
          peaks ++;

        upDown = 0;
      }
      if (song[i] < song[j] && (upDown == 0 || upDown == 2))
      {
        if (end != 0)
          peaks ++;

        upDown = 1;
      }
    }

    printf("%d\n", peaks);
  }
  return(0);
}
