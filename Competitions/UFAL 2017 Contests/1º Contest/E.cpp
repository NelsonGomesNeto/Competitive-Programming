#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;
lli big[(int) 1e5], small[(int) 1e5], n, m;

lli check(lli guess)
{
  lli changes = 0;
  for (int i = 0; i < n; i ++)
    if (big[i] < guess) changes += guess - big[i];
    else break;
  for (int i = m - 1; i >= 0; i --)
    if (small[i] > guess) changes += small[i] - guess;
    else break;
  return(changes);
}

lli getAns(lli lo, lli hi)
{
  lli best = check(lo);
  for (lli i = lo + 1; i <= hi; i ++)
  {
    lli aux = check(i);
    DEBUG printf("%lld %lld\n", i, aux);
    if (aux < best) best = aux;
  }
  return(best);
}

lli tsearch(lli lo, lli hi)
{
  lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
  if (lo >= hi - 2) return(getAns(lo, hi));
  lli elo = check(midlo), ehi = check(midhi);
  DEBUG printf("%lld %lld %lld %lld\n", lo, hi, elo, ehi);
  if (elo <= ehi) return(tsearch(lo, midhi));
  else if (ehi < elo) return(tsearch(midlo, hi));
  else return(tsearch(midlo, midhi));
}

int main()
{
  scanf("%lld %lld", &n, &m);
  for (int i = 0; i < n; i ++) scanf("%lld", &big[i]);
  for (int i = 0; i < m; i ++) scanf("%lld", &small[i]);

  sort(big, big+n); sort(small, small+m);

  lli best = tsearch(0, 1e9 + 1);

  printf("%lld\n", best);

  return(0);
}