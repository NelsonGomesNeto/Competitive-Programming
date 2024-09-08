#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    lli n, k; scanf("%lld %lld", &n, &k);
    lli m = k / (n - 1) - (k % (n - 1) == 0);
    // while ((m + 1) * (n - 1) < k) m++;
    lli rem = k - m * (n - 1);
    printf("%lld\n", m * n + rem);
  }
  return 0;
}
