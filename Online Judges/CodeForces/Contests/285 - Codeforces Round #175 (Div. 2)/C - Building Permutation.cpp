#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  lli a[n]; for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
  sort(a, a+n);
  lli cost = 0;
  for (int i = 0; i < n; i ++)
    cost += abs(i + 1 - a[i]);
  printf("%lld\n", cost);
  
  return(0);
}