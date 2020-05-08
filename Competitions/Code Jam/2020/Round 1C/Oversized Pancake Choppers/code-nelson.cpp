#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli lcm(lli a, lli b)
{
  return a / __gcd(a, b) * b;
}

const int maxN = 1e4, maxD = 51; int n, d;
lli a[maxN];

template <typename General>
struct hash_function {
  size_t operator()(General const& c) const {
    size_t hashValue = 0;
    hashValue += hash<int>() (c.numerator);
    hashValue += hash<int>() (c.divisor);
    return(hashValue);
  }
};

struct fraction
{
  lli numerator, divisor;
  fraction(lli numerator, lli divisor)
  {
    lli g = __gcd(numerator, divisor);
    this->numerator = numerator / g;
    this->divisor = divisor / g;
  }
  bool operator<(const fraction &other) const
  {
    // be very careful not to overflow here
    lli l = lcm(divisor, other.divisor);
    return numerator * (l / divisor) < other.numerator * (l / other.divisor);
  }
  bool operator==(const fraction &other) const
  {
    return numerator == other.numerator && divisor == other.divisor;
  }
};
struct Block
{
  vector<int> slices;
  set<int> indexes;
  lli leftOvers;
};
unordered_map<fraction, Block, hash_function<fraction>> cnt;

int memo[maxN][maxD];
int knapsack(Block &block, int i = 0, int b = d)
{
  if (b <= 0) return 0;
  if (i == block.slices.size()) return block.leftOvers >= b ? b : maxD;
  if (memo[i][b] != -1) return memo[i][b];
  int ans = maxD;
  for (int j = block.slices[i]; j >= 0; j--)
    ans = min(ans, knapsack(block, i + 1, b - j) + j - (j == block.slices[i]));
  return memo[i][b] = ans;
}

int solve()
{
  int ans = d - 1;
  for (auto p: cnt)
  {
    int sum = 0;
    for (int i = 0; i < p.second.slices.size(); i++)
    {
      for (int j = 0; j <= d; j++)
        memo[i][j] = -1;
      sum += p.second.slices[i];
    }
    ans = min(ans, knapsack(p.second));
    DEBUG printf("\tfull %lld / %lld (%d, %d, %lld) - %d\n",
      p.first.numerator, p.first.divisor,
      (int)p.second.slices.size(), sum, p.second.leftOvers,
      knapsack(p.second)
    );
  }
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    cnt.clear();
    scanf("%d %d", &n, &d);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    sort(a, a+n);
    for (int i = 0; i < n; i++)
      for (lli slice = 1; slice <= d; slice++)
      {
        fraction f = fraction(a[i], slice);
        if (!cnt.count(f)) cnt[f] = Block{};
        cnt[f].slices.push_back(slice);
        cnt[f].indexes.insert(i);
      }

    for (auto &p: cnt)
    {
      p.second.leftOvers = 0;
      for (int i = n - 1; i >= 0 && p.second.leftOvers < d; i--)
        if (!p.second.indexes.count(i))
          p.second.leftOvers += p.first.divisor * a[i] / p.first.numerator;
    }

    int ans = solve();
    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}