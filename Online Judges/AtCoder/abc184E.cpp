#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3, inf = 1e7; int n, m;
char mat[maxN][maxN + 1];

struct Pos
{
  int i, j;
  bool valid()
  {
    return i >= 0 && j >= 0 && i < n && j < m && mat[i][j] != '#';
  }
  bool operator<(const Pos &other) const { return i < other.i || (i == other.i && j < other.j); }
};
set<Pos> teleporters[256];
Pos origin, destination;

struct Node
{
  Pos pos; int d;
  bool operator<(const Node &other) const { return d > other.d; }
};
int dist[maxN][maxN];
int di[4] = {0, 0, -1, 1}, dj[4] = {1, -1, 0, 0};
int dijkstra()
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      dist[i][j] = inf;

  priority_queue<Node> pq;
  pq.push(Node{origin, dist[origin.i][origin.j] = 0});
  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();

    if (u.d > dist[u.pos.i][u.pos.j]) continue;
    auto it = teleporters[mat[u.pos.i][u.pos.j]].find(u.pos);
    if (it != teleporters[mat[u.pos.i][u.pos.j]].end())
      teleporters[mat[u.pos.i][u.pos.j]].erase(it);

    for (int k = 0; k < 4; k++)
    {
      Pos newPos = Pos{u.pos.i + di[k], u.pos.j + dj[k]};
      if (newPos.valid() && u.d + 1 < dist[newPos.i][newPos.j])
        pq.push(Node{newPos, dist[newPos.i][newPos.j] = u.d + 1});
    }

    list<Pos> toRem;
    for (Pos p: teleporters[mat[u.pos.i][u.pos.j]])
      if (u.d + 1 < dist[p.i][p.j])
        pq.push(Node{p, dist[p.i][p.j] = u.d + 1});
      else
        toRem.push_back(p);
    for (Pos p: toRem)
      teleporters[mat[u.pos.i][u.pos.j]].erase(p);
  }
  return dist[destination.i][destination.j];
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 'a'; i <= 'z'; i++)
      teleporters[i].clear();
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", mat[i]);
      for (int j = 0; j < m; j++)
      {
        if (mat[i][j] >= 'a' && mat[i][j] <= 'z')
          teleporters[mat[i][j]].insert(Pos{i, j});
        if (mat[i][j] == 'S')
          origin = Pos{i, j};
        if (mat[i][j] == 'G')
          destination = Pos{i, j};
      }
    }

    int ans = dijkstra();
    if (ans >= inf) ans = -1;
    printf("%d\n", ans);
  }
  return 0;
}