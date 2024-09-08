#include <stdio.h>
#include <math.h>
#define esquerda (t[i] * findP1(t, i * 2, end))
#define direita (t[i] * findP1(t, (i * 2) + 1, end))

int max(int a, int b)
{
  return(a > b ? a : b);
}

int findP1(int t[], int i, int end)
{
  if (i * 2 >= end)
  {
    return(t[i]);
  }
  return(max(esquerda, direita));
}

int main()
{
  int tam; scanf("%d", &tam);
  int endOfTree = pow(2, tam);
  int tree[endOfTree], valor, i;
  for (i = 0; i < endOfTree; i ++)
  {
    tree[i] = 0;
  } i = 1;
  while (scanf("%d", &valor) != EOF)
  {
    tree[i] = valor;
    i ++;
  }
  int P1 = findP1(tree, 1, endOfTree);
  printf("%d\n", P1);
  return(0);
}
