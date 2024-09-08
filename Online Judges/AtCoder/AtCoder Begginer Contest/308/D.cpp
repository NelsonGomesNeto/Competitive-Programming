#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e2;
int n, m;
char ss[maxN + 1];
const string snuke = "snuke";
string mat[maxN];

const int di[4] = {0, 1, -1, 0};
const int dj[4] = {1, 0, 0, -1};
bool visited[maxN][maxN][5];
bool dfs(int i = 0, int j = 0, int l = 0)
{
  if (l == 5) l = 0;
  if (i < 0 || j < 0 || i >= n || j >= m || mat[i][j] != snuke[l]) return false;
  if (i == n - 1 && j == m - 1) return true;
  if (visited[i][j][l]) return false;
  visited[i][j][l] = true;

  for (int d = 0; d < 4; ++d)
    if (dfs(i + di[d], j + dj[d], l + 1))
      return true;
  return false;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      mat[i] = string(ss);
    }

    memset(visited, false, sizeof(visited));
    bool ans = dfs();
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
