#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli apSum(lli a1, lli n, lli d)
{
  lli an = a1 + (n - 1)*d;
  return n * (a1 + an) >> 1LL;
}

const int maxX = 1e6;
bool notPrime[maxX + 1];
vector<int> primes;

const int maxN = 2e5; int n, e;
int a[maxN];
vector<int> pos[maxN];

int binarySearch(vector<int> &arr, int target, bool upperBound)
{
  int lo = 0, hi = arr.size() - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (arr[mid] <= target) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (arr[mid] >= target) hi = mid;
      else lo = mid + 1;
    }
  }
  if (upperBound) return arr[lo] <= target ? arr[lo] + 1 : 0;
  else return arr[lo] >= target ? arr[lo] - 1 : n - 1;
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i*primes[j] <= maxX; j ++)
    {
      notPrime[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &e);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      pos[i].clear();
    }

    for (int i = 0; i < n; i++)
      if (a[i] != 1)
        pos[i % e].push_back(i);

    lli ans = 0;
    for (int i = 0; i < n; i++)
      if (!notPrime[a[i]])
      {
        int base = i % e;
        int left = binarySearch(pos[base], i - 1, true);
        int right = binarySearch(pos[base], i + 1, false);

        lli leftSize = (i - left) / e;
        lli rightSize = (right - i) / e;
        DEBUG {
          printf("\t%d - %d | %d %d | %lld %lld\n", i, a[i], left, right, leftSize, rightSize);
          printf("\t\tpos:");
          for (int p: pos[base]) printf(" %d", p);
          printf("\n");
        }

        // ans += apSum(max(1LL, rightSize), leftSize + (rightSize > 0), 1);
        if (leftSize || rightSize)
        {
          if (leftSize) ans += rightSize + leftSize * (rightSize + 1);
          else ans += rightSize;
        }
      }
    printf("%lld\n", ans);
  }
  return 0;
}
