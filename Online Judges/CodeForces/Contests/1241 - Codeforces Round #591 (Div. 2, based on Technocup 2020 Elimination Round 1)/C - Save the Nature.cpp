#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli tickets[maxN], x, a, y, b, k;

bool can(int guess)
{
  lli got = 0, aa = 0, bb = 0; int j = 0;
  for (int i = 1; i <= guess; i ++)
    if (i % a == 0 && i % b == 0)
      got += tickets[j ++] * (x + y);
  int aj = j, bj = j;
  for (int i = 1; i <= guess; i ++)
  {
    if (i % a == 0 && i % b != 0)
      aa += tickets[aj ++] * x;
    if (i % a != 0 && i % b == 0)
      bb += tickets[bj ++] * y;
  }
  for (int i = 1; i <= guess; i ++)
  {
    if (i % a != 0 && i % b == 0)
      aa += tickets[aj ++] * y;
    if (i % a == 0 && i % b != 0)
      bb += tickets[bj ++] * x;
  }
  return got + max(aa, bb) >= k;
}

int binarySearch()
{
  int lo = 1, hi = n;
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    if (can(mid)) hi = mid;
    else lo = mid + 1;
  }
  return can(lo) ? lo : -1;
}

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
      scanf("%lld", &tickets[i]);
    sort(tickets, tickets+n); reverse(tickets, tickets+n);

    scanf("%lld %lld %lld %lld %lld", &x, &a, &y, &b, &k);
    k *= 100;

    int ans = binarySearch();
    printf("%d\n", ans);
  }
  return 0;
}
