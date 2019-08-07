#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n, q; scanf("%d %d", &n, &q);
  lli a[n]; for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
  int in[n + 1], out[n + 1]; memset(in, 0, sizeof(in)), memset(out, 0, sizeof(out));
  while (q --)
  {
    int lo, hi; scanf("%d %d", &lo, &hi); lo --, hi --;
    in[lo] ++; out[hi + 1] ++;
  }
  int occurences[n];
  for (int i = 0, t = 0; i < n; i ++)
  {
    t += in[i] - out[i];
    occurences[i] = t;
  }
  sort(a, a+n), sort(occurences, occurences+n);
  lli totalSum = 0;
  for (int i = 0; i < n; i ++) totalSum += occurences[i] * a[i];
  printf("%lld\n", totalSum);

  return(0);
}