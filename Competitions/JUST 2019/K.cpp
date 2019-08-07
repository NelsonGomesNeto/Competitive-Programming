#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    lli a[n]; for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
    lli sum = 0; for (int i = 0; i < n; i ++) sum |= a[i];
    lli ones = 0, aux = sum;
    while (aux) { ones += aux & 1; aux >>= 1; }
    printf("%lld\n", ones);
  }
  return(0);
}