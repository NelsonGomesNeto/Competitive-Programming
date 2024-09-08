#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n;
int a[maxN];
int acc[maxN + 1];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    for (int i = 0; i < n; i++)
      acc[i + 1] = acc[i] + a[i];

    int ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = i; j < n; j++)
      {
        int mid = acc[j + 1] - acc[i];
        int flip = (j - i + 1) - mid;
        ans = max(ans, flip + acc[n] - mid);
      }

    printf("%d\n", ans);
  }
  return 0;
}