#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    int plo = -1, phi = -1;
    int a[n];
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      if (plo == -1 || a[i] < a[plo])
        plo = i;
      if (phi == -1 || a[i] > a[phi])
        phi = i;
    }

    int ans = min({
      plo + 1 + (n - phi),
      phi + 1 + (n - plo),
      max(plo, phi) + 1,
      max(n - plo, n - phi)
    });
    printf("%d\n", ans);
  }
  return 0;
}
