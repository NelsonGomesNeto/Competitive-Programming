#include <bits/stdc++.h>
int matriz[100][100];

void build(int t, int b)
{
  if (t > b) return;
  matriz[t][t] = 1;
  matriz[t][b] = 2;
  matriz[b][b] = 1;
  matriz[b][t] = 2;
  for (int i = t + 1; i < b; i ++)
  {
    matriz[i][t] = 3;
    matriz[i][b] = 3;
    matriz[t][i] = 3;
    matriz[b][i] = 3;
  }
  build(t + 1, b - 1);
}

int main()
{
  int size;
  while (scanf("%d", &size) != EOF)
  {
    build(0, size - 1);
    for (int i = 0; i < size; i ++)
      for (int j = 0; j < size; j ++)
        printf("%d%s", matriz[i][j], j < size - 1 ? "\0" : "\n");
  }
  return(0);
}