#include <stdio.h>

int posi;

struct tree
{
  int left;
  int right;
};

int achaPai(int i, struct tree node[], int p[])
{
  int already = 0;
  if (node[i].left == -1 && node[i].right == -1)
  {
    return(1);
  }
  if (node[i].right != -1)
  {
    if (achaPai(node[i].right, node, p) == 1)
    {
      p[posi] = i; posi ++; already ++;
    }
  }
  if (node[i].left != -1)
  {
    if (achaPai(node[i].left, node, p) == 1 && already == 0)
    {
      p[posi] = i; posi ++;
    }
  }
  return(0);
}

int main()
{
  int nos; scanf("%d", &nos);
  struct tree t[nos + 1];
  int pais[nos];
  int ler;
  for (ler = 0; ler < nos; ler ++)
  {
    pais[ler] = -1;
    scanf("%d %d", &t[ler].left, &t[ler].right);
  }
  posi = 0;
  achaPai(0, t, pais);
  int o, b, aux;
  for (o = 0; o < posi; o ++)
  {
    for (b = o; b < posi; b ++)
    {
      if (pais[o] > pais[b])
      {
        aux = pais[o];
        pais[o] = pais[b];
        pais[b] = aux;
      }
    }
  }
  for (o = 0; o < posi; o ++)
  {
    printf("%d\n", pais[o]);
  }
  return(0);
}
