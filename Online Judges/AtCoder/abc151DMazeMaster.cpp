#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 20; int n, m;
bool visited[maxN][maxN];
char maze[maxN][maxN + 1];

int di[4] = {0, 0, 1, -1}, dj[4] = {1, -1, 0, 0};
struct Node
{
  int i, j, d;
};
int mostDistant(int si, int sj)
{
  memset(visited, false, sizeof(visited));
  queue<Node> q; q.push({si, sj, 0});
  int md = 0;
  while (!q.empty())
  {
    Node u = q.front(); q.pop();
    if (u.i < 0 || u.j < 0 || u.i >= n || u.j >= m || visited[u.i][u.j] || maze[u.i][u.j] == '#') continue;
    visited[u.i][u.j] = true, md = max(md, u.d);
    for (int k = 0; k < 4; k ++)
      q.push({u.i + di[k], u.j + dj[k], u.d + 1});
  }
  return md;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf(" %s", maze[i]);

    int ans = 0;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        ans = max(ans, mostDistant(i, j));
    printf("%d\n", ans);
  }
  return 0;
}