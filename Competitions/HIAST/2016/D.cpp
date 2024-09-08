#include <bits/stdc++.h>
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int a[5]; for (int i = 0; i < 5; i ++) scanf("%d", &a[i]);
    sort(a, a+5);
    printf("%d\n", a[3] * a[4]);
  }
  return(0);
}
