#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; int p;
int a[maxN];

int main()
{
  while (~scanf("%d %d", &n, &p))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    int ans = 0;
    for (int i = 0; i < n; i++)
      ans += a[i] < p;
    printf("%d\n", ans);
  }
  return 0;
}