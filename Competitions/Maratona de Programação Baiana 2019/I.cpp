#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
pair<int, char> parent[maxN];
vector<int> tree[maxN];

int level[maxN], memo[maxN + 1], memo2[maxN][26];
int startLetter = 'a';

void dfs(int u = 0)
{
  for (int v: tree[u])
  {
    level[v] = level[u] + 1;
    dfs(v);
  }
}

int main()
{
  scanf("%d", &n);
  int pp[n];
  for (int i = 0; i < n - 1; i ++) scanf("%d", &pp[i]);
  string ll; cin >> ll;
  for (int i = 0; i < n - 1; i ++)
  {
    parent[i + 1] = {pp[i] - 1, ll[i]};
    DEBUG printf("%d %d %c\n", i + 1, pp[i] - 1, ll[i]);
    tree[pp[i] - 1].push_back(i + 1);
    startLetter = max(startLetter, (int) ll[i]);
  }
  DEBUG printf("----------------\n");
  dfs();
  priority_queue<pair<pair<int, pair<char, int>>, pair<int, int>>> pq;
  int winner = 1, winnersz = 0, winnerlv = 0;
  for (int i = 1; i < n; i ++)
    if (parent[i].second == startLetter)
      pq.push({{-1, {startLetter, level[i]}}, {parent[i].first, i}}), winner = i;

  while (!pq.empty())
  {
    int u = pq.top().second.first, root = pq.top().second.second, sz = -pq.top().first.first, lt = pq.top().first.second.first, lv = pq.top().first.second.second;
    DEBUG printf("%d %d %d %c\n", u, root, sz, lt);
    pq.pop();
    if (lt < memo[sz] || sz < memo2[u][lt - 'a']) continue;
    memo[sz] = lt, memo2[u][lt - 'a'] = sz;
    winner = root;
    if (u == 0) continue;
    pq.push({{-(sz + 1), {parent[u].second, level[u]}}, {parent[u].first, root}});
  }

  string ans = ""; int now = winner;
  while (now != 0)
  {
    ans += parent[now].second;
    now = parent[now].first;
  }
  cout << ans << endl;

  return(0);
}