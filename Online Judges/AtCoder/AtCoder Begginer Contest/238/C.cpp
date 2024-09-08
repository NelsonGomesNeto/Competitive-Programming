#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxD = 20;
const lli mod = 998244353;
lli n;
vector<int> digits;
vector<lli> pot;
vector<int> mult;

lli memo[maxD][10][2][2];
lli solve(int i = 0, int prv = 0, bool equal = true, bool started = false)
{
  if (i == digits.size()) return 0;
  lli &ans = memo[i][10][equal][started];
  // if (ans != -1) return ans;

  ans = 0;
  for (int d = equal ? digits[i] : 9; d >= 0; d--)
  {
    // ans = (ans + max(1, d)*solve(i + 1, d, equal && d == digits[i], started || d != 0)
    //            + max(0, d-1+(i == digits.size()-1)+started)*pot[i]*(started || d != 0)) % mod;
    ans = (ans + solve(i + 1, d, equal && d == digits[i], started || d != 0)
               + d * pot[i] % mod) % mod;
  }
  return ans;
}

int main()
{
  mult.push_back(1);
  mult.push_back(1);
  for (int i = 2; i <= 10; i++)
    mult.push_back(mult.back() + i);

  while (~scanf("%lld", &n))
  {
    lli aux = n, p = 1;
    digits.clear(), pot.clear();
    while (aux)
    {
      digits.push_back(aux % 10), pot.push_back(p);
      aux /= 10, p = p * 10 % mod;
    }
    reverse(digits.begin(), digits.end());
    reverse(pot.begin(), pot.end());

    memset(memo, -1, sizeof(memo));
    lli ans = (solve() + mod) % mod;
    printf("%lld %lld\n", n, ans);
  }
  return 0;
}