#include <bits/stdc++.h>
#define lli long long int
using namespace std;

set<lli> reachable;

lli removeZeros(lli n)
{
  while (n % 10 == 0)
    n /= 10;
  return(n);
}

int main()
{
  lli n; scanf("%lld", &n);
  while (!reachable.count(n))
  {
    reachable.insert(n);
    n = removeZeros(n + 1);
  }
  printf("%d\n", (int) reachable.size());
  return(0);
}