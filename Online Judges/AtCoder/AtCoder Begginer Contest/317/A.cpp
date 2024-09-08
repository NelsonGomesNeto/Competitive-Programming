#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n, h, x;
int p[maxN];

int main()
{
  while (~scanf("%d %d %d", &n, &h, &x)) {
    for (int i = 0; i < n; ++i)
      scanf("%d", &p[i]);

    int ans = -1;
    for (int i = 0; i < n; ++i)
      if (h + p[i] >= x) {
        ans = i;
        break;
      }
    printf("%d\n", ans + 1);
  }
  return 0;
}
