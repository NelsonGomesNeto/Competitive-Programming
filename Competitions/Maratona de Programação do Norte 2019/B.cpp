#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  lli lol[5] = {300, 1500, 600, 1000, 150};
  lli k[5]; for (int i = 0; i < 5; i ++) scanf("%lld", &k[i]);
  lli ans = 225; for (int i = 0; i < 5; i ++) ans += k[i] * lol[i];
  printf("%lld\n", ans);
  return(0);
}