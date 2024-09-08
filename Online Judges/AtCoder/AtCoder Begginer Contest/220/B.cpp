#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli fromBaseTo10(lli k, lli num)
{
  lli pot = 1, ans = 0;
  while (num)
  {
    ans += (num % 10) * pot;
    num /= 10, pot *= k;
  }
  return ans;
}

int main()
{
  lli k, a, b;
  scanf("%lld %lld %lld", &k, &a, &b);
  a = fromBaseTo10(k, a);
  b = fromBaseTo10(k, b);
  printf("%lld\n", a * b);
  return 0;
}