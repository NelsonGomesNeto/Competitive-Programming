#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
lli a[maxN];
lli b[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n, x; scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      b[i] = a[i];
    }
    sort(b, b+n);

    bool sorted = true;
    for (int i = 1; i < n; i++) if (a[i - 1] > a[i]) sorted = false;

    int range = n - x;
    bool isSorted = true;
    for (int i = range; i < n - range; i++) if (a[i] != b[i]) isSorted = false;

    bool can = sorted || x == 1 || isSorted;

    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
