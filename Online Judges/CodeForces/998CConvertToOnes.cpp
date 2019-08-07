#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  lli n, x, y; scanf("%lld %lld %lld", &n, &x, &y);
  int a[n], ones = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf("%01d", &a[i]);
    ones += a[i];
  }
  int start = 0, prev = a[0];
  while (start < n && a[start] == prev) start ++;

  lli c1 = 0, c2 = 0;
  for (int i = a[0] == 0 ? 0 : start; i < n;)
  {
    while (i < n && a[i]) i ++;
    if (i >= n) break;
    while (i < n && !a[i]) i ++;
    c1 += y;
  }
  if (ones == n) c1 = 0;
  c2 = y;
  for (int i = a[0] == 1 ? start : 0; i < n;)
  {
    while (i < n && !a[i]) i ++;
    while (i < n && a[i]) i ++;
    if (i >= n) break;
    c2 += x;
  }

  printf("%lld\n", min(c1, c2));

  return(0);
}
/*
5 1 1
101
*/