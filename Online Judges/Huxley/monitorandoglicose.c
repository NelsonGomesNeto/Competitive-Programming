#include <stdio.h>

int main()
{
  int taxaglicose = 1, media = 0, divi = 0;
  while (taxaglicose != 0)
  {
    scanf("%i", &taxaglicose);
    media += taxaglicose;
    if (taxaglicose > 0)
    {
      divi ++;
    }
  }
  if (divi > 0)
  {
    media = media / divi;
  }
  if (media < 110)
  {
    printf("Glicose Normal\n");
  }
  else if (media >= 200)
  {
    printf("Glicose Muito Alta\n");
  }
  else
  {
    printf("Glicose Alterada\n");
  }
  return(0);
}
