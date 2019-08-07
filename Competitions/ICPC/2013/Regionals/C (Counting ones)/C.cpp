#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli full[57], ones[57];

lli numberSize(lli number)
{
  lli s = 0;
  while (number) number >>= 1, s ++;
  return(s);
}
lli count(lli number, lli verbose = false)
{
  lli o = 0, ans = 0, prv = number;
  vector<lli> bits;
  while (number)
  {
    bits.push_back(number & 1LL);
    number >>= 1LL;
  }
  if (verbose)
  {
    printf("Counting(%lld), %d - ", prv, (int) bits.size());
    for (lli i: bits) printf("%lld", i); printf("\n");
  }
  for (int i = bits.size() - 1; i >= 0; i --)
    if (bits[i])
    {
      ans += ones[i] + o*(1LL << i);
      o ++;
    }
  return(ans);
}

int main()
{
  lli now = 0;
  full[1] = 1;
  for (int i = 2; i <= 56; i ++)
    full[i] = 2LL*full[i - 1] + (1LL << (i - 1));
  for (int i = 0; i <= 56; i ++)
    ones[i] = full[i] + 1;

  lli a, b;
  while (scanf("%lld %lld", &a, &b) != EOF)
  {
    lli ans = count(b) - count(a - 1);
    printf("%lld\n", ans);
  }

  return(0);
}