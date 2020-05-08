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
const lli maxA = 360e9;
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

struct Block { lli slices, cuts; };
unordered_map<fraction, Block, hash_function<fraction>> cnt;

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

    for (lli slice = 1; slice <= d; slice++)
      for (int i = 0; i < n; i++)
      {
        fraction f = fraction(a[i], slice);
        if (!cnt.count(f)) cnt[f] = Block{0, 0};
        if (cnt[f].slices >= d) continue;
        cnt[f].slices += slice;
        cnt[f].cuts += slice - 1;
      }

    lli ans = d - 1;
    for (auto &p: cnt)
    {
      lli totalSlices = 0;
      for (int i = n - 1; i >= 0 && totalSlices < d; i--)
      {
        lli slices = a[i] * p.first.divisor / p.first.numerator;
        if (slices == 0) break;
        totalSlices += slices;
      }
      if (totalSlices < d) continue;

      DEBUG printf("\t%lld / %lld - %lld %lld\n", p.first.numerator, p.first.divisor, p.second.slices, p.second.cuts);
      if (p.second.slices == d) ans = min(ans, p.second.cuts);
      else if (p.second.slices > d) ans = min(ans, p.second.cuts + (d - p.second.slices) + 1);
      else if (p.second.slices < d) ans = min(ans, p.second.cuts + (d - p.second.slices));
    }
    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}