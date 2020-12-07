#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define llu unsigned long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3, inf = 1e9; int n, m;
char mat[maxN][maxN + 1];

struct Pos
{
  int i, j;
  bool operator==(const Pos &other) const { return i == other.i && j == other.j; }
  bool valid() { return i >= 0 && j >= 0 && i < n && j < m; }
};
Pos origin, destination;

// Best lexicografical order: D L R U
int di[4] = {1, 0, 0, -1}, dj[4] = {0, -1, 1, 0};
char dir[5] = "DLRU";

bool bigger(const vector<lli> &a, const vector<lli> &b)
{
  return a > b;
  int i = 0, j = 0; lli ii = a[0], jj = b[0];
  while (true)
  {
    int aa = ii % 10, bb = jj % 10;
    if (aa != bb) return aa > bb;
    ii /= 10, jj /= 10;
    if (ii == 0) ii = a[++i];
    if (jj == 0) jj = b[++j];
    if (i >= a.size()) return false;
    if (j >= b.size()) return true;
  }
}

struct Node
{
  Pos position; int distance;
  int bitPos;
  vector<llu> path;
  bool operator<(const Node &other) const
  {
    return distance > other.distance || (distance == other.distance && path > other.path);
  }
  void print()
  {
    printf("(%d, %d), distance = %d\n", position.i, position.j, distance);
    printf("\t");
    for (llu i: path) printf("%llu ", i);
    printf("\n");
  }
};

int dist[maxN][maxN];
Pos nxt[maxN][maxN][4];
Node dijkstra()
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      dist[i][j] = inf;
  priority_queue<Node> pq; pq.push({origin, dist[origin.i][origin.j] = 0, -1, {}});
  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();
    // u.print();
    if (u.distance > dist[u.position.i][u.position.j])
      continue;
    if (u.position == destination)
      return u;

    for (int k = 0; k < 4; k++)
    {
      Pos newPos = nxt[u.position.i][u.position.j][k];
      if (!newPos.valid() || mat[newPos.i][newPos.j] != '.') continue;

      if (u.distance + 1 < dist[newPos.i][newPos.j])
      {
        vector<llu> lol = u.path;
        int bitPos = u.bitPos;
        if (bitPos < 0)
          lol.push_back(0), bitPos = 62;

        lol.back() = lol.back() | ((lli)k << bitPos);
        bitPos -= 2;
        pq.push({newPos, dist[newPos.i][newPos.j] = u.distance + 1, bitPos, lol});
      }
    }
  }
  return Node{origin, -1, -1, {}};
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", mat[i]);
      for (int j = 0; j < m; j++)
        if (mat[i][j] == 'S')
          mat[i][j] = '.', origin = Pos{i, j};
        else if (mat[i][j] == 'E')
          mat[i][j] = '.', destination = Pos{i, j};
    }

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (mat[i][j] == '.')
          for (int k = 0; k < 4; k++)
          {
            int m = 1;
            Pos newPos = Pos{i + m*di[k], j + m*dj[k]};
            while (newPos.valid() && mat[newPos.i][newPos.j] == 'X')
            {
              newPos = Pos{i + m*di[k], j + m*dj[k]};
              m++;
            }

            nxt[i][j][k] = newPos;
          }

    Node ans = dijkstra();
    printf("%d\n", ans.distance);
    if (ans.distance != -1)
    {
      string s = "";
      int done = 0;
      for (llu hehe: ans.path)
        for (int at = 62; done < ans.distance && at >= 0; at-=2, done++)
          s += dir[(hehe >> at) & 3];
      printf("%s\n", s.c_str());
    }
  }
  return 0;
}