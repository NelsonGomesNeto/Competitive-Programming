#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 20, maxS = 163;
// must be greater then n, but digit sum must be smaller then s
lli n, s;
vector<int> num;
int memo[maxN][2][maxS];
vector<int> res;
bool solve(int i = 18, bool greater = false, int digitSum = 0)
{
  if (digitSum > s) return false;
  if (i == -1) return greater;
  if (memo[i][greater][digitSum] != -1) return memo[i][greater][digitSum];

  bool ans = false;
  for (int d = greater ? 0 : num[i]; d <= 9; d++)
  {
    ans = max(ans, solve(i - 1, greater | (d > num[i]), digitSum + d));
    if (ans)
    {
      res.push_back(d);
      break;
    }
  }
  return memo[i][greater][digitSum] = ans;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 0; tt < t; tt++)
    {
      scanf("%lld %lld", &n, &s);

      num.clear();
      lli aux = n - 1;
      while (aux)
      {
        num.push_back(aux % 10);
        aux /= 10;
      }
      while (num.size() <= 18)
        num.push_back(0);
      // reverse(num.begin(), num.end());

      memset(memo, -1, sizeof(memo)), res.clear();
      bool ans = solve();
      reverse(res.begin(), res.end());
      lli a = 0;
      for (int i = 0; i < res.size(); i++)
        a = a*10LL + res[i];
      printf("%lld\n", a - n);
    }
  return 0;
}