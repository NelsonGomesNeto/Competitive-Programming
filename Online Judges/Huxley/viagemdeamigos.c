#include <stdio.h>
#include <string.h>

int main()
{
  int pessoas, quartos, convert = 0;
  char local[99];
  float preco = 0, precoindi;
  scanf("%i", &pessoas);
  scanf("%s", &*local);
  scanf("%i", &quartos);
  while (convert <= 99)
  {
    local[convert] = tolower(local[convert]);
    convert ++;
  }
  if (strcmp(local,"pipa") == 0)
  {
    if (quartos == 2)
    {
      preco = 600 + (75 * pessoas);
    }
    else
    {
      preco = 900 + (75 * pessoas);
    }
  }
  else
  {
    if (quartos == 3)
    {
      preco += 950 + (60 * pessoas);
    }
    else
    {
      preco += 1120 + (60 * pessoas);
    }
  }
  precoindi = preco / pessoas;
  printf("%.2f\n%.2f\n", preco, precoindi);
}
