#include <bits/stdc++.h>
using namespace std;
#define lli long long int

int main()
{
  int n; scanf("%d", &n);
  lli a[n], b[n];
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &a[i]);
    b[i] = a[i];
  }
  sort(a, a+n);

  int diff = 0;
  for (int i = 0; i < n; i ++) diff += a[i] != b[i];

  printf("%s\n", diff <= 2 ? "YES" : "NO");
  return(0);
}
