#include <stdio.h>

int main()
{
  int enemies, printar; scanf("%d", &enemies);
  char nome[99]; int ID, level, vida, atk, def;
  for (printar = 0; printar < enemies; printar ++)
  {
    getchar();
    scanf("%[^\n]", nome);
    scanf("%d\n%d\n%d\n%d\n%d", &ID, &level, &vida, &atk, &def);
    printf("Nome: %s\n", nome);
    printf("ID: %d\n", ID);
    printf("Level: %d\n", level);
    printf("Vida: %d\n", vida);
    printf("Ataque: %d\n", atk);
    printf("Defesa: %d\n", def);
  }
  return(0);
}
