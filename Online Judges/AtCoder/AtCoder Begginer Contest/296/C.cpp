#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n; lli x;
lli a[maxN];

int main()
{
  while (~scanf("%d %lld", &n, &x))
  {
    for (int i = 0; i < n; ++i)
      scanf("%lld", &a[i]);

    bool ans = false;
    set<lli> has;
    for (int i = 0; i < n; ++i)
    {
      has.insert(a[i]);
      if (has.count(x + a[i]) || has.count(a[i] - x))
        ans = true;
    }
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
