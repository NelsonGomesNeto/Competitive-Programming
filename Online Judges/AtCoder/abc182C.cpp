#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli maxN = 1e18; lli n;
const int inf = 20;
vector<int> digits;

int solve(int i = 0, int sum = 0)
{
  if (i == digits.size()) return sum % 3 == 0 ? 0 : inf;

  int ans = min(solve(i + 1, sum) + 1, solve(i + 1, sum + digits[i]));
  return ans;
}

int main()
{
  while (scanf("%lld", &n) != EOF)
  {
    digits.clear();
    lli aux = n;
    while (aux)
    {
      digits.push_back(aux % 10);
      aux /= 10;
    }

    int ans = solve();
    ans = ans >= digits.size() ? -1 : ans;
    printf("%d\n", ans);
  }
  return 0;
}