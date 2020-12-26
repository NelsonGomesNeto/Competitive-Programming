#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e2; int n, k;
const lli inf = 1e18;
lli h[maxN];

/* Observations:
  Notice that the amount of movements for a range [lo : hi] is:
  sum max(0LL, h[i] - h[i - 1]) for all i from lo to hi
    notice that for the first iteration: h[i - 1] should be 0

  So you can remove elements from a range
*/

lli memo[maxN][maxN + 1][maxN + 1];
lli solve(int i = 0, int prvPos = -1, int available = k)
{
  if (i == n) return 0;
  lli &ans = memo[i][prvPos + 1][available];
  if (ans != -1) return ans;

  ans = solve(i + 1, i, available) + (prvPos == -1 ? h[i] : max(0LL, h[i] - h[prvPos]));
  if (available)
    ans = min(ans, solve(i + 1, prvPos, available - 1));
  return ans;
}

lli brute(vector<lli> nums, int sz)
{
  lli cnt = 0;
  while (*max_element(nums.begin(), nums.begin()+sz))
  {
    for (int i = 0; i < sz; i++)
      if (nums[i])
      {
        int j = i;
        while (j + 1 < sz && nums[j + 1]) j++;

        lli mn = *min_element(nums.begin()+i, nums.begin()+j+1);
        cnt += mn;
        for (int k = i; k <= j; k++)
          nums[k] -= mn;

        i = j;
      }
  }
  return cnt;
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &h[i]);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}