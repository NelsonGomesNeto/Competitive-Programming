#include <bits/stdc++.h>

int max(int a, int b)
{
  return(a > b ? a : b);
}

void printByte(int byte)
{
  if (!byte) return;
  printByte(byte >> 1);
  printf("%d", byte & 1);
}

int binPack(int i, int n, int actualHate, int done, int hate[])
{
  if (i == n) return(0);

  //printf("%d %d ", i, hate[i] & done); printByte(done); printf("\n");
  int ans = binPack(i + 1, n, actualHate, done, hate);
  if (!(actualHate & (1 << i)) && !(done & hate[i]))
    ans = max(ans, 1 + binPack(i + 1, n, actualHate | hate[i], done | (1 << i), hate));
  return(ans);
}

int main()
{
  int n, t = 0;
  while (scanf("%d", &n) && n)
  {
    if (t ++) printf("\n");

    int hate[n];
    for (int i = 0; i < n; i ++)
    {
      int hates; hate[i] = 0;
      while (scanf("%d", &hates) && hates)
        hate[i] |= (1 << (hates - 1));
    }

    int best = binPack(0, n, 0, 0, hate);
    printf("Teste %d\n%d\n", t, best);
  }
  return(0);
}