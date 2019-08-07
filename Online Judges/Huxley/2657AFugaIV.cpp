#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int r, n, m;
int refugees[maxN], cnt[maxN + 1];
int mat[maxN][maxN], portals[maxN*maxN][2][2], lied;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

bool go(int i = 0, int j = 0, int p = 0)
{
  if (i < 0 || j < 0 || i >= n || j >= m || mat[i][j] == 0 || p > lied) return(false);
  if (i == n - 1 && j == m - 1) return(true);
  int portal = mat[i][j];
  mat[i][j] = 0;
  for (int k = 0; k < 4; k ++)
    if (go(i + dy[k], j + dx[k], p))
      return(true);
  if (portal > 1)
  {
    if (portals[portal][0][0] == i && portals[portal][0][1] == j)
      if (go(portals[portal][1][0], portals[portal][1][1], p + 1))
        return(true);
    else
      if (go(portals[portal][0][0], portals[portal][0][1], p + 1))
        return(true);
  }
  // mat[i][j] = 1;
  return(false);
}

int main()
{
  memset(portals, -1, sizeof(portals));
  scanf("%d", &r);
  for (int i = 0; i < r; i ++)
  {
    scanf("%d", &refugees[i]);
    cnt[refugees[i]] ++;
  }

  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
    {
      scanf("%d", &mat[i][j]);
      if (mat[i][j] > 1)
      {
        if (portals[mat[i][j]][0][0] == -1)
          portals[mat[i][j]][0][0] = i, portals[mat[i][j]][0][1] = j;
        else
          portals[mat[i][j]][1][0] = i, portals[mat[i][j]][1][1] = j;
      }
    }

  bool can = false;
  for (int i = 1; i <= r; i ++)
    if (cnt[i] >= i)
      can = true, lied = r - i;

  if (!can) printf("Ja nao se pode confiar nos refens como antigamente...\n");
  else
  {
    printf("Vamos nessa, temos que sair rapido...\n");
    if (go()) printf("Tudo nosso\n");
    else printf("Continuem cavando!\n");
  }

  return(0);
}