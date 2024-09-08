#include <stdio.h>
#include <math.h>

int main()
{
  int diametro;
  int altura, largura, profundidade;
  scanf("%i", &diametro);
  scanf("%i %i %i", &altura, &largura, &profundidade);

  if (diametro > altura || diametro > largura || diametro > profundidade)
  {
    printf("N\n");
  }
  else
  {
    printf("S\n");
  }
  return(0);
}
//Pi = atan(1)*4 or M_PI (If you use math.h)
//raio = diametro / 2;
/*volumeBola = 4 * M_PI * pow(raio, 3);
volumeCaixa = altura * largura * profundidade;*/
