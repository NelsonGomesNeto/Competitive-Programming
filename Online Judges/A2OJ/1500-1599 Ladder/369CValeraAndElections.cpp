#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n;
struct Road
{
  int city; bool hasProblem;
  bool operator<(const Road &a) const { return(hasProblem < a.hasProblem); }
};
vector<Road> graph[maxN];

/* Explanation:
While on a DFS, mark 1 on memo if the actual vertex (if it's connected to a problematic road)
  dfs()
  memo[nowVertex] += memo[adjaecentVertex]
The intuition is: if there are anyone further from me that also has problems, they sure
will pass throught me and solve my problems
Now we only need to elect the obligatory ones, which are the ones with memo[i] == 1
*/

int problems[maxN], memo[maxN];
void dfs(int u = 0, int prv = -1)
{
  memo[u] = problems[u];
  for (auto v: graph[u])
    if (v.city != prv)
    {
      dfs(v.city, u);
      memo[u] += memo[v.city];
    }
}

int main()
{
  scanf("%d", &n);
  for (int i = 0, u, v, t; i < n - 1; i ++)
  {
    scanf("%d %d %d", &u, &v, &t); u --, v --;
    graph[u].push_back({v, t == 2}), graph[v].push_back({u, t == 2});
    if (t == 2) problems[u] = problems[v] = 1;
  }

  dfs();

  vector<int> elected;
  for (int i = 0; i < n; i ++)
    if (memo[i] == 1)
      elected.push_back(i);

  printf("%d\n", (int) elected.size());
  for (int i: elected) printf("%d ", i + 1);
  printf("\n");

  return(0);
}