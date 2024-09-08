#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 300, maxW = 1e6; int n, w;
int a[maxN];
bool has[maxW + 1];

int main()
{
  while (~scanf("%d %d", &n, &w))
  {
    memset(has, false, sizeof(has));
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    for (int i = 0; i < n; ++i)
    {
      for (int j = i + 1; j < n; ++j)
      {
        for (int k = j + 1; k < n; ++k)
        {
          int sum = a[i] + a[j] + a[k];
          if (sum <= maxW) has[sum] = true;
        }
        int sum = a[i] + a[j];
        if (sum <= maxW) has[sum] = true;
      }
      int sum = a[i];
      if (sum <= maxW) has[sum] = true;
    }

    int ans = 0;
    for (int i = 0; i <= w; ++i) ans += has[i];
    printf("%d\n", ans);
  }
  return 0;
}
