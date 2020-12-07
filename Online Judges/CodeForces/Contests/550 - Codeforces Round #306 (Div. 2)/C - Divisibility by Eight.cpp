#include <bits/stdc++.h>
#define DEBUG if(0)
int dp[100][10][10][10];

int divisibleByEight(int i, int got, int n, char num[], int size)
{
  DEBUG printf("%d %d (%d %d %d)\n", got, n, n / 100, (n / 10) % 10, n % 10);
  if (got && got <= 3 && !(n % 8)) return(n);
  if (i >= size || got > 3) return(-1);
  if (dp[i][n / 100][(n / 10) % 10][n % 10] == -1)
  {
    int ans = divisibleByEight(i + 1, got + 1, n*10 + (num[i] - '0'), num, size);
    if (ans != -1) return(ans);
    ans = divisibleByEight(i + 1, got, n, num, size);
    if (ans != -1) return(ans);
    ans = divisibleByEight(i + 1, 0, 0, num, size);
    if (ans != -1) return(ans);
    dp[i][n / 100][(n / 10) % 10][n % 10] = 0;
  }
  return(-1);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  char num[101]; scanf("%s", num);
  int n = divisibleByEight(0, 0, 0, num, strlen(num));
  if (n == -1) printf("NO\n");
  else printf("YES\n%d\n", n);
  return(0);
}
