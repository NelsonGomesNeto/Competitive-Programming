#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n;
lli a[maxN];
int cnt[maxN];
int powers[maxN];

int countPowersOfTwo(lli num)
{
  int c = 0;
  while (num && (~num & 1))
    num >>= 1, ++c;
  return c;
}

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d", &n);
    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
      scanf("%lld", &a[i]);
      cnt[i] = countPowersOfTwo(a[i]);
      sum += cnt[i];
      powers[i] = countPowersOfTwo(i + 1);
    }
    sort(powers, powers+n);

    int ans = 0;
    for (int i = n - 1; i >= 0 && sum < n; --i)
    {
      sum += powers[i];
      ++ans;
    }
    if (sum < n)
      ans = -1;
    printf("%d\n", ans);
  }

  return 0;
}
