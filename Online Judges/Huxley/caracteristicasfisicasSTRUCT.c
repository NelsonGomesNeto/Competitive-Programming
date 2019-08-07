#include <stdio.h>

struct existencia
{
  int idade;
  char sexo, olhos, cabelo;
};

int main()
{
  struct existencia p;
  int pessoa = 0, velho = 0; float mulher = 0;
  while (scanf("%d", &p.idade) && p.idade != -1)
  {
    pessoa ++;
    getchar();
    scanf("%c %c %c", &p.sexo, &p.cabelo, &p.olhos);
    if (p.sexo == 'f' && p.olhos == 'v' && p.cabelo == 'l' && p.idade >= 18 && p.idade <= 35)
    {
      mulher ++;
    }
    if (p.idade > velho)
    {
      velho = p.idade;
    }
  }
  mulher /= (float) pessoa;
  printf("Mais velho: %d\n", velho);
  printf("Mulheres com olhos verdes, loiras com 18 a 35 anos: %.2f%%\n", mulher * 100);
  return(0);
}
