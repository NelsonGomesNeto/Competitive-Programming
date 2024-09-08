#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2;
int a, b, c;

double memo[maxN][maxN][maxN];
double solve(vector<int> coins = {a, b, c})
{
  DEBUG printf("\t%d %d %d\n", coins[0], coins[1], coins[2]);
  if (*max_element(coins.begin(), coins.end()) == 100) return 0;
  double &ans = memo[coins[0]][coins[1]][coins[2]];
  if (ans != -1) return ans;

  ans = 0;
  double sumCoins = coins[0] + coins[1] + coins[2];
  for (int i = 0; i < 3; i++)
  {
    double p = coins[i] / sumCoins;
    coins[i]++;
    ans += p * (1 + solve(coins));
    coins[i]--;
  }
  return ans;
}

int main()
{
  while (scanf("%d %d %d", &a, &b, &c) != EOF)
  {
    for (int i = 0; i < maxN; i++)
      for (int j = 0; j < maxN; j++)
        for (int k = 0; k < maxN; k++)
          memo[i][j][k] = -1;
    double ans = solve();
    printf("%.15lf\n", ans);
  }
  return 0;
}