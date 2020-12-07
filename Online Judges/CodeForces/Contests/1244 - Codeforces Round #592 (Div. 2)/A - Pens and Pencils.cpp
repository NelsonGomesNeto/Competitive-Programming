#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int a, b, c, d, k; scanf("%d %d %d %d %d", &a, &b, &c, &d, &k);
    int aa = ceil((double) a / c);
    int bb = ceil((double) b / d);
    if (aa + bb > k) printf("-1\n");
    else printf("%d %d\n", aa, bb);
  }
  return 0;
}
