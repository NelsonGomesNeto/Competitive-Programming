#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 40; int n; lli t;
const int maxMask = 1 << (maxN >> 1);
lli a[maxN];
vector<lli> l, r;

void fill(int i, int di, int end, lli sum = 0)
{
  if (i == end)
  {
    if (sum <= t)
    {
      if (di == 1) l.push_back(sum);
      else r.push_back(sum);
    }
    return;
  }

  fill(i + di, di, end, sum);
  fill(i + di, di, end, sum + a[i]);
}

lli binarySearch(vector<lli> &arr, lli target)
{
  int lo = 0, hi = arr.size() - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (arr[mid] <= target) lo = mid;
    else hi = mid - 1;
  }
  return arr[lo] <= target ? arr[lo] : 0;
}

int main()
{
  while (scanf("%d %lld", &n, &t) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    l.clear(), r.clear();
    fill(0, 1, n >> 1);
    fill(n - 1, -1, (n >> 1) - 1);

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    lli ans = binarySearch(l, t);
    for (lli i: l)
      ans = max(ans, i + binarySearch(r, t - i));

    printf("%lld\n", ans);
  }
  return 0;
}