#include <stdio.h>
#include <string.h>

#define troca swap(&p[o].preco, &p[b].preco, &p[o].comprado, &p[b].comprado, p[o].nome, p[b].nome);

struct produtos
{
  char nome[99]; float preco; int comprado;
};

void swap (float *n, float *m, int *x, int *y, char s[], char i[])
{
  float aux; char auxC[99];
  aux = *n;
  *n = *m;
  *m = aux;

  aux = *x;
  *x = *y;
  *y = aux;

  strcpy(auxC, s);
  strcpy(s, i);
  strcpy(i, auxC);
}

int main()
{
  float dinheiros; int quantidade_produtos, ler, sold = 0;
  scanf("%f\n%d", &dinheiros, &quantidade_produtos);
  struct produtos p[quantidade_produtos];
  for (ler = 0; ler < quantidade_produtos; ler ++)
  {
    getchar();
    scanf("%s %f", p[ler].nome, &p[ler].preco);
    p[ler].comprado = 0;
  }
  int o, b;
  for (o = 0; o < quantidade_produtos; o ++)
  {
    for (b = o; b < quantidade_produtos; b ++)
    {
      if (p[o].preco > p[b].preco)
      {
        troca
      }
    }
  }
  for (ler = 0; ler < quantidade_produtos; ler ++)
  {
    if (dinheiros - p[ler].preco >= 0)
    {
      dinheiros -= p[ler].preco;
      p[ler].comprado = 1;
      sold ++;
    }
  }
  for (o = 0; o < quantidade_produtos; o ++)
  {
    for (b = o; b < quantidade_produtos; b ++)
    {
      if (p[o].comprado < p[b].comprado)
      {
        troca
      }
    }
  }
  for (o = 0; o < sold; o ++)
  {
    for (b = o; b < sold; b ++)
    {
      if (strcmp(p[o].nome, p[b].nome) > 0)
      {
        troca
      }
    }
  }
  for (ler = 0; ler < sold; ler ++)
  {
    printf("%s %.2f\n", p[ler].nome, p[ler].preco);
  }
  printf("%.2f\n", dinheiros);
  return(0);
}
