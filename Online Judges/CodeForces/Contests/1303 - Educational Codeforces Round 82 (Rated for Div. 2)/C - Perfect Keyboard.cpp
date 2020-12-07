#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 200 + 1;
char ss[maxN];
string s;

vector<int> graph[26];
int indegree[26];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    memset(indegree, 0, sizeof(indegree));
    for (int i = 0; i < 26; i ++) graph[i].clear();

    scanf(" %s", ss);
    s = string(ss);
    for (int i = 0; i < s.size() - 1; i ++)
    {
      int u = min(s[i], s[i + 1]) - 'a', v = max(s[i], s[i + 1]) - 'a';
      graph[u].push_back(v);
      indegree[v] ++;
    }

    queue<int> q;
    string ans = "";
    for (int i = 0; i < 26; i ++)
      if (!indegree[i])
        q.push(i);
    while (!q.empty())
    {
      int u = q.front(); q.pop();
      ans += (char)(u + 'a');
      for (int v: graph[u])
        if (-- indegree[v] == 0)
          q.push(v);
    }
    // printf("%s %d\n", ans.c_str(), (int)ans.size());
    // for (int i = 0; i < 26; i ++)
    //   printf("%d%c", indegree[i], i < 25 ? ' ' : '\n');

    if (ans.size() == 26)
      printf("YES\n%s\n", ans.c_str());
    else
      printf("NO\n");
  }
  return 0;
}