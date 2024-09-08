#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 300;
int n, a, b;
int c[maxN];

int main()
{
  while (~scanf("%d %d %d", &n, &a, &b))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &c[i]);

    int ans;
    for (int i = 0; i < n; ++i)
      if (a + b == c[i])
        ans = i;
    printf("%d\n", ans + 1);
  }
  return 0;
}
