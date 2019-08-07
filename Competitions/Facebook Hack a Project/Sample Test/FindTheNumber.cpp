#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
set<lli> a;

int main()
{
  scanf("%d", &n);
  for (int i = 0, aa; i < n; i ++)
  {
    scanf("%d", &aa);
    a.insert(aa);
  }
  int k; scanf("%d", &k);
  printf("%s\n", a.count(k) ? "YES" : "NO");
  return(0);
}