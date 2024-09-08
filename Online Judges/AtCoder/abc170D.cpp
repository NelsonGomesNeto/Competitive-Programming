#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxX = 1e6 + 1; int n;
int a[maxN];
bool valid[maxX];
int cnt[maxX];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    memset(cnt, 0, sizeof(cnt));
    fill(valid, valid+maxX, true);
    for (int i = 0; i < n; i++)
      cnt[a[i]]++;

    for (int i = 1; i < maxX; i++)
      if (cnt[i])
      {
        if (cnt[i] > 1) valid[i] = false;
        for (int j = 2; i*j < maxX; j++)
          valid[i*j] = false;
      }
    int ans = 0;
    for (int i = 1; i < maxX; i++)
      if (cnt[i])
        ans += valid[i];
    printf("%d\n", ans);
  }
  return 0;
}