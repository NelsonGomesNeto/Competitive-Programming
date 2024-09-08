#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
lli b[maxN];
set<int> has;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &b[i]);

    bool ans = false;
    has.clear();
    for (int i = 0; i < n && !ans; i++)
    {
      if (has.count(b[i])) ans = true;
      else has.insert(b[i]);
    }

    printf("%s\n", ans ? "YES" : "NO");
  }
  return 0;
}
