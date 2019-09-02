#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
const int maxN = 3e5; int n;
const lli mod = 998244353;
pair<int, int> p[maxN];
int a[maxN + 1], b[maxN + 1];
map<pair<int, int>, int> ab;
lli fact[maxN + 1];
 
int main()
{
  scanf("%d", &n);
  fact[0] = 1; for (int i = 1; i <= n; i ++) fact[i] = fact[i - 1] * i % mod;
 
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &p[i].first, &p[i].second);
    a[p[i].first] ++, b[p[i].second] ++;
    if (!ab.count(p[i])) ab[p[i]] = 0;
    ab[p[i]] ++;
  }
  sort(p, p+n);
 
  lli ans = fact[n], aCnt = 1, bCnt = 1, abCnt = 1;
  for (int i = 1; i <= n; i ++)
  {
    aCnt = aCnt * fact[a[i]] % mod;
    bCnt = bCnt * fact[b[i]] % mod;
  }
  for (auto i: ab)
    abCnt = abCnt * fact[i.second] % mod;
 
  for (int i = 1; i < n; i ++)
    if (p[i].second < p[i - 1].second)
      abCnt = 0;
 
  ans = (((ans - aCnt + mod) % mod - bCnt + mod) % mod + abCnt) % mod;
  printf("%lld\n", ans);
 
  return(0);
}