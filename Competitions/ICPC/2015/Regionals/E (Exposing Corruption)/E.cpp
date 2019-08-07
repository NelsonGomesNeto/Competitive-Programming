#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100, maxB = 1e4, inf = 1e6; int d, p, r, b;
int dPrice[maxN], pPrice[maxN];
vector<int> graph[2*maxN]; bool visited[2*maxN];

struct Group
{
  int d, p, price;
  void operator+=(const Group &g)
  {
    d += g.d, p += g.p, price += g.price;
  }
  bool operator<(const Group &g)
  {

  }
  Group operator+(const Group &g)
  {
    return(Group({d + g.d, p + g.p, price + g.price}));
  }
};
vector<Group> groups;
Group nullGroup = Group({0, 0, 0});

Group dfs(int u)
{
  if (visited[u]) return(nullGroup);
  visited[u] = true;
  Group ans = Group({u < d, u >= d, u < d ? dPrice[u] : pPrice[u - d]});
  for (int v: graph[u]) ans += dfs(v);
  return(ans);
}

int memo[2][2*maxN][maxB];
int solve(bool dSolve, int i = 0, int budget = b)
{
  if (i == groups.size()) return(0);
  if (memo[dSolve][i][budget] == -inf)
  {
    int ans = solve(dSolve, i + 1, budget);
    if (groups[i].price <= budget)
      ans = max(ans, solve(dSolve, i + 1, budget - groups[i].price) + (dSolve ? groups[i].p - groups[i].d : groups[i].d - groups[i].p));
    memo[dSolve][i][budget] = ans;
  }
  return(memo[dSolve][i][budget]);
}

int main()
{
  scanf("%d %d %d %d", &d, &p, &r, &b);
  for (int i = 0; i < d; i ++) scanf("%d", &dPrice[i]);
  for (int i = 0; i < p; i ++) scanf("%d", &pPrice[i]);

  for (int i = 0, u, v; i < r; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    v += d;
    graph[u].push_back(v), graph[v].push_back(u);
  }
  for (int i = 0; i < d + p; i ++)
    if (!visited[i])
      groups.push_back(dfs(i));

  for (int i = 0; i < groups.size(); i ++) for (int j = 0; j <= b; j ++) memo[0][i][j] = memo[1][i][j] = -inf;
  int dAns = solve(true), pAns = solve(false);
  printf("%d %d\n", d + dAns, p + pAns);

  return(0);
}