#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

lli l, r;

int rightLimit(lli num)
{
  int size = 0;
  while (num >> 1) num >>= 1, size ++;
  return(size);
}

lli fixToBigger(lli next, int k)
{
  while (next < l && k >= 0)
  {
    if ((next | (1LL << k)) <= r) next |= 1LL << k;
    k --;
  }
  return(next);
}

int main()
{
  scanf("%lld %lld", &l, &r);
  lli result = 0, a = r, b = l;
  int rr = rightLimit(r);
  while (rr != -1)
  {
    lli now = 1LL << rr;
    if ((now & a) && !(now & b)) result |= now;
    else if ((now & a) && (now & b))
    {
      lli nextA = fixToBigger(a - now, rr - 1), nextB = fixToBigger(b - now, rr - 1);
      if (nextA >= l && nextA <= r) b = nextA, result |= now;
      else if (nextB >= l && nextB <= r) b = nextB, result |= now;
    }
    else if (!(now & a) && (now & b)) result |= now;
    else if (!(now & a) && !(now & b))
    {
      lli nextB = (b | now) & ~(now - 1), nextA = (a | now) & ~(now - 1);
      if (nextB >= l && nextB <= r) b = nextB, result |= now;
      else if (nextA >= l && nextA <= r) a = nextA, result |= now;
    }
    rr --;
  }

  printf("%lld\n", l == r ? 0 : result);
  return(0);
}