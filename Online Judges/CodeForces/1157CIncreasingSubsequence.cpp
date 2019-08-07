#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];
char movements[maxN + 1];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);

  int ans = 0, lo = 0, hi = n - 1, prv = 0;
  for (; ans < n; ans ++)
  {
    if (a[lo] > prv && a[lo] == a[hi])
    {
      int left = ans, p = 0; while (left < n && a[lo] > p) p = a[lo ++], left ++;
      int right = ans; p = 0; while (right < n && a[hi] > p) p = a[hi --], right ++;
      if (left > right) for (int i = ans; i < left; i ++) movements[i] = 'L';
      else for (int i = ans; i < right; i ++) movements[i] = 'R';
      ans = max(left, right);
      break;
    }
    else if (a[lo] > prv && a[hi] > prv)
    {
      if (a[lo] < a[hi]) movements[ans] = 'L', prv = a[lo ++];
      else movements[ans] = 'R', prv = a[hi --];
    }
    else if (a[lo] > prv) movements[ans] = 'L', prv = a[lo ++];
    else if (a[hi] > prv) movements[ans] = 'R', prv = a[hi --];
    else break;
  }

  printf("%d\n", ans);
  printf("%s\n", movements);
  return(0);
}