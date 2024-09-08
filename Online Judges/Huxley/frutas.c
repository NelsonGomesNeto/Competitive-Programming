#include <stdio.h>
#include <string.h>

int main()
{
  int testes, check, dias, peso; scanf("%d", &testes);
  float preco, mediaPreco = 0, mediaPeso = 0;
  for (dias = 1; dias <= testes; dias ++)
  {
    char frutas[999];
    scanf("%f", &preco);
    mediaPreco += preco;
    getchar();
    scanf("%[^\n]", frutas);
    peso = 1;
    for (check = 0; check < strlen(frutas); check ++)
    {
      if (frutas[check] == ' ')
      peso ++;
    }
    mediaPeso += peso;
    printf("dia %d: %d kg\n", dias, peso);
  }
  mediaPeso /= testes; mediaPreco /= testes;
  printf("%.2f kg por dia\n", mediaPeso);
  printf("R$ %.2f por dia\n", mediaPreco);
  return(0);
}
