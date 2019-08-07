#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n, k;
lli x[maxN], acc[maxN + 1], maximum[maxN];

int main()
{
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &x[i]);
    acc[i + 1] = acc[i] + x[i];
  }
  for (int i = n - k; i >= 0; i --)
    maximum[i] = max(maximum[i + 1], acc[i + k] - acc[i]);;

  int a, b; lli bestTotal = -1;
  for (int i = 0; i < n - k + 1; i ++)
    if (acc[i + k] - acc[i] + maximum[i + k] > bestTotal)
      bestTotal = acc[i + k] - acc[i] + maximum[i + k], a = i;
  bestTotal = -1;
  for (int i = a + k; i < n - k + 1; i ++)
    if (acc[i + k] - acc[i] > bestTotal)
      bestTotal = acc[i + k] - acc[i], b = i;
  printf("%d %d\n", a + 1, b + 1);

  return(0);
}