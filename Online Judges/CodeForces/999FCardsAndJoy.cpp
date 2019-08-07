#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;
const int maxNum = 1e5; int h[10], n, k;
lli dp[501][5001];

lli solve(int qFav, int qCard)
{
  if (!qCard || !qFav) return(0);

  if (dp[qFav][qCard] == -1)
  {
    lli ans = 0;
    for (int i = 1; i <= k; i ++)
      if (qCard - i >= 0)
        ans = max(ans, h[i - 1] + solve(qFav - 1, qCard - i));
    dp[qFav][qCard] = ans;
  }
  return(dp[qFav][qCard]);
}

int main()
{
  scanf("%d %d", &n, &k); int cards = n * k;
  int card[cards]; for (int i = 0; i < cards; i ++) scanf("%d", &card[i]);
  set<int> allFav;
  int f[n];
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &f[i]);
    allFav.insert(f[i]);
  }
  for (int i = 0; i < k; i ++) scanf("%d", &h[i]);

  int qCard[maxNum + 1], qFav[maxNum + 1];
  memset(qCard, 0, sizeof(qCard)); memset(qFav, 0, sizeof(qFav));
  for (int i = 0; i < cards; i ++) qCard[card[i]] ++;
  for (int i = 0; i < n; i ++) qFav[f[i]] ++;

  lli ans = 0; memset(dp, -1, sizeof(dp));
  for (auto i: allFav)
  {
    DEBUG printf("card: %d, fav: %d, available: %d\n", i, qFav[i], qCard[i]);
    ans += solve(qFav[i], qCard[i]);
  }
  printf("%lld\n", ans);

  return(0);
}