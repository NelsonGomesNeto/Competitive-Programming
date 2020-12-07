#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int n;
int a[maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf("%d", &a[i]);

  int ans = 1e9;
  for (int i = 0; i < n; i ++)
  {
    int now = 0;
    for (int j = 0; j < n; j ++)
      now += abs(a[i] - a[j]) & 1;
    ans = min(ans, now);
  }
  printf("%d\n", ans);

  return(0);
}