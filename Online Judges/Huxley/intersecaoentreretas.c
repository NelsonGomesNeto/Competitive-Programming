#include <stdio.h>

int main()
{
  int x1, y1, x2, y2;
  double A, B, C, D, E, F, y, x, aux;
  while (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != EOF)
  {
    A = (y2 - y1) * (-1);
    B = (x2 - x1);
    C = ((x1 * A) + (y1 * B)) * (-1);
    if (B != 0)
    {
      A /= B; C /= B; B /= B;
    }
    else
    {
      C /= A; A /= A;
    }
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    D = (y2 - y1) * (-1);
    E = (x2 - x1);
    F = ((x1 * D) + (y1 * E)) * (-1);
    if (E != 0)
    {
      D /= E; F /= E; E /= E;
    }
    else
    {
      F /= D; D /= D;
    }
    aux = A;
    A *= (D * (-1)); B *= (D * (-1)); C *= (D * (-1));
    D *= aux; E *= aux; F *= aux;
    if (B + E != 0 && A != 0)
    {
      y = (C + F) / (B + E);
      x = (C - (B * y)) / A;
      y *= -1; x *= -1;
      printf("%.2lf %.2lf\n", x, y);
    }
    else
    {
      printf("NUNCA\n");
    }
  }
  return(0);
}
