#include <bits/stdc++.h>
using namespace std;

char s[100005]; int dp[100005];

int main()
{
  memset(dp, 0, sizeof(dp));
  scanf("%s", s);
  for (int i = 1; s[i]; i ++)
    dp[i] = dp[i - 1] + (s[i - 1] == s[i]);

  int l, h, queries;
  scanf("%d", &queries);
  while (queries -- > 0)
  {
    scanf("%d %d", &l, &h); l --; h --;
    printf("%d\n", dp[h] - dp[l]);
  }
  return(0);
}