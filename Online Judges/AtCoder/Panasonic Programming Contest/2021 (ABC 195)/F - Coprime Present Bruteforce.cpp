#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxDelta = 73;
bool gcdTable[maxDelta][maxDelta];

lli a, b;
vector<lli> divisibleBy2And3[2][2];
// 0 0 - (n % 2 != 0) e (n % 3 != 0)
// 0 1 - (n % 2 != 0) e (n % 3 == 0)
// 1 0 - (n % 2 == 0) e (n % 3 != 0)
// 1 1 - (n % 2 == 0) e (n % 3 == 0)
deque<lli> curr;
lli solve2()
{
  // 1 - choose none
  // [0][1].size - from [0][1]
  // [1][0].size - from [1][0]
  // [0][1].size * [1][0].size - from [0][1] and [1][0]
  // [1][1].size - from [1][1]

  lli ans = 1;

  deque<lli> valids[2][2];
  for (int i = 0; i < 2; i++)
    for (int j = i == 0; j < 2; j++)
    {
      for (lli num: divisibleBy2And3[i][j])
      {
        bool valid = true;
        for (lli c: curr)
          if (gcdTable[num - a][c - a]) 
          {
            valid = false;
            break;
          }
        if (valid)
          valids[i][j].push_back(num);
      }
      ans += valids[i][j].size();
    }

  lli total0110 = 0;
  for (lli num01: valids[0][1])
    for (lli num10: valids[1][0])
      if (!gcdTable[num01 - a][num10 - a])
        total0110++;
  ans += total0110;

  return ans;
}
lli solve(int i = 0)
{
  if (i == divisibleBy2And3[0][0].size())
    return solve2();

  // not put:
  lli total = solve(i + 1);

  // put:
  lli toAdd = divisibleBy2And3[0][0][i];
  for (lli num: curr)
    if (gcdTable[toAdd - a][num - a])
      return total;
  curr.push_back(toAdd);
  total += solve(i + 1);
  curr.pop_back();

  return total;
}

int main()
{
  while (~scanf("%lld %lld", &a, &b))
  {
    for (lli i = a; i <= b; i++)
      for (lli j = a; j <= b; j++)
        gcdTable[i - a][j - a] = gcd(i, j) != 1;

    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++)
        divisibleBy2And3[i][j].clear();
    for (lli i = a; i <= b; i++)
    {
      int by2 = ~i & 1;
      int by3 = i % 3 == 0;
      divisibleBy2And3[by2][by3].push_back(i);
    }

    curr.clear();
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}