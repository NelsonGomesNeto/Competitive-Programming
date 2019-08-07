#include <bits/stdc++.h>
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n, k; scanf("%d %d", &n, &k);
    bool hasZero = false;
    int a[n]; for (int i = 0; i < n; i ++) { scanf("%d", &a[i]); if (a[i] == 0) hasZero = true; }
    sort(a, a+n);
    for (int i = 0; i < n && a[i] < 0 && k; i ++) a[i] *= -1, k --;
    sort(a, a+n);

    if (k && (k & 1) && !hasZero)
      for (int i = 0; i < n; i ++)
        if (a[i] > 0)
        {
          a[i] *= -1;
          break;
        }
    
    int sum = 0; for (int i = 0; i < n; i ++) sum += a[i];
    printf("%d\n", sum);
  }
  return(0);
}