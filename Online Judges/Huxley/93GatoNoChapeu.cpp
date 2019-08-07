#include <bits/stdc++.h>
#define lli long long int

int main()
{
  lli height, working;
  while (scanf("%lld %lld", &height, &working) && !(!height && !working))
  {
    for (lli n = 1, c = 1, cc = 1, h = height, pile = height; n < height;)
    {
      // printf("%lld %lld %lld\n", n, c, h);
      if (h == 1) { printf("0 1\n"); break; }
      c *= n;
      h /= (n + 1);
      pile += c * h;
      if (h <= 1 && c != working)
        n ++, c = 1, cc = 1, h = height, pile = height;
      else if (h != 1) cc += c;
      else if (h == 1 && c == working)
      {
        printf("%lld %lld\n", cc, pile);
        break;
      }
    }
  }
  return(0);
}