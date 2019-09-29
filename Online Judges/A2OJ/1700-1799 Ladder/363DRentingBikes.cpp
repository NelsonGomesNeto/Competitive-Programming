#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Binary search the number of bikes:
    lo = mid, if to buy that number of bikes requires a budget <= a
    hi = mid - 1, else ^
  How can we calculate the budget required to buy (x) bikes
    Sort students' budget
    Sort bikes' price
    The greedy best match is:
      richest student tries to buy the x-th cheapest bike
      second richest student tries to buy the (x-1)-th cheapest bike
      ...
*/

const int maxN = 1e5; int n, m; lli a;
lli b[maxN], p[maxN];

// This function calculates the number of a's budget spent to buy a given number of bikes
lli check(int bikes)
{
  lli price = 0;
  for (int i = 0; i < bikes; i ++)
    if (p[i] > b[bikes - i - 1])
      price += p[i] - b[bikes - i - 1];
  return price;
}

int main()
{
  while (scanf("%d %d %lld", &n, &m, &a) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &b[i]);
    sort(b, b+n); reverse(b, b+n);
    for (int j = 0; j < m; j ++)
      scanf("%lld", &p[j]);
    sort(p, p+m);

    int lo = 0, hi = min(n, m);
    while (lo < hi)
    {
      int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
      if (check(mid) <= a) lo = mid;
      else hi = mid - 1;
    }

    lli cost = 0;
    for (int i = 0; i < lo; i ++)
      cost += p[i];
    // cost - a == how much students spent to buy a given (lo) number of bikes

    printf("%d %lld\n", lo, max(cost - a, 0LL));
  }

  return 0;
}