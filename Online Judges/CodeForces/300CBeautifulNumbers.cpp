#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
#define lli long long int
lli mod = 1000000007; int a, b, n, diff;
lli modularFactorial[1000001];

int valid(lli sum)
{
  lli aux = sum;
  while (sum > 0)
  {
    int remain = sum % 10;
    if (remain != a && remain != b) return(0);
    sum /= 10;
  }
  DEBUG printf("%lld\n", aux);
  return(1);
}

lli modularPowerIterative(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1) ans = (ans * x) % mod;
    x = (x * x) % mod;
    y /= 2;
  }
  return(ans);
}

lli modularPower(lli x, lli y)
{
  if (y == 0) return(1);
  lli r = modularPower(x, y / 2);
  lli rr = (r * r) % mod;
  if (y & 1) return((rr * x) % mod);
  return((r * r) % mod);
}

// a * b^(p-1) mod p = a mod p
// a * b^(p-2) mod p = (a mod p) / b
lli modularDivision(lli a, lli b)
{
  return((a * modularPower(b, mod - 2)) % mod);
}

lli modularChoose(lli num, lli k)
{
  return(modularDivision(modularFactorial[num], (modularFactorial[k] * modularFactorial[num - k]) % mod));
}

int main()
{
  scanf("%d %d %d", &a, &b, &n); diff = b - a;
  lli now = 0; for (int i = 0; i < n; i ++) now += a;
  DEBUG printf("%lld\n", now);

  modularFactorial[0] = 1;
  for (int i = 1; i <= n; i ++) modularFactorial[i] = (modularFactorial[i - 1] * i) % mod;

  lli ans = valid(now) ? modularChoose(n, 0) : 0;
  for (int i = 0; i < n; i ++)
  {
    now += diff;
    if (valid(now)) ans = (ans + modularChoose(n, i + 1)) % mod;
    DEBUG if (valid(now)) printf("%lld - %d\n", now, i);
  }

  DEBUG printf("%lld\n", now);

  printf("%lld\n", ans);
  return(0);
}