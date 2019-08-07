#include <stdio.h>
#include <string.h>

int mergulhos = 0;

void convert(char palavra[999])
{
  int low;
  for (low = 0; low < strlen(palavra); low ++)
  {
    palavra[low] = tolower(palavra[low]);
  }
}

int check(char existe[999])
{
  convert(&*existe);
  if (strcmp(existe,"mergulho") != 0 && strcmp(existe,"barco") != 0 && strcmp(existe,"buggy") != 0)
  {
    return(1);
  }
  else { return(0); }
}

float preco(char tipo[999])
{
  float custo;
  if (strcmp(tipo,"mergulho") == 0)
  { custo = 50; mergulhos ++; }
  else if (strcmp(tipo,"barco") == 0)
  { custo = 65; }
  else { custo = 90; }
  return(custo);
}

int main()
{
  char passeio[999]; char joao[999];
  float total = 0;
  while (scanf("%[^\n]", passeio) && check(passeio) == 0)
  {
    getchar();
    scanf("%[^\n]", joao); convert(joao);
    if (strcmp(joao,"sim") == 0)
    {
      total += preco(passeio) * 0.6;
    }
    else
    {
      total += preco(passeio);
    }
    getchar();
  }
  printf("%d\n%.2f\n", mergulhos, total);
  return(0);
}
