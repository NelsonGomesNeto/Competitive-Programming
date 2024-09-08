#include <stdio.h>

struct tree
{
  int left;
  int right;
};

void achaPai(int i, struct tree node[], int p, int *ePai)
{
  if (node[i].left == -1 && node[i].right == -1 && p == 1)
  {
    (*ePai) ++;
    return;
  }
  if (node[i].left != -1)
  {
    achaPai(node[i].left, node, p + 1, &*ePai);
  }
  if (node[i].right != -1)
  {
    achaPai(node[i].right, node, p + 1, &*ePai);
  }
  return;
}

int main()
{
  int nos; scanf("%d", &nos);
  struct tree t[nos + 1];
  int ler;
  for (ler = 0; ler < nos; ler ++)
  {
    scanf("%d %d", &t[ler].left, &t[ler].right);
  }
  int isIt, pai;
  for (pai = 0; pai < nos; pai ++)
  {
    isIt = 0;
    achaPai(pai, t, 0, &isIt);
    if (isIt > 0)
    {
      printf("%d\n", pai);
    }
  }
  return(0);
}
