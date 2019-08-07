#include <bits/stdc++.h>
using namespace std;

int n, angles[15], sum;
int memo[15][180*15 + 1];

bool can(int i, int angle)
{
  if (i == n) return((angle % 360) == 0);
  if (memo[i][abs(angle)] == -1)
  {
    bool ans = can(i + 1, angle + angles[i]);
    ans = max(ans, can(i + 1, angle - angles[i]));
    memo[i][abs(angle)] = ans;
  }
  return(memo[i][abs(angle)]);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &angles[i]);
    sum += angles[i];
  }

  if (sum & 1) printf("NO\n");
  else
  {
    memset(memo, -1, sizeof(memo));
    printf("%s\n", can(0, 0) ? "YES" : "NO");
  }

  return(0);
}