#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n;
int a[maxN], cnt[maxN + 1];
int ans[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      cnt[a[i]]++;
    }

    for (int i = 0, j = 0; i <= maxN; i++)
      while (cnt[i]--)
        ans[j++] = i;

    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i < n - 1 ?  ' ' : '\n');
  }
  return 0;
}