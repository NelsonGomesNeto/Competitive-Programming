#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e9; lli n;
vector<int> digits;

lli memo[10][10][10];
lli solve(int i = 0, int carry1 = 0, int carry2 = 0)
{
  if (i == digits.size()) return carry1 == 0 && carry2 == 0;
  lli &ans = memo[i][carry1][carry2];
  if (ans != -1) return ans;

  ans = 0;
  for (int d1 = 0; d1 <= 9; d1++)
    for (int d2 = 0; d2 <= 9; d2++)
      if ((d1 + d2 + carry1) % 10 == digits[i])
        ans += solve(i + 1, carry2, (d1 + d2 + carry1) / 10);

  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld", &n);
    digits.clear();
    lli aux = n;
    while (aux)
    {
      digits.push_back(aux % 10);
      aux /= 10;
    }

    memset(memo, -1, sizeof(memo));
    lli ans = solve() - 2;
    printf("%lld\n", ans);
  }
  return 0;
}