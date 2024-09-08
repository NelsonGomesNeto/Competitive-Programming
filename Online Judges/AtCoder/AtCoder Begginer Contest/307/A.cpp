#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10;
int n;
int a[7*maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < 7*n; ++i)
      scanf("%d", &a[i]);

    vector<int> ans(n, 0);
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < 7; ++j)
        ans[i] += a[i*7 + j];
    }

    for (int i = 0; i < n; ++i)
      printf("%d%c", ans[i], i + 1 < n ? ' ' : '\n');
  }
  return 0;
}
