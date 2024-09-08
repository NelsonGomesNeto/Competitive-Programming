#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
abs(x - y) + abs(x - -y)
abs(x - y) + abs(x + y)
The biggest of them:
2*n * x + positive numbers - somethings

only apply on positive numbers

80 80 56 56 48 48 40 40
*/

const int maxN = 1e5; int n;
lli d[2*maxN];
vector<lli> ud;
vector<lli> ans;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < 2*n; i++)
      scanf("%lld", &d[i]);
    sort(d, d+2*n, greater<lli>());
    ud.clear();
    for (int i = 0; i < 2*n; i++)
      ud.push_back(d[i]);
    ud.resize(distance(ud.begin(), unique(ud.begin(), ud.end())));
    if (ud.size() != n)
    {
      printf("NO\n");
      continue;
    }

    bool can = true;
    ans.clear();
    lli sum = 0;
    for (int i = 0; i < n; i++)
    {
      lli div = 2*n - 2*i;
      lli now = ud[i] - 2*sum;
      DEBUG printf("\t%d %lld - %lld %lld\n", i, ud[i], div, now);
      if (now >= 0 && now % div != 0)
      {
        can = false;
        break;
      }

      lli num = now / div;
      sum += num;
      ans.push_back(num), ans.push_back(-num);
    }
    sort(ans.begin(), ans.end(), greater<lli>());
    ans.resize(distance(ans.begin(), unique(ans.begin(), ans.end())));
    if (ans.size() != 2*n)
      can = false;

    if (can)
    {
      lli res = 0;
      for (int i = 0; i < 2*n; i++)
        res += abs(ans[n - 1] - ans[i]);
      if (res != ud.back())
        can = false;
    }

    DEBUG {
      for (int i = 0; i < ans.size(); i++)
        printf("%4lld%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
    }
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
