#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int a1, a2, k1, k2, n;
  scanf("%d %d %d %d %d", &a1, &a2, &k1, &k2, &n);
  if (k1 < k2)
    swap(k1, k2), swap(a1, a2);

  int maximum = n / k2;
  if (maximum > a2)
  {
    maximum = a2;
    maximum += min(a1, (n - maximum * k2) / k1);
  }
  int minimum = 0;
  while ((a1 || a2) && n > a1 * (k1 - 1) + a2 * (k2 - 1))
  {
    minimum ++;
    if (a1) n -= k1, a1 --;
    else n -= k2, a2 --;
  }
  printf("%d %d\n", minimum, maximum);

  return(0);
}