#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int n;
int b[maxN], a[maxN];

int main()
{
  scanf("%d", &n);

  for (int i = 0; i < n - 1; i ++)
    scanf("%d", &b[i]);

  a[0] = b[0]; a[n - 1] = b[n - 2];
  for (int i = 1; i < n - 1; i ++)
    a[i] = min({b[i - 1], b[i]});

  int ans = 0;
  for (int i = 0; i < n; i ++)
    ans += a[i];

  printf("%d\n", ans);

  return(0);
}