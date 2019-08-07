#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
int a[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);
    sort(a, a+n);

    if (n == 2)
      printf("0\n");
    else
    {
      int base = a[n - 2];
      int ans = min(base - 1, n - 2);
      printf("%d\n", ans);
    }
  }
  return(0);
}
