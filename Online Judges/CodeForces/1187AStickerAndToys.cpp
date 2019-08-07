#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n, s, t; scanf("%d %d %d", &n, &s, &t);
    printf("%d\n", max(n - s, n - t) + 1);
  }
  return(0);
}
