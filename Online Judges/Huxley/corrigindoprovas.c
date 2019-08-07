#include <stdio.h>

int main()
{
  int provas[5], ler, media = 0, hora, min, seg = 0;
  for (ler = 0; ler < 5; ler ++)
  {
    scanf("%d", &provas[ler]);
    media += provas[ler];
  }
  media /= 5;
  seg = media * 100;
  if (seg >= 60)
  {
    min = seg / 60;
    seg %= 60;
  }
  if (min >= 60)
  {
    hora = min / 60;
    min %= 60;
  }
  printf("%d\n%d\n%d\n%d\n", media, hora, min, seg);
  return(0);
}
