#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8e3; int n;
int cnt[maxN + 1];
int a[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]), cnt[i] = 0;
    cnt[n] = 0;

    for (int i = 0; i < n; i++)
      for (int j = i + 1, s = a[i] + a[i + 1]; j < n && s <= n; s += a[++j])
        cnt[s]++;

    int ans = 0;
    for (int i = 0; i < n; i++)
      if (cnt[a[i]])
        ans++;
    printf("%d\n", ans);
  }
  return 0;
}
