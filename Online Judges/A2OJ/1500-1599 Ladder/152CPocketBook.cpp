#include <bits/stdc++.h>
using namespace std;
#define lli long long int
lli mod = 1000000007;

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  set<char> count[m];
  char name[m + 1];
  for (int i = 0; i < n; i ++)
  {
    scanf("\n%s", name);
    for (int j = 0; name[j]; j ++)
      count[j].insert(name[j]);
  }

  lli ans = 1;
  for (int i = 0; i < m; i ++)
    ans = (ans * count[i].size()) % mod;
  printf("%lld\n", ans);

  return(0);
}
