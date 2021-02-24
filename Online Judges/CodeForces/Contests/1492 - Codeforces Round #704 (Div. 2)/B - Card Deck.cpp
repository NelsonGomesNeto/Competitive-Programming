#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int p[maxN];
int pos[maxN + 1];
vector<int> ans;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &p[i]);
      pos[p[i]] = i;
    }

    ans.clear();
    int curr = n - 1;
    for (int i = n; i >= 1; i--)
    {
      for (int j = pos[i]; j <= curr; j++)
        ans.push_back(p[j]);
      curr = n - ans.size() - 1;
    }
    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
