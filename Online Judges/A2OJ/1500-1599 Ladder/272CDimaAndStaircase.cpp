#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, m;
lli a[maxN], acc[maxN], boxes[maxN][3];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
  scanf("%d", &m);
  for (int i = 0; i < m; i ++) scanf("%lld %lld", &boxes[i][0], &boxes[i][1]);
  acc[0] = a[0]; for (int i = 1; i < n; i ++) acc[i] = max(acc[i - 1], a[i]);

  for (int i = 0; i < m; i ++)
  {
    boxes[i][2] = max(a[0], acc[boxes[i][0] - 1]);
    a[0] = boxes[i][2] + boxes[i][1];
    printf("%lld\n", boxes[i][2]);
  }

  return(0);
}