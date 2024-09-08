#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
  int quanti; scanf("%d", &quanti);
  char string[9999]; int ler, i, j = 0, posi, check = 1, ya = 0; double mat = 0;
  for (ler = 0; ler < quanti; ler ++)
  {
    getchar(); scanf("%[^\n]", string);
    mat = strlen(string);
    //printf("%d\n", (int) mat);
    for (check = 1, ya = 0; check <= mat; check ++)
    {
      if (check * check == mat)
      {
        mat = check;
        ya = 1;
        break;
      }
    }
    if (ya == 0)
    {
      printf("INVALIDO\n");
    }
    else
    {
      char fim[(int) mat][(int) mat]; j = 0;
      for (i = 0; i < strlen(string); i ++)
      {
        posi = i;
        if (posi >= mat)
        {
          posi %= (int)mat;
        }
        fim[j][posi] = string[i];
        if (posi == mat - 1)
        {
          j ++;
        }
        //printf("%c~%d#", fim[j][posi], j);
      }
      //printf("~~~~~~%d\n", (int) mat);
      for (i = 0; i < mat; i ++)
      {
        for (j = 0; j < mat; j ++)
        {
          printf("%c", fim[j][i]);
        }
      }
      printf("\n");
    }
  }
  return(0);
}
