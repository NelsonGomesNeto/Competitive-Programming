#include <stdio.h>

int main()
{
  int user, repeat; scanf("%d", &user);
  int idade[user], amigos[user], fotos[user];
  char nome[user][99], sexo[user], estado[user];
  for (repeat = 0; repeat < user; repeat ++)
  {
    scanf("%d", &idade[repeat]);
    getchar(); scanf("%[^\n]", nome[repeat]);
    getchar(); scanf("%c\n%c", &sexo[repeat], &estado[repeat]);
    scanf("%d\n%d", &amigos[repeat], &fotos[repeat]);
  }
  for (repeat = 0; repeat < user; repeat ++)
  {
    printf("Idade: %d\n", idade[repeat]);
    printf("Nome: %s\n", nome[repeat]);
    printf("Sexo: %c\n", sexo[repeat]);
    printf("Estado Civil: %c\n", estado[repeat]);
    printf("Numero de amigos: %d\n", amigos[repeat]);
    printf("Numero de fotos: %d\n", fotos[repeat]);
    printf("\n");
  }
  return(0);
}
/*
Idade: 20
Nome: Caio
Sexo: M
Estado Civil: S
Numero de amigos: 150
Numero de fotos: 300
*/
