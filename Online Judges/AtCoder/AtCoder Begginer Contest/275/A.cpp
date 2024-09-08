#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n;
int h[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &h[i]);
    int ans = max_element(h, h+n) - h + 1;
    printf("%d\n", ans);
  }
  return 0;
}
