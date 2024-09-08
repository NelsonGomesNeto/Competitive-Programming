#include <stdio.h>
#include <string.h>

int main()
{
  char nome[999], senha[999]; int run = 0;
  printf("Digite seu nome de usuario:\n");
  while (scanf("%[^\n]", nome) != EOF)
  {
    if (run > 0)
    {
      printf("Digite seu nome de usuario:\n");
    }
    getchar();
    printf("Digite sua senha:\n");
    scanf("%[^\n]", senha);
    if (strcmp(nome, senha) == 0)
    {
      printf("Erro! Senha igual a nome do usuario!\n");
    }
    getchar();
    run ++;
  }
  return(0);
}
