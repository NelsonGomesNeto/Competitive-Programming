#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4; int n;
int a[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      int curr = a[i];
      for (int j = i; j < n; j++)
      {
        curr = min(curr, a[j]);
        ans = max(ans, curr * (j - i + 1));
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}