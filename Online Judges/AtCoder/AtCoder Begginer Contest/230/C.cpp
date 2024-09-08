#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
max(1, 1) <= k <= min(N, N)
  
  paint(k, k)
*/

const int maxN = 3e5; lli N, a, b, p, q, r, s;
string ans[maxN];

int main()
{
  int pundim = 0;
  while (~scanf("%lld %lld %lld", &N, &a, &b))
  {
    scanf("%lld %lld %lld %lld", &p, &q, &r, &s);
    if (pundim++) printf("---------\n");

    int n = q - p + 1, m = s - r + 1;
    for (int i = 0; i < n; i++)
    {
      ans[i].clear();
      ans[i].resize(m, '.');
    }

    for (lli i = p; i <= q; i++)
      for (lli j = r; j <= s; j++)
        if (i + j == a + b || i - j == a - b)
          ans[i - p][j - r] = '#';

    for (int i = 0; i < n; i++)
      printf("%s\n", ans[i].c_str());
  }
  return 0;
}