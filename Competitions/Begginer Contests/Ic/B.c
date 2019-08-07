#include <stdio.h>
#include <stdlib.h>

int main()
{
  int test, run = 0; scanf("%d", &test);
  for (run = 1; run <= test; run ++)
  {
    getchar();
    int tam; scanf("N = %d", &tam);
    long int m[tam][tam], i, j;
    for (j = 0; j < tam; j ++)
    {
      for (i = 0; i < tam; i ++)
      {
        scanf("%ld", &m[j][i]);
      }
    }
    int iM, jM, nope = 0;
    for (i = 0, iM = tam - 1; i < tam; i ++, iM --)
    {
      for (j = 0, jM = tam - 1; j < tam; j ++, jM --)
      {
        if (m[j][i] != m[jM][iM] || m[j][i] < 0 || m[jM][iM] < 0)
        {
          nope ++;
          break;
        }
      }
    }
    if (nope == 0)
    {
      printf("Test #%d: Symmetric.\n", run);
    }
    else
    {
      printf("Test #%d: Non-symmetric.\n", run);
    }
  }
  return(0);
}
