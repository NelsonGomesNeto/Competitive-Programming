#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int a[n], sum = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  sort(a, a+n);

  int now = 0, c = 0;
  for (int i = n - 1; i >= 0; i --)
  {
    now += a[i]; c ++;
    if (sum - now < now) break;
  }

  printf("%d\n", c);

  return(0);
}