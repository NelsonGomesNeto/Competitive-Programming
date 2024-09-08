#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli n;
vector<int> digits;

const int maxD = 20;
int memo[maxD][maxD];
int solve(int i = 0, int rem = 0, lli num = 0)
{
  if (i == digits.size()) return num % 25 == 0 ? rem : 1e9;
  int &ans = memo[i][rem];
  if (ans != -1) return ans;

  ans = solve(i + 1, rem + 1, num);
  ans = min(ans, solve(i + 1, rem, num * 10 + digits[i]));

  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld", &n);
    lli aux = n;
    digits.clear();
    while (aux)
    {
      digits.push_back(aux % 10);
      aux /= 10;
    }
    // reverse(digits.begin(), digits.end());

    // memset(memo, -1, sizeof(memo));
    // int ans = solve();

    int ans = digits.size();
    vector<vector<int>> ends = {{2, 5}, {5, 0}, {7, 5}, {0, 0}};

    for (vector<int> e: ends)
    {
      int p = e.size() - 1;
      for (int i = 0; i < digits.size(); i++)
      {
        if (digits[i] == e[p])
          p--;
        DEBUG printf("\t%d %d\n", i, p);
        if (p < 0)
          ans = min(ans, i - 2 + 1);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
