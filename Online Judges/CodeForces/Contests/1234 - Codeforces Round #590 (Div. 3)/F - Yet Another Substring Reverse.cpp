#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  We can represent a substring as a bitmask, since it's only allowed to have
  a character at most once.

  The length of the biggest substring is 20. So we can iterate through the
  string, find all valid substrings and save their bitmask representation.

  We can always join two substrings with reverse operation. So, we just need to
  find the best valid substring for each bitmask we've preprocessed.
  The best possible substring of a bitmask is the complement of it, but it might
  not be in the string... So, we build bottom-up the best existing bitmask:
    for bitmask in [0 : 1 << maxAl)
      memo[bitmask] = max(memo[bitmask], memo[bitmask ^ (1 << j)])
    (This way, memo[bitmask] of a bitmask that doesn't exist in the string will
    hold the maximum of all combinations of its bits)

  So, we iterate again through all bitmasks (present in the string) and:
    ans = max(ans, memo[bitmask] + memo[complement])
*/

const int maxN = 1e6 + 1, maxAl = 20; int n;
char s[maxN];

int memo[1 << maxAl];

int main()
{
  scanf("%s", s); n = strlen(s);

  for (int i = 0; i < n; i ++)
    for (int j = i, bitmask = 0; j < n; j ++)
    {
      if (bitmask & (1 << (s[j] - 'a'))) break;
      bitmask |= (1 << (s[j] - 'a'));
      memo[bitmask] = __builtin_popcount(bitmask);
    }

  for (int bitmask = 0, end = 1 << maxAl; bitmask < end; bitmask ++)
    for (int j = 0; j < 20; j ++)
      if (bitmask & (1 << j))
        memo[bitmask] = max(memo[bitmask], memo[bitmask ^ (1 << j)]);

  int ans = 0;
  for (int bitmask = 0, end = 1 << maxAl; bitmask < end; bitmask ++)
    if (memo[bitmask] == __builtin_popcount(bitmask))
      ans = max(ans, memo[bitmask] + memo[~bitmask & ((1 << maxAl) - 1)]);
  printf("%d\n", ans);

  return 0;
}
