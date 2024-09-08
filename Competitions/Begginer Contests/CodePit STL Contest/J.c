#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  char move[999]; int run = 1;
  while (scanf("%[^\n]", move) != EOF)
  {
    int m[3][3], exe, j, i;
    for (j = 0; j < 3; j ++)
    {
      for (i = 0; i < 3; i ++)
      {
        m[j][i] = 0;
      }
    }
    for (exe = 0; exe < strlen(move); exe ++)
    {
      if (move[exe] == 'a')
      {
        m[0][0] ++; m[0][1] ++;
        m[1][0] ++;
      }
      else if (move[exe] == 'b')
      {
        m[0][0] ++; m[0][1] ++; m[0][2] ++;
                    m[1][1] ++;
      }
      else if (move[exe] == 'c')
      {
        m[0][1] ++; m[0][2] ++;
                    m[1][2] ++;
      }
      else if (move[exe] == 'd')
      {
        m[0][0] ++;
        m[1][0] ++; m[1][1] ++;
        m[2][0] ++;
      }
      else if (move[exe] == 'e')
      {
                    m[0][1] ++;
        m[1][0] ++; m[1][1] ++; m[1][2] ++;
                    m[2][1] ++;
      }
      else if (move[exe] == 'f')
      {
                    m[0][2] ++;
        m[1][1] ++; m[1][2] ++;
                    m[2][2] ++;
      }
      else if (move[exe] == 'g')
      {
        m[1][0] ++;
        m[2][0] ++; m[2][1] ++;
      }
      else if (move[exe] == 'h')
      {
                    m[1][1] ++;
        m[2][0] ++; m[2][1] ++; m[2][2] ++;
      }
      else if (move[exe] == 'i')
      {
                    m[1][2] ++;
        m[2][1] ++; m[2][2] ++;
      }
      for (j = 0; j < 3; j ++)
      {
        for (i = 0; i < 3; i ++)
        {
          if (m[j][i] == 10)
          {
            m[j][i] = 0;
          }
        }
      }
    }
    printf("Case #%d:\n", run);
    for (j = 0; j < 3; j ++)
    {
      for (i = 0; i < 2; i ++)
      {
        if (m[j][i] > 9)
        {
          m[j][i] = 9;
        }
        printf("%d ", m[j][i]);
      }
      if (m[j][i] > 9)
      {
        m[j][i] = 9;
      }
      printf("%d\n", m[j][i]);
    }
    for (i = 0; i < 300; i ++)
    {
      move[i] = '\0';
    }
    run ++;
    getchar();
  }
  return(0);
}
