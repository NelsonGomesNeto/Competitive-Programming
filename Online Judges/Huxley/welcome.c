#include <stdio.h>

int main()
{
  char nome[120];
  scanf("%[^\n]s", &*nome);
  printf("Seja muito bem-vindo %s\n", nome);
  return(0);
}
