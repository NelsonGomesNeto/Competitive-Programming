#include <bits/stdc++.h>
#define lli long long int
#define DEBUG if(0)
#define DEBUG2 if(0)

int meetPoint(int n)
{
  int r = 0, h = 0, same = 0;
  while (!same)
  {
    DEBUG2 printf("%d %d\n", r, h);
    r -= 2; h += 1;
    r = (r + n) % n; h %= n;
    if (r == h) same ++;
  }
  return(r);
}

int main()
{
  DEBUG for (int i = 1; i <= 100; i ++) printf("%d %d\n\n", i, meetPoint(i));
  int t; scanf("%d", &t);
  while (t --)
  {
    lli n; scanf("%lld", &n);
    printf("%lld\n", !(n % 3) ? n/3 : 0);
  }

  return(0);
}
// It is 2/3 if the oposite direction is r, and 1/3 if it's h