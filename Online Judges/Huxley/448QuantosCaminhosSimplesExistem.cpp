#include <bits/stdc++.h>
using namespace std;
set<string> done;
vector<string> intToString;
int dp[(int) 1e6];

int dfs(vector<vector<pair<int, int > > > graph, int u, int target, int size)
{
  // printf("%d %d %d\n", u, graph[u].size(), dp[u]);
  if (u == target)
  {
    // done.insert(path.c_str());
    return(1);
  }
  if (dp[u] == -1)
  {
    int ans = 0;
    // dp[u] = 0;
    for (auto v: graph[u])
      // path += intToString[v.first];
      if (dp[v.first] == -1)
        ans += dfs(graph, v.first, target, size + v.second);
      // path.erase(path.begin() + size);
    dp[u] = 1 + ans;
  }
  return(dp[u]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  int n; scanf("%d\n", &n);
  map<string, int> stringToInt;
  vector<vector<pair<int, int> > > graph;
  char u[1000] = "", v[1000] = "", end;
  string uu, vv;
  for (int i = 0; i < n; i ++)
  {
    scanf("%s%c", u, &end); uu = u;
    if (!stringToInt.count(uu)) stringToInt[uu] = stringToInt.size(), graph.push_back(vector<pair<int, int> >()), intToString.push_back(uu);
    if (end == '\n') continue;
    while (scanf("%s%c", v, &end) && end != '\n')
    {
      vv = v;
      if (!stringToInt.count(vv)) stringToInt[vv] = stringToInt.size(), graph.push_back(vector<pair<int, int> >()), intToString.push_back(vv);
      graph[stringToInt[uu]].push_back({stringToInt[vv], (int) strlen(v)});
    }
    vv = v;
    if (!stringToInt.count(vv)) stringToInt[vv] = stringToInt.size(), graph.push_back(vector<pair<int, int> >()), intToString.push_back(vv);
    graph[stringToInt[uu]].push_back({stringToInt[vv], (int) strlen(v)});
  }
  scanf("%s %s", u, v);
  string path = ""; uu = u; vv = v;
  if (!stringToInt.count(uu) || !stringToInt.count(vv)) printf("0\n");
  else
  {
    path += u;
    printf("QQQ\n");
    int lol = dfs(graph, stringToInt[uu], stringToInt[vv], (int) strlen(u));
    for (auto s: done) printf("%s\n", s.c_str());
    printf("%d\n", (int) done.size());
    printf("%d\n", lol);
  }
  return(0);
}
