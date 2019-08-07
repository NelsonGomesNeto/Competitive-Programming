#include <stdio.h>

int tempoAlcance(float pA, float tA, float pB, float tB, float *temp)
{
  if (pA < pB && tA <= tB)
  {
    *temp = -1;
    return(-1);
  }
  else if (pA < pB)
  {
    pA += pA * (tA /100);
    pB += pB * (tB / 100);
    *temp += 1;
    //printf("%.0f~~%.0f~~%f\n", pA, pB, *temp);
    tempoAlcance(pA, tA, pB, tB, &*temp);
  }
}

int main()
{
  float habA, taxA, habB, taxB, tempo = 0;
  while (scanf("%f %f %f %f", &habA, &taxA, &habB, &taxB) != EOF)
  {
    tempo = 0;
    tempoAlcance(habA, taxA, habB, taxB, &tempo);
    if (tempo == -1)
    {
      printf("A população do país A jamais alcançará a população do país B\n");
    }
    else
    {
      printf("A população do país A alcançará a população do país B em %.0f anos\n", tempo);
    }
  }
  return(0);
}
