#include <bits/stdc++.h>
using namespace std;

const int maxN = 5000 * 2;
map<string, int> cityMap;
vector<int> graph[maxN];

int color[maxN];
int has[maxN];
bool hasCycle(int u)
{
  if (color[u]) return(color[u] == 1);
  color[u] = 1;
  for (int v: graph[u])
    if (hasCycle(v))
      return(has[v] = true);
  color[u] = 2;
  return(false);
}

int main()
{
  int n; scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    string a, b; cin >> a >> b;
    if (!cityMap.count(a)) cityMap[a] = cityMap.size();
    if (!cityMap.count(b)) cityMap[b] = cityMap.size();
    int u = cityMap[a], v = cityMap[b];
    graph[u].push_back(v);
  }

  memset(has, -1, sizeof(has));
  string q;
  while (cin >> q)
  {
    int u = cityMap[q];
    cout << q;
    if (has[u] == -1)
    {
      memset(color, 0, sizeof(color));
      has[u] = hasCycle(u);
    }
    if (has[u]) cout << " safe\n";
    else cout << " trapped\n";
  }

  return(0);
}