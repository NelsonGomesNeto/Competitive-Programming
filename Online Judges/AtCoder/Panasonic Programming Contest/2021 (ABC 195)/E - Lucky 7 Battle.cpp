#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <assert.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char s[maxN + 1], x[maxN + 1];
int nums[maxN];

// 1 Aoki, -1 Takahashi
int digits[6] = {1, 3, 2, 6, 4, 5};
int memo[maxN][7];
int solve(int i = 0, int curr = 0)
{
  if (i == n)
    return curr == 0 ? -1 : 1;

  int &ans = memo[i][curr];
  if (ans != -2)
    return ans;

  int zero = solve(i + 1, curr);
  int other = solve(i + 1, (curr + nums[i]) % 7);
  if (x[i] == 'A')
    ans = max(zero, other);
  else // Takahashi
    ans = min(zero, other);
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", s);
    for (int i = 0; i < n; i++)
      nums[i] = (int)(s[i] - '0') * digits[(n - 1 - i) % 6];
    scanf(" %s", x);
    DEBUG printf("%d - %s - %s\n", n, s, x);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < 7; j++)
        memo[i][j] = -2;
    int ans = solve();
    printf("%s\n", ans == 1 ? "Aoki" : "Takahashi");
  }
  return 0;
}