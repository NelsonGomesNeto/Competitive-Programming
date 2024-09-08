#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    set<lli> aaa;
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      aaa.insert(a[i]);
    }

    printf("%d\n", (int)aaa.size());
  }
  return 0;
}
