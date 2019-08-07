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
      raio += 1e-9;
      distancia = (((Cx - x) * (Cx - x)) + ((Cy - y) * (Cy - y)));
      if (distancia <= raio * raio)
      {
        circ ++;
      }
    }
    else
    {

      scanf("%Lf%Lf%Lf%Lf", &xmin, &ymin, &xmax, &ymax);
      if (x >= xmin - 1e-9 && x <= xmax + 1e-9 && y >= ymin - 1e-9 && y <= ymax + 1e-9)
      {
        retan ++;
      }
    }
    vezes --;
  }
  printf("Retangulos: %d\nCirculos: %d\n", retan, circ);
  return(0);
}
/*2 2
6
circulo
0 0 2.82
circulo
0 0 2.83
retangulo
0 0 1 1
retangulo
0 0 1.99999999 1.99999999
retangulo
0 0 3 3*/
