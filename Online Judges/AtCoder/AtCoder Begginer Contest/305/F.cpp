#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n, m;
char ok[4];

bool done;
bool known[maxN];
bool visited[maxN];
vector<vector<int>> graph;
void goTo(int u, bool start = false)
{
  if (done) return;
  if (!start)
  {
    printf("%d\n", u + 1);
    fflush(stdout);
  }
  if (u == n - 1)
  {
    scanf(" %s", ok);
    done = true;
    return;
  }

  int k;
  scanf("%d", &k);
  for (int i = 0; i < k; ++i)
  {
    int v;
    scanf("%d", &v);
    --v;
    if (!known[u])
      graph[u].push_back(v);
  }
  if (!known[u])
    sort(graph[u].begin(), graph[u].end(), greater<int>());
  DEBUG printf("\tfinished visiting %d\n", u + 1);

  known[u] = true;
  visited[u] = true;
}

void dfs(int u = 0, int prv = -1)
{
  if (done) return;
  goTo(u, u == 0 && prv == -1);

  for (int v : graph[u])
    if (!visited[v])
      dfs(v, u);

  if (prv != -1)
    goTo(prv);
}

int main()
{
  scanf("%d %d", &n, &m);

  fill(known, known+n, false);
  fill(visited, visited+n, false);
  graph.clear();
  graph.resize(n);

  done = false;
  dfs();

  return 0;
}
