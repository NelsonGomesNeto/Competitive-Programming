#include <stdio.h>
#include <string.h>

char *mini(char word[99])
{
  int convert;
  for (convert = 0; convert < strlen(word); convert ++)
  {
    word[convert] = tolower(word[convert]);
  }
  return(word);
}

int main()
{
  char sair[99]; int fami, total = 0; float custo = 0;
  do
  {
    scanf("%d", &fami);
    total += (fami + 1);
    custo += ((fami + 1) * 14);
  } while (getchar() && scanf("%[^\n]", sair) && strcmp(mini(sair),"sair"));
  printf("%d\n%.2f\n", total, custo);
  return(0);
}
