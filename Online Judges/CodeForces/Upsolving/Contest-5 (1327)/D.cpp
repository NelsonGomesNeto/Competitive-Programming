#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int p[maxN], c[maxN];
bool visited[maxN];
vector<vector<int>> cycles;

bool valid(vector<int> &cycle, int k)
{
  for (int j = 0; j < k; j++)
  {
    bool valid = true;
    for (int i = j; i < cycle.size() && valid; i += k)
      if (c[cycle[i]] != c[cycle[j]])
        valid = false;
    if (valid) return true;
  }
  return false;
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    cycles.clear();
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &p[i]);
      p[i]--, visited[i] = false;
    }
    for (int i = 0; i < n; i++)
      scanf("%d", &c[i]);

    for (int i = 0; i < n; i++)
    {
      cycles.push_back(vector<int>());
      if (!visited[i])
      {
        visited[i] = true;
        int at = p[i]; cycles.back().push_back(at);
        while (at != i)
        {
          at = p[at];
          cycles.back().push_back(at);
          visited[at] = true;
        }
      }
    }

    int ans = 1e9;
    for (vector<int> &cycle: cycles)
      for (int i = 1, end = sqrt(cycle.size()); i <= end; i++)
        if (cycle.size() % i == 0)
        {
          if (valid(cycle, i))
            ans = min(ans, i);
          int ii = cycle.size() / i;
          if (cycle.size() % ii == 0 && valid(cycle, ii))
            ans = min(ans, ii);
        }
    printf("%d\n", ans);
  }
  return 0;
}