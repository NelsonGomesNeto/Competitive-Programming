#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n1, n2;
vector<int> tree[2*maxN];

int dist[2*maxN], prv[2*maxN];
void bfs(int source)
{
  fill(dist, dist+n1+n2, -1);
  queue<int> q;
  dist[source] = 0;
  q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (int v: tree[u])
      if (dist[v] == -1)
      {
        dist[v] = dist[u] + 1;
        prv[v] = u;
        q.push(v);
      }
  }
}
int findMid(int a, int b, int d)
{
  int midd = (d) >> 1;

  while (midd)
  {
    b = prv[b];
    midd--;
  }

  return b;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) tree[i].clear();
    for (int i = 1; i < n1; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    scanf("%d", &n2);
    for (int i = 0; i < n2; i++) tree[n1 + i].clear();
    for (int i = 1; i < n2; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      u += n1, v += n1;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    bfs(0);
    int a1 = max_element(dist, dist+n1) - dist;
    bfs(a1);
    int b1 = max_element(dist, dist+n1) - dist;
    int d1 = *max_element(dist, dist+n1);
    int mid1 = findMid(a1, b1, d1);

    bfs(n1);
    int a2 = max_element(dist+n1, dist+n1+n2) - dist;
    bfs(a2);
    int b2 = max_element(dist+n1, dist+n1+n2) - dist;
    int d2 = *max_element(dist+n1, dist+n1+n2);
    int mid2 = findMid(a2, b2, d2);

    tree[mid1].push_back(mid2);
    tree[mid2].push_back(mid1);

    bfs(0);
    int aa = max_element(dist, dist+n1+n2) - dist;
    bfs(aa);
    DEBUG printf("\t%d %d\n", d1, d2);
    printf("%d\n", *max_element(dist, dist+n1+n2));
    printf("%d %d\n", mid1 + 1, mid2 - n1 + 1);
  }
  return 0;
}