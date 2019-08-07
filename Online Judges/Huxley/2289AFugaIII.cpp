#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int r, n, m;
int refugees[maxN], cnt[maxN + 1];
int mat[maxN][maxN], path[maxN*maxN], pathSize;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char dirName[4][10] = {"Sul", "Leste", "Norte", "Oeste"};

bool go(int i = 0, int j = 0, int p = 0)
{
  if (i < 0 || j < 0 || i >= n || j >= m || mat[i][j] == 0) return(false);
  if (i == n - 1 && j == m - 1)
  {
    pathSize = p;
    return(true);
  }
  mat[i][j] = 0;
  for (int k = 0; k < 4; k ++)
    if (go(i + dy[k], j + dx[k], p + 1))
    {
      path[p] = k;
      return(true);
    }
  // mat[i][j] = 1;
  return(false);
}

void printPath()
{
  for (int i = 0; i < pathSize; i ++)
    printf("%s%s", dirName[path[i]], i < pathSize - 1 ? ", " : "\n");
}

int main()
{
  scanf("%d", &r);
  for (int i = 0; i < r; i ++)
  {
    scanf("%d", &refugees[i]);
    cnt[refugees[i]] ++;
  }

  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      scanf("%d", &mat[i][j]);

  bool can = false;
  for (int i = 1; i <= r; i ++)
    if (cnt[i] >= i)
      can = true;

  if (!can) printf("Ja nao se pode confiar nos refens como antigamente...\n");
  else
  {
    printf("Vamos nessa, temos que sair rapido...\n");
    if (go()) printPath();
    else printf("Continuem cavando!\n");
  }

  return(0);
}