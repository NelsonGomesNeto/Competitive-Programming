#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  We want to count the number of ways we can build a valid piece:
    A piece of n blocks and base length b is valid iff:
      It uses all blocks
      All stacks have at least one block (over the whole base)
      Stacks heights are from left to right increasing and then decreasing
        Same height is allowed for both increasing and decreasing

  Suppose you have n blocks and base length b (f(n, b)), what can you do?
    You could place b blocks over the whole base: f(n - b, b)
      You would continue with the same base b but would have spent b blocks
    You could retry the same, but without the leftmost block on the base: f(n, b - 1)
      Notice that we're not placing the blocks yet, we're just asking the same original
      question, but with a smaller base.
    You could retry the same, but without the rightmost block on the base: f(n, b - 1)
      Notice that removing the leftmost and then removing the rightmost is the same
      as removing the rightmost and then removing the leftmost. So we need to disconsider
      once the case in which we've removed the leftmost and the rightmost.
  The final recurrence will be: f(n, b) = f(n - b, b) + 2*f(n, b - 1) - f(n, b - 2)
*/

const int maxN = 5e3 + 1; int s, b;
const int mod = 1e9 + 7;

int memo[maxN][maxN];
// n == blocks, base = base length
int solve(int n = b - s, int base = s) // O(S * B)
{
  if (base <= 0) return 0;
  if (memo[n][base] != -1) return memo[n][base];
  if (!n || base == 1) return memo[n][base] = 1;

  int ans = (2LL * solve(n, base - 1) % mod - solve(n, base - 2) + mod) % mod;
  if (n >= base)
    ans = (ans + solve(n - base, base)) % mod;
  return memo[n][base] = ans;
}

int solve2(int n = b, int base = s) // O(S^2 * B)
{
  if (memo[n][base] != -1) return memo[n][base];
  if (!n || base == 1) return memo[n][base] = 1;

  int ans = 0;
  for (int i = 1; i <= base && n - i >= 0; i ++)
    ans = (ans + (lli)(base - i + 1) * solve2(n - i, i) % mod) % mod;
  return memo[n][base] = ans;
}

int main()
{
  while (scanf("%d %d", &s, &b) != EOF)
  {
    memset(memo, -1, sizeof(memo));
    printf("%d\n", solve());
  }
  return 0;
}