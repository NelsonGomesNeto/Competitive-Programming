#include <bits/stdc++.h>
#define lli long long int
using namespace std;

char recipe[101];
lli has[3], price[3], budget;
lli r[3];

void read(int n, lli a[])
{
  for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
}

bool eval(lli x)
{
  lli b = x*r[0] - has[0], s = x*r[1] - has[1], c = x*r[2] - has[2];
  b = max(0LL, b), s = max(0LL, s), c = max(0LL, c);
  lli toPay = b*price[0] + s*price[1] + c*price[2];
  return(toPay <= budget);
}

lli binarySearch(lli lo, lli hi)
{
  if (lo >= hi) return(lo);
  lli mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
  if (eval(mid)) return(binarySearch(mid, hi));
  return(binarySearch(lo, mid - 1));
}

int main()
{
  int lmap[256]; lmap['B'] = 0, lmap['S'] = 1, lmap['C'] = 2;
  scanf("%s", recipe);
  for (int i = 0; recipe[i]; i ++) r[lmap[recipe[i]]] ++;

  read(3, has); read(3, price); scanf("%lld", &budget);

  printf("%lld\n", binarySearch(0, 1e14));

  return(0);
}