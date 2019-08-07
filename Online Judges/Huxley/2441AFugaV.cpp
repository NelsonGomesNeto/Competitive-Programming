#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100, inf = 1e7; int n, m;
int mat[maxN][maxN], visited[maxN][maxN];
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

int go(int i = 0, int j = 0, int prv = -1)
{
  if (i < 0 || j < 0 || i >= n || j >= m || mat[i][j] == 0) return(inf);
  if (i == n - 1 && j == m - 1) return(0);
  mat[i][j] = 0;
  int ans = inf;
  for (int k = 0; k < 4; k ++)
    ans = min(ans, go(i + dy[k], j + dx[k], k) + (prv == -1 ? 0 : ((prv == 0 || prv == 2) && (k == 1 || k == 3)) || ((prv == 1 || prv == 3) && (k == 0 || k == 2))));
  mat[i][j] = 1;
  return(ans);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      scanf("%d", &mat[i][j]);

  int ans = go();
  if (ans >= inf) printf("Continuem cavando!\n");
  else printf("O caminho tem complexidade: %d\n", ans);

  return(0);
}