#include <stdio.h>

struct tree
{
  int valor, left, right;
};

int max(int a, int b)
{
  return(a > b ? a : b);
}

int maior[30], menor[30];

int alt(int i, struct tree node[], int nivel)
{
  if (node[i].valor > maior[nivel])
  {
    maior[nivel] = node[i].valor;
  }
  if (node[i].valor < menor[nivel])
  {
    menor[nivel] = node[i].valor;
  }
  if (node[i].left != -1)
  {
    alt(node[i].left, node, nivel + 1);
  }
  if (node[i].right != -1)
  {
    alt(node[i].right, node, nivel + 1);
  }
  return;
}

int main()
{
  int nos, filhos, ler; scanf("%d", &nos);
  struct tree n[nos + 30];
  int valor;
  for (ler = 0; ler < 30; ler ++)
  {
    maior[ler] = -999999;
    menor[ler] = 999999;
  }
  for (ler = 0; ler < nos; ler ++)
  {
    scanf("%d", &n[ler].valor);
    scanf("%d %d", &n[ler].left, &n[ler].right);
  }
  alt(0, n, 1);
  int i, nivel = 1;
  for (i = 0; i < 30; i ++)
  {
    if (maior[i] != -999999 && menor[i] != 999999)
    {
      printf("Nivel %d: Maior = %d, Menor = %d\n", nivel, maior[i], menor[i]);
      nivel ++;
    }
  }
  return(0);
}
