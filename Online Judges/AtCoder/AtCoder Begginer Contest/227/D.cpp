#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
n!
/ (k! * (n - k)!)
*/

const int maxN = 2e5; int n, k;
lli a[maxN];
multiset<lli> now;
multiset<lli> rem;

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    sort(a, a+n);
    reverse(a, a+n);

    now.clear();
    for (int i = 0; i < k - 1; i++)
      now.insert(a[i]);
    rem.clear();
    for (int i = k - 1; i < n; i++)
      rem.insert(a[i]);

    lli ans = 0;
    lli base = 0;
    while (!rem.empty())
    {
      while (!rem.empty() && *rem.rbegin() > *now.begin() - base)
      {
        lli addToNow = *rem.rbegin() + base;
        lli addToRem = *now.begin() - base;
        now.erase(now.begin());
        now.insert(addToNow);
        rem.erase(prev(rem.end()));
        rem.insert(addToRem);
      }

      now.insert(*rem.begin() + base);
      rem.erase(rem.begin());

      lli curr = *now.begin() - base;
      if (curr > 0) ans += curr;
      base = ans;

      now.erase(now.begin());
    }

    printf("%lld\n", ans);
  }
  return 0;
}