#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6, maxM = 1e4, maxG = 1e3; int n, m, g, r;
const int inf = 1e9;
int d[maxM];

int dist[maxM][maxG];
struct Node
{
  int dis; int i, t;
  bool operator<(const Node &other) const
  {
    return dis > other.dis;
  }
};
int dijkstra()
{
  for (int i = 0; i < m; i++)
    for (int j = 0; j < g; j++)
      dist[i][j] = inf;
  priority_queue<Node, vector<Node>, less<Node>> pq;
  pq.push(Node{dist[0][0] = 0LL, 0, 0});
  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();
    DEBUG printf("\t%d %d %d\n", u.i, u.t, u.dis);
    if (u.dis > dist[u.i][u.t]) continue;
    int i = u.i + 1;
    if (i < m && u.t + d[i] - d[u.i] <= g)
    {
      int newT = (u.t + d[i] - d[u.i]);
      if (newT == g) newT = 0;
      int newDist = dist[u.i][u.t] + d[i] - d[u.i] + (newT == 0 && i != m - 1 ? r : 0);
      if (newDist < dist[i][newT])
        pq.push(Node{dist[i][newT] = newDist, i, newT});
    }
    i = u.i - 1;
    if (i >= 0 && u.t + d[u.i] - d[i] <= g)
    {
      int newT = (u.t + d[u.i] - d[i]);
      if (newT == g) newT = 0;
      int newDist = dist[u.i][u.t] + d[u.i] - d[i] + (newT == 0 && i != m - 1 ? r : 0);
      if (newDist < dist[i][newT])
        pq.push(Node{dist[i][newT] = newDist, i, newT});
    }
  }
  return *min_element(dist[m - 1], dist[m - 1]+g);
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < m; i++)
      scanf("%d", &d[i]);
    sort(d, d+m);
    scanf("%d %d", &g, &r);

    int ans = dijkstra();
    printf("%d\n", ans == inf ? -1 : ans);
  }
  return 0;
}
