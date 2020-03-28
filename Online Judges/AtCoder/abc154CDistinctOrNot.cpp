#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    set<lli> all;
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      all.insert(a[i]);
    }

    printf("%s\n", all.size() == n ? "YES" : "NO");
  }
  return 0;
}