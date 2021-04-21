#include <bits/stdc++.h>
#define DEBUG if(0)
#define REC if (1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, k; lli a, b;
lli p[maxN];
lli smallestSuffixSum[maxN + 1];

int loks, lons, hiks, hins;
vector<lli> los[maxN], his[maxN];
void calcHalf(int ns, vector<lli> arr[], lli limit)
{
  for (int bitmask = 0, end = 1 << ns; bitmask < end; bitmask++)
  {
    int has = __builtin_popcount(bitmask);
    if (has <= k)
    {
      lli sum = 0;
      for (int j = 0; j < ns; j++)
        if (bitmask & (1 << j))
          sum += p[j];

      if (sum + smallestSuffixSum[k - has] <= limit)
        arr[has].push_back(sum);
    }
  }

  for (int i = 0; i <= k; i++)
    sort(arr[i].begin(), arr[i].end());
}
void lolHalf(int ni, vector<lli> arr[], lli limit, lli sum = 0, int chosen = 0)
{
  if (chosen > k) return;
  // if (sum + smallestSuffixSum[k - chosen] > limit) return;

  if (ni < 0)
  {
    if (sum + smallestSuffixSum[k - chosen] <= limit)
      arr[chosen].push_back(sum);
    return;
  }

  lolHalf(ni - 1, arr, limit, sum, chosen);
  lolHalf(ni - 1, arr, limit, sum + p[ni], chosen + 1);
}

int binarySearch(int ki, lli base, lli limit)
{
  if (his[ki].empty()) return 0;
  // DEBUG printf("\t%d %lld %d | %d\n", ki, base, upperBound, (int)his[ki].size());
  int lo = 0, hi = his[ki].size() - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (base + his[ki][mid] <= limit) lo = mid;
    else hi = mid - 1;
  }
  return base + his[ki][lo] <= limit ? lo + 1 : 0;
}

// calculates the amount of ways to choose k numbers whose sum is <= limit
lli prefix(lli hi, lli lo)
{
  lli ans = 0;
  for (int i = 0; i <= min(k, lons); i++)
  {
    DEBUG printf("loks: %d, losSize: %d\n", i, (int)los[i].size());
    for (lli x: los[i])
      if (x <= hi)
      {
        int toAdd = binarySearch(k - i, x, hi);
        int toRem = x <= lo ? binarySearch(k - i, x, lo) : 0;
        DEBUG printf("\t%d %d | %lld | %d %d %d\n", i, k - i, x, (int)his[k - i].size(), toAdd, toRem);
        ans += toAdd - toRem;
      }
  }
  return ans;
}

void precalc(lli limit = b)
{
  lons = n >> 1;
  hins = (n + 1) >> 1;
  for (int i = 0; i <= k; i++)
    los[i].clear(), his[i].clear();

  sort(p, p+n, greater<lli>());
  reverse(p, p+hins);
  for (int i = 0; i < hins; i++)
    smallestSuffixSum[i + 1] = smallestSuffixSum[i] + p[i];

  sort(p, p+n, less<lli>());
  REC
    lolHalf(lons - 1, los, limit);
  else
    calcHalf(lons, los, limit);


  sort(p, p+n, less<lli>());
  for (int i = 0; i < lons; i++)
    smallestSuffixSum[i + 1] = smallestSuffixSum[i] + p[i];

  sort(p, p+n, greater<lli>());
  REC
    lolHalf(hins - 1, his, limit);
  else
    calcHalf(hins, his, limit);

  REC {
    for (int i = 0; i <= min(k, lons); i++)
      sort(los[i].begin(), los[i].end());
    for (int i = 0; i <= min(k, hins); i++)
      sort(his[i].begin(), his[i].end());
  }
}

int main()
{
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i++)
    scanf("%lld", &p[i]);
  scanf("%lld %lld", &a, &b);

  precalc();

  DEBUG {
    sort(p, p+n, less<lli>());
    for (int i = 0; i < n; i++)
      printf("%lld%c", p[i], i < n - 1 ? ' ' : '\n');
  }

  lli ans = prefix(b, a - 1);
  printf("%lld\n", ans);

  return 0;
}