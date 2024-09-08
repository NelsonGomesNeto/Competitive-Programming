#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5;
int n;
int socks[maxN];
map<int, int> cnt;

int main()
{
  while (~scanf("%d", &n))
  {
    cnt.clear();
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &socks[i]);
      ++cnt[socks[i]];
    }

    int ans = 0;
    for (const auto& [color, c] : cnt)
    {
      ans += c >> 1;
    }
    printf("%d\n", ans);
  }
  return 0;
}
