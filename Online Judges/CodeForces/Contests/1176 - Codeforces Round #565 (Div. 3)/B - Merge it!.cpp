#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
int a[maxN], cnt[3];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      cnt[a[i] % 3] ++;
    }

    int c12 = min(cnt[1], cnt[2]);
    printf("%d\n", cnt[0] + c12 + (cnt[1] - c12) / 3 + (cnt[2] - c12) / 3);
  }
  return 0;
}