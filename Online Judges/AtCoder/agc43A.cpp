#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 102, inf = 1e6; int n, m;
char mat[maxN][maxN + 1];

int di[2] = {1, 0}, dj[2] = {0, 1};
struct Node
{
  int i, j, d;
  bool operator<(const Node &other) const { return d > other.d; };
};
int dist[maxN][maxN];
int dijkstra()
{
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) dist[i][j] = inf;
  priority_queue<Node> pq;
  pq.push(Node{0, 0, dist[0][0] = mat[0][0] == '#'});
  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();
    if (u.d > dist[u.i][u.j]) continue;
    for (int k = 0; k < 2; k++)
    {
      int ni = u.i + di[k], nj = u.j + dj[k];
      if (ni >= n || nj >= m) continue;
      if (dist[u.i][u.j] + (mat[ni][nj] == '#') < dist[ni][nj])
        pq.push(Node{ni, nj, dist[ni][nj] = dist[u.i][u.j] + (mat[ni][nj] == '#')});
    }
  }
  return dist[n - 1][m - 1];
}

int memo[maxN][maxN][2];
int solve(int i = 0, int j = 0, char wasInside = false)
{
  if (i >= n || j >= m) return inf;
  if (i == n - 1 && j == m - 1) return wasInside || (mat[i][j] == '#' && !wasInside);
  if (memo[i][j][wasInside] != -1) return memo[i][j][wasInside];
  
  int ans = min(solve(i + 1, j, mat[i][j] == '#'), solve(i, j + 1, mat[i][j] == '#'));
  ans += wasInside && mat[i][j] == '.';

  return memo[i][j][wasInside] = ans;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf(" %s", mat[i]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    DEBUG printf("%d - ", dijkstra());
    printf("%d\n", ans);
  }
  return 0;
}