#include <stdio.h>
#include <math.h>

void printFormated(float num)
{
  if ((int) round(num * 100) % 10 == 0)
    printf("%.1f\n", num);
  else
    printf("%.2f\n", num);
}

int main()
{
  char forma; scanf("%c", &forma);

  if (forma == 'Q')
  {
    float tamanho; scanf("%f", &tamanho);
    printFormated(tamanho * tamanho); // Área
    printFormated(tamanho * 4); // Perímetro
  }
  else if (forma == 'R')
  {
    float altura, largura; scanf("%f\n%f", &altura, &largura);
    printFormated(altura * largura); // Área
    printFormated((altura * 2) + (largura * 2)); // Perímetro
  }
  else if (forma == 'C')
  {
    float raio; scanf("%f", &raio);
    printFormated(3.14 * raio * raio); // Área
    printFormated(2 * 3.14 * raio); // Comprimento
  }
  else
    printf("Nenhuma figura selecionada\n");

  return(0);
}
