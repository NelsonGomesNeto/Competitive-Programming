#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  We always want the biggest shortest path
  Let's inverse the graph edges, notice that the schedule won't change
  But now, we can only reach u from v: if color[u] = edgeColor[(v, u)]

  Running a BFS from n, whenever we reach a vertex, we've done so
  through the shortest path. Also, depending on the edge we've used:
  we've reached u with the shortest path and with color[u] = edgeColor.

  So the first time we reach u, we've reached u with color c. So u's
  color must be (1 - c). And since we want to paint this vertex with
  (1 - c), we must as well wait for it to be reached with that color.
  Notice that it may not happen, so it's possible to find a schedule
  such that Egor will be there forever.

  The rigorous proof is here: https://codeforces.com/blog/entry/82417
*/

const int maxN = 5e5; int n, m;
const int inf = 1e6;

struct Node
{
  int u; bool isDay; int distance;
};
vector<int> graph[2][maxN];
int distances[2][maxN], colors[maxN];
int bfs(int u = 0)
{
  memset(colors, 0, sizeof(colors));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < 2; j++)
      distances[j][i] = inf;

  queue<Node> q;
  q.push(Node{n - 1, false, 0});
  q.push(Node{n - 1, true, 0});
  while (!q.empty())
  {
    Node node = q.front(); q.pop();
    if (distances[node.isDay][node.u] != inf) continue;
    distances[node.isDay][node.u] = node.distance;
    colors[node.u] = distances[1][node.u] > distances[0][node.u];

    // node.distance is the biggest possible between day and night
    // since the other is already filled with the shortest path
    if (distances[1 - node.isDay][node.u] != inf)
      for (int isDay = 0; isDay < 2; isDay++)
        for (int v: graph[isDay][node.u])
          q.push(Node{v, (bool)isDay, node.distance + 1});
  }
  return max(distances[0][0], distances[1][0]);
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++)
      graph[0][i].clear(), graph[1][i].clear();

    for (int i = 0; i < m; i++)
    {
      int u, v, day; scanf("%d %d %d", &u, &v, &day); u--, v--;
      graph[day][v].push_back(u);
    }

    int ans = bfs();
    ans = ans == inf ? -1 : ans;
    printf("%d\n", ans);
    for (int i = 0; i < n; i++)
      printf("%d", colors[i]);
    printf("\n");
  }
  return 0;
}
