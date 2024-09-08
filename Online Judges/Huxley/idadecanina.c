#include <stdio.h>
#include <string.h>

int main()
{
  int idade, convert = 0;
  char tipo[99];
  scanf("%i", &idade);
  scanf("%s", &*tipo);
  while (convert <= 99)
  {
    tipo[convert] = tolower(tipo[convert]);
    convert ++;
  }
  if (strcmp(tipo,"pequeno") == 0)
  {
    if (idade == 1)
    {
      idade = 5;
    }
    else if (idade == 3)
    {
      idade = 21;
    }
    else
    {
      idade = 26;
    }
  }
  else if (strcmp(tipo,"grande") == 0)
  {
    if (idade == 1)
    {
      idade = 8;
    }
    else if (idade == 3)
    {
      idade = 23;
    }
    else
    {
      idade = 38;
    }
  }
  else
  {
    if (idade == 1)
    {
      idade = 6;
    }
    else if (idade == 3)
    {
      idade = 19;
    }
    else
    {
      idade = 32;
    }
  }
  printf("%i\n", idade);
  return(0);
}
