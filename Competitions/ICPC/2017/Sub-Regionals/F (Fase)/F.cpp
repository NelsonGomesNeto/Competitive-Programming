#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, k; scanf("%d\n%d", &n, &k);
  int a[n];
  for (int i = 0; i < n; i ++)
    scanf("%d", &a[i]);
  sort(a, a+n);

  int c = 0, i = n - 1;
  while (c < k)
  {
    c ++;
    while (i >= 1 && a[i - 1] == a[i])
    {
      i --; c ++;
    } i --;
  }

  printf("%d\n", c);

  return(0);
}