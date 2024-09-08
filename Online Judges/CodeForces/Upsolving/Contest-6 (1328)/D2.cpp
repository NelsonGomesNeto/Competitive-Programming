#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int t[maxN], c[maxN];
bool visited[maxN];

int main()
{
  int q; scanf("%d", &q);
  while (q--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &t[i]);
      t[i]--, visited[i] = false, c[i] = 1;
    }
    bool isCycle = true, hasDiff = false;
    for (int i = 0; i < n; i++)
    {
      int u = i, nxt = (i+1)%n, prv = i?i-1:n-1;
      if (t[u] == t[nxt])
        isCycle = false;
      else
        hasDiff = true;
    }
    DEBUG printf("isCycle: %d, hasDiff: %d\n", isCycle, hasDiff);

    if (!hasDiff)
    {
      for (int i = 0; i < n; i++)
        c[i] = 1;
    }
    else if (isCycle)
    {
      for (int i = 0; i < n; i++)
        c[i] = (i&1) + 1;
      if (n & 1)
        c[n - 1] = 3;
    }
    else
    {
      vector<vector<int>> groups;
      int start = 0;
      for (int i = 0; i < n; i++)
      {
        int j = i;
        while (j + 1 < n && t[j + 1] == t[i]) j++;
        int k = j;
        while (t[(k+1)%n] != t[k]) k = (k+1)%n;
        start = (k+1)%n;
        break;
      }

      for (int i = start, done = 0; done < n; i=(i+1)%n, done++)
      {
        if (visited[i]) continue;
        int j = i;
        while (j + 1 < n && t[j + 1] == t[i]) j++;
        groups.push_back(vector<int>());
        int k = j;
        groups.back().push_back(k), visited[k] = true;
        while (t[(k+1)%n] != t[k])
        {
          k = (k+1)%n;
          groups.back().push_back(k), visited[k] = true;
        }
        i = k;
      }
      DEBUG {
        printf("%d groups\n", (int)groups.size());
        for (vector<int> &group: groups)
        {
          printf("\t");
          for (int i = 0; i < group.size(); i++)
            printf("%d%c", group[i], i < group.size() - 1 ? ' ' : '\n');
        }
      }

      for (vector<int> &group: groups)
        for (int i = 0; i < group.size(); i++)
          c[group[i]] = (i&1) + 1;
    }

    DEBUG
    {
      bool valid = true;
      for (int i = 0; i < n; i++)
      {
        int nxt = (i+1) % n;
        if (t[i] != t[nxt] && c[i] == c[nxt])
          valid = false;
      }
      printf("%s\n", valid ? "VALID" : "INVALID");
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
      ans = max(ans, c[i]);
    printf("%d\n", ans);
    for (int i = 0; i < n; i++)
      printf("%d%c", c[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}