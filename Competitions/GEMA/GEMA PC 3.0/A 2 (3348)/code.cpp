#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100 + 1, maxX = 15 + 1;
/*
  Targets <= 100
  Coins quantity sum <= 45
  Same as before, but with simple DP
*/

int targets[3];
struct Coin
{
  int quantity, value;
  void read() { scanf("%d %d", &quantity, &value); }
};
Coin coins[3];

int memo[3][maxN][maxX][maxX][maxX];
bool solve(int i = 0, int left = targets[0])
{
  if (left < 0) return false;
  if (left == 0) return i == 2 ? true : solve(i + 1, targets[i + 1]);
  int &ans = memo[i][left][coins[0].quantity][coins[1].quantity][coins[2].quantity];
  if (ans != -1)
    return ans;

  for (int j = 0; j < 3; j++)
    if (coins[j].quantity)
    {
      coins[j].quantity--;
      if (solve(i, left - coins[j].value))
        return ans = true;
      coins[j].quantity++;
    }

  return ans = false;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d %d", &targets[0], &targets[1], &targets[2]);
      for (int i = 0; i < 3; i++)
        coins[i].read();

      memset(memo, -1, sizeof(memo));
      bool can = solve();
      printf("%s\n", can ? "Yes" : "No");
    }
  return 0;
}