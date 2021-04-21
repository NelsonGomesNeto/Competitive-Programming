#include <bits/stdc++.h>
#define DEBUG if(1)
#define REC if (1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, k; lli a, b;
lli p[maxN];
lli biggestSuffixSum[maxN + 1];
lli smallestSuffixSum[maxN + 1];

int loks, lons, hiks, hins;
vector<lli> los[maxN], his[maxN];
void calcHalf(int ns, vector<lli> arr[])
{
  for (int bitmask = 0, end = 1 << ns; bitmask < end; bitmask++)
  {
    int has = __builtin_popcount(bitmask);
    if (has <= k)
    {
      lli sum = 0;
      for (int j = 0; j < ns && sum <= b; j++)
        if (bitmask & (1 << j))
          sum += p[j];
      if (sum + biggestSuffixSum[k - has] >= a && sum + smallestSuffixSum[k - has] <= b)
        arr[has].push_back(sum);
    }
  }
  for (int i = 0; i <= k; i++)
    sort(arr[i].begin(), arr[i].end());
}
void lolHalf (int ni, vector<lli> arr[], lli sum = 0, int chosen = 0)
{
  if (chosen > k) return;

  if (ni < 0)
  {
    if (sum + biggestSuffixSum[k - chosen] >= a && sum + smallestSuffixSum[k - chosen] <= b)
      arr[chosen].push_back(sum);
    return;
  }

  lolHalf(ni - 1, arr, sum, chosen);
  lolHalf(ni - 1, arr, sum + p[ni], chosen + 1);
}

int binarySearch(int ki, lli base, bool upperBound)
{
  // DEBUG printf("\t%d %lld %d | %d\n", ki, base, upperBound, (int)his[ki].size());
  int lo = 0, hi = his[ki].size() - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (base + his[ki][mid] < a) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (base + his[ki][mid] > b) hi = mid;
      else lo = mid + 1;
    }
  }
  if (his[ki].empty()) return 0;

  if (upperBound) return base + his[ki][lo] >= a ? 0 : lo + 1;
  else return base + his[ki][lo] <= b ? 0 : his[ki].size() - lo;
}

int main()
{
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i++)
    scanf("%lld", &p[i]);
  scanf("%lld %lld", &a, &b);

  sort(p, p+n, greater<lli>());
  sort(p, p+n, less<lli>());

  DEBUG {
    sort(p, p+n, less<lli>());
    for (int i = 0; i < n; i++)
      printf("%lld%c", p[i], i < n - 1 ? ' ' : '\n');
  }

  lli ans = 0;
  lons = n >> 1;
  hins = (n + 1) >> 1;


  sort(p, p+n, greater<lli>());
  for (int i = 0; i < hins; i++)
    biggestSuffixSum[i + 1] = biggestSuffixSum[i] + p[i];
  reverse(p, p+hins);
  for (int i = 0; i < hins; i++)
    smallestSuffixSum[i + 1] = smallestSuffixSum[i] + p[i];

  sort(p, p+n, less<lli>());
  REC
    lolHalf(lons - 1, los);
  else
    calcHalf(lons, los);


  sort(p, p+n, less<lli>());
  for (int i = 0; i < lons; i++)
    smallestSuffixSum[i + 1] = smallestSuffixSum[i] + p[i];
  reverse(p, p+lons);
  for (int i = 0; i < lons; i++)
    biggestSuffixSum[i + 1] = biggestSuffixSum[i] + p[i];

  sort(p, p+n, greater<lli>());
  REC
    lolHalf(hins - 1, his);
  else
    calcHalf(hins, his);

  REC {
    for (int i = 0; i <= min(k, lons); i++)
      sort(los[i].begin(), los[i].end());
    for (int i = 0; i <= min(k, hins); i++)
      sort(his[i].begin(), his[i].end());
  }

  for (int i = 0; i <= min(k, lons); i++)
  {
    DEBUG printf("%d %d\n", i, (int)los[i].size());
    for (lli x: los[i])
      if (x <= b)
      {
        int remlo = binarySearch(k - i, x, true), remhi = binarySearch(k - i, x, false);
        // DEBUG printf("%d %d | %lld | %d %d %d\n", i, k - i, x, (int)his[k - i].size(), remlo, remhi);
        ans += his[k - i].size() - remlo - remhi;
      }
  }
  printf("%lld\n", ans);

  return 0;
}