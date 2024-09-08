#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
lli a[maxN];
bool l[maxN], r[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);

    l[0] = true;
    for (int i = 1; i < n; i ++)
      l[i] = min(l[i - 1], a[i] >= i);
    r[n - 1] = true;
    for (int i = n - 2, j = 1; i >= 0; i --, j ++)
      r[i] = min(r[i + 1], a[i] >= j);

    bool can = false;
    for (int i = 0; i < n; i ++)
      if (l[i] && r[i])
        can = true;
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}
