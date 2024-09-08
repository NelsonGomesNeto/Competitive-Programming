#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3;
int cnt[2][6];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    memset(cnt, 0, sizeof(cnt));

    for (int i = 0; i < n; i++)
    {
      int a, b; scanf("%d %d", &a, &b);
      cnt[0][a - 1]++, cnt[1][b - 1]++;
    }

    printf("%d\n", 1 + (cnt[0][5] < cnt[1][5]));
  }
  return 0;
}