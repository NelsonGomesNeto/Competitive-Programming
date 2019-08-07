#include <stdio.h>

struct tree
{
  int valor, left, right;
};

int search, sim;

int alt(int i, struct tree node[], int soma)
{
  soma += node[i].valor;
  if (soma == search && node[i].left == -1 && node[i].right == -1)
  {
    sim = 1;
  }
  if (node[i].left != -1)
  {
    alt(node[i].left, node, soma);
  }
  if (node[i].right != -1)
  {
    alt(node[i].right, node, soma);
  }
  return;
}

int main()
{
  int nos, filhos, ler; scanf("%d", &nos);
  struct tree n[nos + 30];
  int valor;
  for (ler = 0; ler < nos; ler ++)
  {
    scanf("%d", &n[ler].valor);
    scanf("%d %d", &n[ler].left, &n[ler].right);
  }
  scanf("%d", &search);
  sim = 0;
  alt(0, n, 0);
  if (sim == 1)
  {
    printf("SIM\n");
  }
  else
  {
    printf("NAO\n");
  }
  return(0);
}
