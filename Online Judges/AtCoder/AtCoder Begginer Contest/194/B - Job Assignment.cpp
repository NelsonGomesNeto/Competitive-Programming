#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    int a[n], b[n];
    for (int i = 0; i < n; i++)
      scanf("%d %d", &a[i], &b[i]);

    int ans = 1e9;
    for (int i = 0; i < n; i++)
      ans = min(ans, a[i] + b[i]);
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        ans = min({ans, max(a[i], b[j]), max(b[i], a[j])});
    printf("%d\n", ans);
  }
  return 0;
}