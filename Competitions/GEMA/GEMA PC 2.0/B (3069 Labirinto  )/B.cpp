#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3, inf = 1e8; int n, m;
int di[4] = {0, 0, 1, -1}, dj[4] = {1, -1, 0, 0};
char maze[maxN][maxN + 1];
struct Edge { int i, j, c; };
vector<Edge> teleports[maxN][maxN];

struct Node
{
  int i, j, d;
  bool operator<(const Node &other) const { return d > other.d; }
  bool invalid() { return i < 0 || j < 0 || i >= n || j >= m || maze[i][j] == '#'; }
};
int dist[maxN][maxN];
int dijkstra()
{
  for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) dist[i][j] = inf;
  priority_queue<Node> pq; pq.push(Node{0, 0, dist[0][0] = 0});
  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();
    if (u.d > dist[u.i][u.j]) continue;
    for (int k = 0; k < 4; k ++)
    {
      Node v = Node{u.i + di[k], u.j + dj[k], dist[u.i][u.j] + 1};
      if (!v.invalid() && v.d < dist[v.i][v.j])
        dist[v.i][v.j] = v.d, pq.push(v);
    }
    if (maze[u.i][u.j] == 'o')
      for (Edge &e: teleports[u.i][u.j])
        if (dist[u.i][u.j] + e.c < dist[e.i][e.j])
          pq.push(Node{e.i, e.j, dist[e.i][e.j] = dist[u.i][u.j] + e.c});
  }
  return dist[n - 1][m - 1];
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++)
    {
      scanf(" %s", maze[i]);
      for (int j = 0; j < m; j ++)
        teleports[i][j].clear();
    }
    int t; scanf("%d", &t);
    for (int i = 0; i < t; i ++)
    {
      int ui, uj, vi, vj, c; scanf("%d %d %d %d %d", &ui, &uj, &vi, &vj, &c);
      ui --, uj --, vi --, vj --;
      teleports[ui][uj].push_back(Edge{vi, vj, c});
      teleports[vi][vj].push_back(Edge{ui, uj, c});
    }

    int ans = dijkstra();
    printf("%d\n", ans);
  }
  return 0;
}