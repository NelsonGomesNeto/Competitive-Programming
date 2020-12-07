#include <bits/stdc++.h>
using namespace std;
int n, a, b, c;
int dp[5000], inf = 10000;

int cut(int size)
{
  if (dp[size] == -1)
  {
    int best = (size == a || size == b || size == c) ? 1 : -inf, i;
    for (i = 1; i < size; i ++)
      best = max(best, cut(i) + cut(size - i));
    dp[size] = best;
  }
  return(dp[size]);
}

int main()
{
  scanf("%d %d %d %d", &n, &a, &b, &c);

  memset(dp, -1, sizeof(dp));
  int answer = cut(n);

  printf("%d\n", answer);

  return(0);
}