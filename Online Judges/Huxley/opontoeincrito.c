#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
  long double x, y, aux; int circ = 0, retan = 0, repeat; scanf("%Lf%Lf", &x, &y);
  long double xmin, ymin, xmax, ymax;
  long double Cx, Cy, raio, distancia;
  int vezes; scanf("%d", &vezes);
  while (vezes > 0)
  {
    char tipo[20];
    getchar();
    scanf("%[^\n]", tipo);
    for (repeat = 0; repeat < strlen(tipo); repeat ++)
    {
      tipo[repeat] = tolower(tipo[repeat]);
    }
    if (strcmp(tipo,"circulo") == 0)
    {

      scanf("%Lf%Lf%Lf", &Cx, &Cy, &raio);
      if (raio < 0)
      {
        raio *= -1;
      }
      distancia = (((Cx - x) * (Cx - x)) + ((Cy - y) * (Cy - y)));
      if (distancia * distancia <= raio + 0.0000005)
      {
        circ ++;
      }
    }
    else
    {

      scanf("%Lf%Lf%Lf%Lf", &xmin, &ymin, &xmax, &ymax);
      if (x >= xmin - 0.0000005 && x <= xmax + 0.0000005 && y >= ymin - 0.0000005 && y <= ymax + 0.0000005)
      {
        retan ++;
      }
    }
    vezes --;
  }
  printf("Retangulos: %d\nCirculos: %d\n", retan, circ);
  return(0);
}
