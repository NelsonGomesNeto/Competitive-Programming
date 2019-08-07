#include <stdio.h>
#include <string.h>

char ainda[3]; int convert, idade = 0, fraldas = 0, resto = 0;

int check()
{
  scanf("%s", &*ainda);
  for (convert = 0; convert < 3; convert ++)
  {
    ainda[convert] = tolower(ainda[convert]);
  }
  if (strcmp(ainda,"nao") == 0 || strcmp(ainda,"não") == 0 || strcmp(ainda,"nÃo") == 0)
  {
    return(0);
  }
  else
  {
    return(1);
  }
}

int main()
{
  do
  {
    scanf("%i", &idade);
    if (idade <= 2)
    {
      fraldas += (9 * 30);
    }
    else
    {
      fraldas += (6 * 30);
    }
  } while (check() == 1);
  if (fraldas % 100 == 0)
  {
    resto = 0;
    fraldas /= 100;
  }
  else
  {
    resto = 100 - fraldas % 100;
    fraldas = (fraldas / 100) + 1;
  }
  printf("%i\n%i\n", fraldas, resto);
  return(0);
}
