#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int a, b, q;

const int maxSz = 200*200;
lli memo[maxSz], sz;
lli f(lli x)
{
  return x / sz * memo[sz - 1] + memo[x % sz];
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d %d", &a, &b, &q);
    sz = a * b;
    for (int i = 1; i < sz; i++)
      memo[i] = memo[i - 1] + (i % a % b != i % b % a);

    for (int i = 0; i < q; i++)
    {
      lli l, r; scanf("%lld %lld", &l, &r);
      printf("%lld%c", f(r) - f(l - 1), i < q - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
