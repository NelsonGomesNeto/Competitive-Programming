#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)

int main()
{
  int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d);

  int p = a*d, q = b*c;
  int np = max(p, q) - min(p, q), nq = max(p, q);
  for (int i = 2; i <= max(np, nq); i ++)
    while (!(np % i) && !(nq % i))
    {
      np /= i;
      nq /= i;
    }

  DEBUG printf("%d %d %d\n", p, q, divisor);

  printf("%d/%d\n", np, nq);

  return(0);
}
