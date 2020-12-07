#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
#define lli long long int
lli candies, people, m, d;

lli eva(lli x)
{
  lli pack = people * x;
  lli loops = candies / pack, passed = people - 1, isFull = candies % pack == 0;
  if (!isFull)
    passed = (candies - (loops * pack)) / x - 1;

  lli timesSomeone = loops + !isFull;
  lli totalArkady = timesSomeone * x;
  if (timesSomeone > d) return(0);
  return(totalArkady);
}

lli checkRange(lli lo, lli hi)
{
  lli best = 0;
  for (lli i = lo; i <= hi; i ++)
    best = max(best, eva(i));
  return(best);
}

lli ternarySearch(lli lo, lli hi)
{
  DEBUG printf("%lld %lld\n", lo, hi);
  if (lo >= hi - 5) return(checkRange(lo, hi));

  lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
  DEBUG printf("%lld %lld %lld %lld\n", midlo, eva(midlo), midhi, eva(midhi));
  if (eva(midlo) >= eva(midhi)) return(ternarySearch(lo, midhi + 1));
  else return(ternarySearch(midlo - 1, hi));
}

int main()
{
  scanf("%lld %lld %lld %lld", &candies, &people, &m, &d);

  lli best = 1, bTotal = 0, startingX = candies / (d * people);

  //printf("%lld\n", startingX);
  //for (lli x = startingX; x <= m; x ++)
    //printf("%lld: %lld\n", x, eva(x));

  for (lli i = 1; i <= d; i ++)
    bTotal = max(bTotal, ternarySearch(max((lli)1, candies / ((i + 1) * people)), max((lli)1, candies / (i * people))));

  printf("%lld\n", bTotal);

  return(0);
}