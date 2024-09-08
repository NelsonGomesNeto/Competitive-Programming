#include <stdio.h>

int main()
{
  int voto, xAli = 0, yAlc = 0, zBra = 0, wNul = 0, Win; float aAli, bAlc, divi = 0;
  while (scanf("%i", &voto) && voto != -1)
  {
    if (voto == 83)
    {
      xAli ++; divi ++;
    }
    else if (voto == 93)
    {
      yAlc ++; divi ++;
    }
    else if (voto == 0)
    {
      zBra ++; divi ++;
    }
    else
    {
      wNul ++;
    }
  }
  if (xAli > yAlc)
  {
    Win = 83;
  }
  else { Win = 93; }
  if (xAli > 0)
  {
    aAli = (xAli * 100) / divi;
  }
  else { aAli = 0; }
  if (yAlc > 0)
  {
    bAlc = (yAlc * 100) / divi;
  }
  else { bAlc = 0; }
  printf("%i\n%i\n%i\n%i\n%i\n%.2f\n%.2f\n", xAli, yAlc, zBra, wNul, Win, aAli, bAlc);
  return(0);
}
