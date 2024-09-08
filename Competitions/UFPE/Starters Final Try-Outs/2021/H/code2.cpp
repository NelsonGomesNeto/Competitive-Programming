#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

#define game8 vector<vector<short>>

template <typename General>
struct hash_function {
  size_t operator()(General const& c) const {
    size_t hashValue = 0;
    for (auto i: c) hashValue += hash<string>() (string(i.begin(), i.end()));
    return(hashValue);
  }
};
unordered_map<game8, int, hash_function<game8>> done;

game8 init, resolved;
lli cost[9];

void printMat(game8 &mat)
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
    printf("%d%c", mat[i][j], j == 2 ? '\n' : ' ');
}

struct Node
{
  game8 curr;
  lli c, h;
  void calcH()
  {
    h = 0;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        h += resolved[i][j] != curr[i][j];
  }
  bool operator<(const Node &other) const
  {
    return c > other.c;
    return c + h > other.c + h;
  }
};
unordered_map<game8, lli, hash_function<game8>> dist;
int di[4] = {-1, 1, 0, 0}, dj[4] = {0, 0, -1, 1};
lli astar()
{
  priority_queue<Node> pq;
  Node initNode = Node{init, 0};
  initNode.calcH();
  pq.push(initNode);
  dist[init] = 0;
  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();
    // printMat(u.curr); printf("\t%lld\n", u.c);
    // if (dist.count(resolved)) break;
    if (dist[u.curr] < u.c) continue;

    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
      if (u.curr[i][j] == 0)
        for (int k = 0; k < 4; k++)
        {
          int ni = i + di[k], nj = j + dj[k];
          if (ni >= 0 && ni < 3 && nj >= 0 && nj < 3)
          {
            Node v = u;
            v.c += cost[v.curr[ni][nj]];
            swap(v.curr[i][j], v.curr[ni][nj]);
            if (!dist.count(v.curr) || v.c < dist[v.curr])
            {
              v.calcH();
              dist[v.curr] = v.c;
              pq.push(v);
            }
          }
        }
  }

  assert(dist.count(resolved));
  return dist[resolved];
}

int main()
{
  for (int tt = 1; tt <= 1; tt++)
  {
    init.clear(); resolved.clear();
    init.resize(3, vector<short>(3)), resolved.resize(3, vector<short>(3));
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
      {
        resolved[i][j] = i*3 + j + 1;
        scanf("%hd", &init[i][j]);
      }
    resolved[2][2] = 0;

    for (int i = 1; i < 9; i++)
      scanf("%lld", &cost[i]);

    dist.clear();
    lli ans = astar();
    printf("%lld\n", ans);
  }

  return 0;
}