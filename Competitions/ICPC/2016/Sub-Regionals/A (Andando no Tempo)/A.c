#include <stdio.h>

int main()
{
  int creditos[3];
  scanf("%d %d %d", &creditos[0], &creditos[1], &creditos[2]);
  int i, j, k, atual, possivel = 0;
  for (i = 0; i < 3; i ++)
  {
    atual = 0;
    for (j = i, k = 0; k < 3; j ++, k ++)
    {
      j %= 3;
      if (creditos[j] == atual)
        possivel = 1;

      atual += creditos[j];
    }
  }
  
  if (possivel)
    printf("S\n");
  else
    printf("N\n");
  return(0);
}
