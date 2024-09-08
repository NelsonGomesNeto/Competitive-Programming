#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char ss[10];
string s[maxN];
string pre[maxN], suf[maxN];
map<string, vector<int>> suffixes, prefixes;
bool visited[maxN];
int indegree[maxN];

int memo[maxN][2][10];
int solve(int u, bool takahashi = false, int hehe = 0)
{
  int &ans = memo[u][takahashi][hehe];
  if (ans != -2) return ans;

  if (!prefixes.count(suf[u])) return ans = takahashi ? -1 : 1;

  ans = 0;
  int best = takahashi ? -1 : 1;
  for (auto &v: prefixes[suf[u]])
  {
    int res = solve(v, !takahashi, (hehe + 1) % 10);
    if (takahashi) best = max(best, res);
    else best = min(best, res);

    if (takahashi ? best == 1 : best == -1) break;
  }

  return ans = best;
}

int main()
{
  int hehe = 0;
  while (~scanf("%d", &n))
  {
    if (hehe++) printf("--------\n");

    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      s[i] = string(ss);
    }

    suffixes.clear(), prefixes.clear();
    for (int i = 0; i < n; i++)
    {
      prefixes[pre[i] = s[i].substr(0, 3)].push_back(i);
      suffixes[suf[i] = s[i].substr(s[i].size() - 3)].push_back(i);
    }

    DEBUG {
      printf("prefixes:\n");
      for (auto &p: prefixes)
      {
        printf("\t%s:", p.first.c_str());
        for (auto &i: p.second) printf(" %d", i);
        printf("\n");
      }
      printf("suffixes:\n");
      for (auto &p: suffixes)
      {
        printf("\t%s:", p.first.c_str());
        for (auto &i: p.second) printf(" %d", i);
        printf("\n");
      }
    }

    for (int i = 0; i < n; i++)
      for (int j = 0; j < 10; j++)
        memo[i][0][j] = memo[i][1][j] = -2;

    memset(visited, false, sizeof(visited));
    memset(indegree, 0, sizeof(indegree));
    for (int i = 0; i < n; i++)
      indegree[i] = prefixes.count(suf[i]) ? prefixes[suf[i]].size() : 0;

    priority_queue<pair<int, int>> q;
    for (int i = 0; i < n; i++)
      // if (indegree[i] == 0)
        q.push({indegree[i], i});
    while (!q.empty())
    {
      int u = q.top().second; q.pop();
      // if (visited[u]) continue;
      solve(u);
      // visited[u] = true;

      // for (int v: suffixes[pre[u]])
        // if (indegree[v]-- == 1)
          // q.push(v);
    }

    for (int i = 0; i < n; i++)
    {
      int res = solve(i);
      printf("%s\n", res == 0 ? "Draw" : res > 0 ? "Takahashi" : "Aoki");
    }
  }
  return 0;
}