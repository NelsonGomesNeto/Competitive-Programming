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

int manhattan(Pos pos)
{
  return abs(destination.i - pos.i) + abs(destination.j - pos.j);
}

struct Node
{
  int dist, hdist; Pos pos; int prvDir, combo;
  bool operator<(const Node &other) const { return hdist > other.hdist; }
  // bool operator<(const Node &other) const { return dist > other.dist; }
  void print() { printf("\t%d (%d, %d) %d %d\n", dist, pos.i, pos.j, prvDir, combo); }
};
int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};
vector<vector<vector<map<int, int>>>> dist;
int dijkstra()
{
  priority_queue<Node> pq;
  pq.push(Node{0, 0, origin, 4, 1});
  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();
    DEBUG u.print();
    if (!dist[u.pos.i][u.pos.j][u.prvDir].count(u.combo) && u.dist > dist[u.pos.i][u.pos.j][u.prvDir][u.combo])
      continue;

    for (int dir = 0; dir < 4; dir++)
    {
      Pos newPos = {u.pos.i + di[dir], u.pos.j + dj[dir]};
      if (newPos.i < 0 || newPos.i >= n || newPos.j < 0 || newPos.j >= m || mat[newPos.i][newPos.j] == '@') continue;
      int newDist = u.dist + (u.prvDir == dir && u.combo < k ? 0 : 1);
      int newCombo = dir == u.prvDir ? min(u.combo + 1, k) : 1;
      if (!dist[newPos.i][newPos.j][dir].count(newCombo) || newDist < dist[newPos.i][newPos.j][dir][newCombo])
      {
        dist[newPos.i][newPos.j][dir][newCombo] = newDist;
        pq.push(Node{newDist, newDist + manhattan(newPos), newPos, dir, newCombo});
      }
    }
  }
  int ans = 1e9;
  for (int i = 0; i < 5; i++)
    for (auto &hehe: dist[destination.i][destination.j][i])
      ans = min(ans, hehe.second);
  return ans == 1e9 ? -1 : ans;
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    mat.clear();
    mat.resize(n, vector<char>(m));
    dist.clear();
    dist.resize(n, vector<vector<map<int, int>>>(m));
    origin.read(); destination.read();

    char line[m + 1];
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", line);
      for (int j = 0; j < m; j++)
      {
        mat[i][j] = line[j];
        dist[i][j].resize(5);
      }
    }

    int ans = dijkstra();
    printf("%d\n", ans);
  }
  return 0;
}