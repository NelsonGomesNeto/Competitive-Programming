#include <stdio.h>
#include <stdlib.h>

int main()
{
  int maior, menor;
  while (scanf("%d %d", &maior, &menor) && !(maior == 0 && menor == 0))
  {
    char m[maior][maior], n[menor][menor];
    int j, i, d, d90, d180, d270;
    for (j = 0; j < maior; j ++)
    {
      getchar();
      scanf("%s", m[j]);
    }
    for (j = 0; j < menor; j ++)
    {
      getchar();
      scanf("%s", n[j]);
    }
    int jM, iM, nope;
    d = 0;//Check d
    for (j = 0; j <= maior - menor; j ++)
    {
      for (i = 0; i <= maior - menor; i ++)
      {
        nope = 0;
        for (jM = 0; jM < menor; jM ++)
        {
          for (iM = 0; iM < menor; iM ++)
          {
            //printf("%c", n[jM][iM]);
            if (m[j + jM][i + iM] != n[jM][iM])
            {
              jM = menor; iM = menor;
              nope ++;
              break;
            }
          }
          //printf("\n");
        }
        if (nope == 0)
        {
          d ++;
        }
      }
    }
    int y, x;
    d90 = 0;//Check d90
    for (j = 0; j <= maior - menor; j ++)
    {
      for (i = 0; i <= maior - menor; i ++)
      {
        nope = 0;
        for (iM = 0, y = 0; iM < menor; iM ++, y ++)
        {
          for (jM = menor - 1, x = 0; jM >= 0; jM --, x ++)
          {
            if (m[j + y][i + x] != n[jM][iM])
            {
              jM = -1; iM = menor;
              nope ++;
              break;
            }
          }
        }
        if (nope == 0)
        {
          d90 ++;
        }
      }
    }
    d180 = 0;//Check d180
    for (j = 0; j <= maior - menor; j ++)
    {
      for (i = 0; i <= maior - menor; i ++)
      {
        nope = 0;
        for (jM = menor - 1, y = 0; jM >= 0; jM --, y ++)
        {
          for (iM = menor - 1, x = 0; iM >= 0; iM --, x ++)
          {
            if (m[j + y][i + x] != n[jM][iM])
            {
              jM = - 1; iM = -1;
              nope ++;
              break;
            }
          }
        }
        if (nope == 0)
        {
          d180 ++;
        }
      }
    }
    d270 = 0;//Check d270
    for (j = 0; j <= maior - menor; j ++)
    {
      for (i = 0; i <= maior - menor; i ++)
      {
        nope = 0;
        for (iM = menor - 1, y = 0; iM >= 0; iM --, y ++)
        {
          for (jM = 0, x = 0; jM < menor; jM ++, x ++)
          {
            if (m[j + y][i + x] != n[jM][iM])
            {
              jM = menor; iM = -1;
              nope ++;
              break;
            }
          }
        }
        if (nope == 0)
        {
          d270 ++;
        }
      }
    }
    printf("%d %d %d %d\n", d, d90, d180, d270);
  }
  return(0);
}
