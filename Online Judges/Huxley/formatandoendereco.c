#include <stdio.h>

int main()
{
  int num, cep;
  char rua[99], bairro[99], cidade[99], estado[99];
  scanf("%[^\n]", rua);
  scanf("%d", &num);
  getchar();
  scanf("%[^\n]", bairro);
  getchar();
  scanf("%[^\n]", cidade);
  getchar();
  scanf("%[^\n]", estado);
  scanf("%d", &cep);
  printf("%s, %d.\n", rua, num);
  printf("Bairro: %s. Cep: %d\n", bairro, cep);
  printf("%s/%s\n", cidade, estado);
  return(0);
}
