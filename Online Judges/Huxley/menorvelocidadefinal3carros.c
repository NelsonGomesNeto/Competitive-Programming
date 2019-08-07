#include <stdio.h>

int main()
{
  float V01, a1, t1, Vf1;
  float V02, a2, t2, Vf2;
  float V03, a3, t3, Vf3;
  float menorVf;
  scanf("%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f", &V01, &a1, &t1,
  &V02, &a2, &t2, &V03, &a3, &t3);
  Vf1 = V01 + (a1 * t1);
  menorVf = Vf1;
  Vf2 = V02 + (a2 * t2);
  if (Vf2 < menorVf)
  {
    menorVf = Vf2;
  }
  Vf3 = V03 + (a3 * t3);
  if (Vf3 < menorVf)
  {
    menorVf = Vf3;
  }
  menorVf *= 3.6;
  printf("%.1f\n", menorVf);
  return(0);
}
