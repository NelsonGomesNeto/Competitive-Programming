#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int a, b;
const int maxA = 100, maxB = 1000;
int memo[maxA][maxB + 1];
int solve(int i = 0, int s = 0)
{
  if (s > b) return 0;
  if (i == a) return s == b;
  int &ans = memo[i][s];
  if (ans != -1) return ans;

  ans = 0;
  for (int k = 1; k <= 6; k++)
    ans = max(ans, solve(i + 1, s + k));

  return ans;
}

int main()
{
  while (~scanf("%d %d", &a, &b))
  {
    memset(memo, -1, sizeof(memo));
    printf("%s\n", solve() ? "Yes" : "No");
  }
  return 0;
}