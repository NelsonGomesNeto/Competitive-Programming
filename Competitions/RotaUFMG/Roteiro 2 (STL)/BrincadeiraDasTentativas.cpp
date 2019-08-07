#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, t = 0;
  while (scanf("%d", &n) && n)
  {
    if (t ++) printf("\n");
    
    int a[n];
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);
    sort(a, a+n);

    do
    {
      for (int i = 0; i < n; i ++)
        printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
    } while (next_permutation(a, a+n));
  }
  return(0);
}