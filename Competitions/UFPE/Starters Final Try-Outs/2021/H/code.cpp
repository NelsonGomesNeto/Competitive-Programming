#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

vector<short> init, resolved;
lli cost[9];

void printMat(vector<short> &mat)
{
  for (int i = 0; i < 9; i++)
    printf("%d%c", mat[i], i % 3 == 2 ? '\n' : ' ');
}

struct Node
{
  vector<short> curr;
  lli c, h;
  void calcH()
  {
    h = 0;
    for (int i = 0; i < 9; i++)
      h += resolved[i] != curr[i];
  }
  bool operator<(const Node &other) const
  {
    // return c > other.c;
    return c + h > other.c + h;
  }
};
map<vector<short>, lli> dist;
int di[4] = {-3, 1, -1, 3};
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
    if (dist.count(resolved)) break;
    if (dist[u.curr] < u.c) continue;

    for (int i = 0; i < 9; i++)
      if (u.curr[i] == 0)
        for (int k = 0; k < 4; k++)
        {
          int ni = i + di[k];
          if (ni >= 0 && ni < 9)
          {
            Node v = u;
            v.c += cost[v.curr[ni]];
            swap(v.curr[i], v.curr[ni]);
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
  for (int tt = 1; tt <= 2; tt++)
  {
    init.clear(); resolved.clear();
    for (int i = 0; i < 9; i++)
    {
      resolved.push_back(i + 1);
      init.push_back(0);
      scanf("%hd", &init.back());
    }
    resolved.back() = 0;

    for (int i = 1; i < 9; i++)
      scanf("%lld", &cost[i]);

    dist.clear();
    lli ans = astar();
    printf("%lld\n", ans);
  }

  return 0;
}