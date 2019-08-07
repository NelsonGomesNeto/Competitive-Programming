#include <bits/stdc++.h>
using namespace std;
#define lli long long int

int main()
{
  int n, x; scanf("%d %d", &n, &x);
  int knowledge[n];
  for (int i = 0; i < n; i ++)
    scanf("%d", &knowledge[i]);
  sort(knowledge, knowledge+n);

  lli cost = 0;
  for (int i = 0; i < n; i ++)
  {
    cost += (lli) knowledge[i] * x;
    x = x == 1 ? x : x - 1;
  }

  printf("%lld\n", cost);

  return(0);
}