#include <bits/stdc++.h>
using namespace std;

/* Explanation:
Online: Probably only with a Link Cut Tree, since it queries to modify topology (still doesn't know how it works)
Offline:
  Note that there can be multiple trees
  You will store queries of type 1 and 2, the trees and "x wants i document"
  for each query in queries:
    type 1: use Union find to merge x and y
    type 2: answer every single query that wants this document d
      since this document will only expand accordingly to now's tree, no matter
      what happens afterwards, d will only reach the highest parent of x (it's employee)
      for each qd in documentQueries:
        if sameSet(qd.employee, x) and qd.employee is parent of x (or is x):
          qd.employee will have signed document d
          (check if it's parent can be done either with LCA or in out DP)
  Remeber to store the answers and then print them in the correct order ;)
*/

const int maxN = 1e5; int n, m;
vector<int> trees[maxN]; bool notRoot[maxN]; int in[maxN], out[maxN], parent[maxN], t;
vector<vector<int>> queries;
vector<pair<int, int>> documentQueries[maxN]; int documentID, ans[maxN], ansID;

int findParent(int u)
{
  if (parent[u] == u) return(u);
  return(parent[u] = findParent(parent[u]));
}

void dfs(int u)
{
  in[u] = t ++;
  for (int v: trees[u]) dfs(v);
  out[u] = t ++;
}

int main()
{
  scanf("%d %d", &n, &m);
  int op, x, y;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d", &op, &x); x --;
    if (op == 1)
    {
      scanf("%d", &y); y --;
      trees[y].push_back(x), notRoot[x] = true;
      queries.push_back({op, x, y}); // y becomes boss of x
    }
    else if (op == 2) queries.push_back({op, x, documentID ++});
    else
    {
      scanf("%d", &y); y --;
      documentQueries[y].push_back({x, ansID ++}); // ansID is when x wanted for document y
    }
  }
  for (int i = 0; i < n; i ++)
  {
    parent[i] = i;
    if (!notRoot[i]) dfs(i);
  }

  for (auto query: queries)
  {
    op = query[0], x = query[1], y = query[2];
    if (op == 1) parent[x] = y;
    else
      for (auto w: documentQueries[y]) // (x, ansID)
        ans[w.second] = findParent(w.first) == findParent(x) && in[w.first] <= in[x] && out[w.first] >= out[x];
  }
  for (int i = 0; i < ansID; i ++) printf("%s\n", ans[i] ? "YES" : "NO");

  return(0);
}
