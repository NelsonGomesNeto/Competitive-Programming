#include <bits/stdc++.h>
using namespace std;

int main()
{
  int a, d;
  while (scanf("%d %d", &a, &d) && !(!a && !d))
  {
    int aa[a], dd[d];
    for (int i = 0; i < a; i ++) scanf("%d", &aa[i]);
    for (int i = 0; i < d; i ++) scanf("%d", &dd[i]);
    sort(aa, aa+a); sort(dd, dd+d);

    if (aa[0] < dd[1])
      printf("Y\n");
    else
      printf("N\n");
  }
}