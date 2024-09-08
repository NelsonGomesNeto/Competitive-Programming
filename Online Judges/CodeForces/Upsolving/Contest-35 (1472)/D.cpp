#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    sort(a, a+n, greater<lli>());

    lli alice = 0, bob = 0;
    for (int i = 0; i < n; i++)
      if (i & 1)
        bob += a[i] & 1 ? a[i] : 0;
      else
        alice += a[i] & 1 ? 0 : a[i];

    printf("%s\n", alice > bob ? "Alice" : alice == bob ? "Tie" : "Bob");
  }
  return 0;
}
