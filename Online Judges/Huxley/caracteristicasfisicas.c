#include <stdio.h>

int main()
{
  int idade, pessoa = 0, velho = 0; float mulher = 0; char sexo, olhos, cabelo;
  while (scanf("%d", &idade) && idade != -1)
  {
    pessoa ++;
    getchar();
    scanf("%c %c %c", &sexo, &cabelo, &olhos);
    if (sexo == 'f' && olhos == 'v' && cabelo == 'l' && idade >= 18 && idade <= 35)
    {
      mulher ++;
    }
    if (idade > velho)
    {
      velho = idade;
    }
  }
  mulher /= (float) pessoa;
  printf("Mais velho: %d\n", velho);
  printf("Mulheres com olhos verdes, loiras com 18 a 35 anos: %.2f%%\n", mulher * 100);
  return(0);
}
