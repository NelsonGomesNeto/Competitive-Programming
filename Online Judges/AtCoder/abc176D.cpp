#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3, inf = 1e9; int n, m;
struct Pos
{
  int i, j;
  void read() { scanf("%d %d", &i, &j); i--, j--; }
  bool operator==(const Pos &other) const { return i == other.i && j == other.j; }
};
int di[4] = {0, 0, 1, -1}, dj[4] = {1, -1, 0, 0};
Pos origin, destination;
char maze[maxN][maxN + 1];

struct Node
{
  Pos position; int portal;
  bool operator<(const Node &other) const { return portal > other.portal; }
};
int dist[maxN][maxN];
int dijkstra()
{
  for (int i = 0; i < n; i++)
    fill(dist[i], dist[i]+m, inf);
  priority_queue<Node> pq; pq.push(Node{origin, 0});
  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();
    if (u.position == destination)
      return u.portal;
    if (dist[u.position.i][u.position.j] < u.portal)
      continue;

    for (int k = 0; k < 4; k++)
    {
      int ni = u.position.i + di[k], nj = u.position.j + dj[k];
      if (ni < 0 || nj < 0 || ni >= n || nj >= m || maze[ni][nj] == '#') continue;
      if (u.portal < dist[ni][nj])
        pq.push(Node{Pos{ni, nj}, dist[ni][nj] = u.portal});
    }
    for (int i = -2; i <= 2; i++)
      for (int j = -2; j <= 2; j++)
      {
        int ni = u.position.i + i, nj = u.position.j + j;
        if (ni < 0 || nj < 0 || ni >= n || nj >= m || maze[ni][nj] == '#') continue;
        if (u.portal + 1 < dist[ni][nj])
          pq.push(Node{Pos{ni, nj}, dist[ni][nj] = u.portal + 1});
      }
  }
  return -1;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    origin.read();
    destination.read();
    for (int i = 0; i < n; i++) scanf(" %s", maze[i]);

    int ans = dijkstra();
    printf("%d\n", ans);
  }
  return 0;
}