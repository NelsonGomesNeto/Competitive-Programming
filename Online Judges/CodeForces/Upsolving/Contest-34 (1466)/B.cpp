#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int x[maxN];
bool added[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &x[i]);

    for (int i = 0; i < n; i++) added[i] = false;
    for (int i = 0; i < n; i++)
    {
      int j = i;
      while (j + 1 < n && x[j + 1] == x[i]) j++;
      int sz = j - i + 1;
      i = j;
      if (sz > 1) x[i]++, added[i] = true;
    }
    map<int, int> ans;
    for (int i = 0; i < n; i++)
    {
      if (!added[i] && ans.count(x[i])) x[i]++;
      if (!ans.count(x[i])) ans[x[i]] = 0;
      ans[x[i]]++;
    }

    printf("%d\n", (int)ans.size());
  }
  return 0;
}
