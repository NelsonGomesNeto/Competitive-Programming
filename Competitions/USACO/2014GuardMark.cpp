#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  The first thing to notice is that there's an optimal order for the cows
  This order will allow us to use a greedy strategy
    c[i].w + c[i].s > c[i+1].w + c[i+1].s, for all i
    It's proven that following this order, you will be able to put
    the maximum amount of cows on top of each order. Of course which cow
    will be discarted isn't known, but they sure will follow this order

  Now, we can try every possible set of cows using bitmask
    The bitmask will be an integer, where the i-th bit represents wheter
    or not the i-th cow is present in that set

  memo[bitmask] will store the minimum strenght available, set all to inf
  for every bitmask in [1, (1 << n) - 1]:
    height = 0
    for j in [0, n - 1]: (remember this is the optimal order)
      if (j-th cow is present in bitmask and c[j].w <= memo[bitmask]):
        memo[bitmask] = min(memo[bitmask] - c[j].w, c[j].s)
        height += c[j].h
    if (height >= H): ans = max(ans, memo[bitmask])
*/

const int maxN = 20; int n; lli H;
const lli inf = 1e18;
struct Cow
{
  lli height, weight, strength;
  bool operator<(const Cow &c) const { return(weight + strength < c.weight + c.strength); }
};
Cow cows[maxN];
lli memo[1 << maxN];

int main()
{
  FILE *input = fopen("guard.in", "rb");
  FILE *output = fopen("guard.out", "wb");

  fscanf(input, "%d %lld", &n, &H);
  for (int i = 0; i < n; i ++)
    fscanf(input, "%lld %lld %lld", &cows[i].height, &cows[i].weight, &cows[i].strength);

  sort(cows, cows+n); reverse(cows, cows+n);
  lli ans = -1;
  for (int bitmask = 1, end = 1 << n; bitmask < end; bitmask ++)
  {
    memo[bitmask] = inf; lli height = 0;
    for (int j = 0; j < n; j ++)
      if ((bitmask & (1 << j)) && cows[j].weight <= memo[bitmask])
        memo[bitmask] = min(memo[bitmask] - cows[j].weight, cows[j].strength), height += cows[j].height;
    if (height >= H) ans = max(ans, memo[bitmask]);
  }
  if (ans == -1) fprintf(output, "Mark is too tall\n");
  else fprintf(output, "%lld\n", ans);

  return(0);
}