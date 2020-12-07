#include <bits/stdc++.h>
#define lli long long int

int lowerBound(lli array[], int lo, int hi, lli target)
{
  if (lo >= hi) return(array[lo] <= target ? lo : lo - 1);
  int mid = (lo + hi) / 2;
  if (target <= array[mid]) return(lowerBound(array, lo, mid, target));
  else return(lowerBound(array, mid + 1, hi, target));
}

int main()
{
  lli n, q; scanf("%lld %lld", &n, &q);
  lli str[n]; for (int i = 0; i < n; i ++) scanf("%lld", &str[i]);
  lli order[q]; for (int i = 0; i < q; i ++) scanf("%lld", &order[i]);

  lli needed[n]; needed[0] = str[0];
  for (int i = 1; i < n; i ++)
    needed[i] = str[i] + needed[i - 1];

  lli removed = 0;
  for (int i = 0; i < q; i ++)
  {
    lli killed = lowerBound(needed, 0, n - 1, order[i] + removed) + 1;
    //printf("||%d||\n", killed);
    if (killed >= n)
    {
      removed = 0;
      printf("%lld\n", n);
    }
    else
    {
      removed += order[i];
      printf("%lld\n", n - killed);
    }
  }

  return(0);
}