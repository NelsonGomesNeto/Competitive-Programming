#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5 + 1; int n;
vector<int> graph[maxN];
void addEdge(int u, int v)
{
  graph[u].push_back(v), graph[v].push_back(u);
}
lli a[maxN], b[maxN];
int color[maxN];

struct Edge
{
  int kind; lli w; int u, v;
  bool operator<(const Edge &other) const { return w < other.w; }
};
vector<Edge> edges;

/*
  Let's assume 0 is white (0)
  Now, we just need to choose the color of every other vertex
  If we paint it white: we need to remove the edge with 0
  Also, if we paint it the same color as the previous: we need to remove the edge with the previous
*/
lli memo[maxN][2][2];
lli solve(int i = 1, int color = 0, int firstColor = 0)
{
  if (i == n + 1) return 0;
  lli &ans = memo[i][color][firstColor];
  if (ans != -1) return ans;

  if (i == 1)
  {
    ans = min(solve(i + 1, 0, 0) + a[i - 1], solve(i + 1, 1, 1));
  }
  else if (i < n)
  {
    ans = min(solve(i + 1, 0, firstColor) + a[i - 1] + b[i - 2]*(color == 0),
              solve(i + 1, 1, firstColor) + b[i - 2]*(color == 1));
  }
  else
  {
    ans = min(solve(i + 1, 0, firstColor) + a[i - 1] + b[i - 2]*(color == 0) + b[i - 1]*(firstColor == 0),
              solve(i + 1, 1, firstColor) + b[i - 2]*(color == 1) + b[i - 1]*(firstColor == 1));
  }
  return ans;
}

int main()
{
  int pundim = 0;
  while (~scanf("%d", &n))
  {
    if (pundim++)
    {
      for (int i = 0; i <= n; i++) graph[i].clear();
      printf("---------------\n");
    }

    for (int i = 1; i <= n; i++)
      addEdge(0, i), addEdge(i, i + 1 > n ? 1 : i + 1);

    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < n; i++)
      scanf("%lld", &b[i]);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}