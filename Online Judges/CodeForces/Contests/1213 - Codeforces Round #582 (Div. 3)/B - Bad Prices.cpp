#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 15e4; int n;
int a[maxN], rightToLeft[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);

    rightToLeft[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; i --)
      rightToLeft[i] = min(rightToLeft[i + 1], a[i]);

    int ans = 0;
    for (int i = 0; i < n - 1; i ++)
      ans += a[i] > rightToLeft[i + 1];
    printf("%d\n", ans);
  }
  return(0);
}