#include <stdio.h>

struct tree
{
  int left, right;
};

int max(int a, int b)
{
  return(a > b ? a : b);
}

int alt(int i, struct tree node[])
{
  int alt_left = 0;
  int alt_right = 0;
  if (node[i].left != -1)
  {
    alt_left = alt(node[i].left, node);
  }
  if (node[i].right != -1)
  {
    alt_right = alt(node[i].right, node);
  }
  return(1 + max(alt_left, alt_right));
}

int main()
{
  int nos, filhos, raiz, ler; scanf("%d %d %d", &nos, &filhos, &raiz);
  struct tree n[nos];
  for (ler = 0; ler < nos; ler ++)
  {
    n[ler].left = -1;
    n[ler].right = -1;
  }
  int noAtual;
  for (ler = 0; ler < filhos; ler ++)
  {
    scanf("%d", &noAtual);
    scanf("%d %d", &n[noAtual].left, &n[noAtual].right);
  }
  int H = alt(raiz, n);
  printf("%d\n", H);
  return(0);
}
