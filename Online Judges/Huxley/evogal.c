#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isVogal(char l)
{
  l = tolower(l);
  return(l == 'a' || l == 'e' || l == 'i' || l == 'o' || l == 'u');
}

int main()
{
  char letra[100]; scanf("%s", letra);

  if (strlen(letra) == 1)
    if (isVogal(letra[0]))
      printf("Eh vogal\n");
    else
      printf("Nao eh vogal\n");
  else
    printf("1 caractere, por favor!\n");

  return(0);
}
