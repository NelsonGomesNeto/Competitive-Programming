#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Pos
{
  int i, j;
  void read() { scanf("%d %d", &i, &j); i--, j--; }
  bool operator==(const Pos &other) const { return i == other.i && j == other.j; }
};

int n, m, k;
Pos origin, destination;
vector<vector<char>> mat;

int manhattan(Pos &pos)
{
  return abs(destination.i - pos.i) + abs(destination.j - pos.j);
}
int euclid(Pos &pos)
{
  int dx = destination.i - pos.i, dy = destination.j - pos.j;
  return sqrt(dx*dx + dy*dy);
}

struct Node
{
  lli dist, hdist; Pos pos; int dir, combo;
  bool operator<(const Node &other) const { return dist > other.dist; }
  // bool operator<(const Node &other) const { return dist > other.dist || (dist == other.dist && hdist > other.hdist); }
  void print() { printf("\t%lld (%d, %d) %d %d\n", dist, pos.i, pos.j, dir, combo); }
};
int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};
vector<vector<vector<lli>>> dist;
int dijkstra()
{
  priority_queue<Node> pq;
  pq.push(Node{0, 0, origin, 4, 1});
  dist[origin.i][origin.j][4] = 0;
  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();
    DEBUG u.print();
    if (u.dist > dist[u.pos.i][u.pos.j][u.dir])
      continue;

    // rotate
    for (int dir = 0; dir < 4; dir++)
    {
      lli newDist = (u.dist / k + (u.dist % k != 0)) * k;
      if (newDist < dist[u.pos.i][u.pos.j][dir])
        pq.push(Node{dist[u.pos.i][u.pos.j][dir] = newDist, newDist, u.pos, dir, u.combo});
    }
    // move
    if (u.dir != 4)
    {
      Pos newPos = {u.pos.i + di[u.dir], u.pos.j + dj[u.dir]};
      if (newPos.i < 0 || newPos.i >= n || newPos.j < 0 || newPos.j >= m || mat[newPos.i][newPos.j] == '@') continue;
      lli newDist = u.dist + 1;
      if (newDist < dist[newPos.i][newPos.j][u.dir])
        pq.push(Node{dist[newPos.i][newPos.j][u.dir] = newDist, newDist, newPos, u.dir, u.combo});
    }
  }
  lli ans = 1e18;
  for (int i = 0; i < 5; i++)
    ans = min(ans, dist[destination.i][destination.j][i]);
  return ans == 1e18 ? -1 : ans / k + (ans % k != 0);
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    mat.clear();
    mat.resize(n, vector<char>(m));
    dist.clear();
    dist.resize(n, vector<vector<lli>>(m));
    origin.read(); destination.read();

    char line[m + 1];
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", line);
      for (int j = 0; j < m; j++)
      {
        mat[i][j] = line[j];
        dist[i][j].resize(5, 1e18);
      }
    }

    int ans = dijkstra();
    printf("%d\n", ans);
  }
  return 0;
}
