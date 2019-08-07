#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int aa[2], bb[2];

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  lli a[n], b[m];
  
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &a[i]);
    aa[a[i] & 1] ++;
  }
  for (int i = 0; i < m; i ++)
  {
    scanf("%lld", &b[i]);
    bb[b[i] & 1] ++;
  }

  printf("%d\n", min(aa[0], bb[1]) + min(aa[1], bb[0]));

  return(0);
}
