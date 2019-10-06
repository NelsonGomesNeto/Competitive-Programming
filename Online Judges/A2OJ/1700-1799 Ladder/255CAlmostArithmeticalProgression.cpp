#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 4e3, maxX = 1e6 + 1; int n;
int cnt[maxX], rpos[maxX], b[maxN];

void clear()
{
  for (int i = 0; i < n; i ++) cnt[b[i]] = 0, rpos[b[i]] = -1;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%d", &b[i]);

    int ans = 1;
    clear();
    for (int i = 0; i < n; i ++) ans = max(ans, ++ cnt[b[i]]);

    for (int i = 0; i < n; i ++)
    {
      clear();
      for (int j = i; j < n; j ++)
      {
        if (b[i] == b[j])
        {
          rpos[b[i]] = j;
          continue;
        }
        if (rpos[b[i]] > rpos[b[j]])
          rpos[b[j]] = j, cnt[b[j]] ++;
      }
      for (int j = 0; j < n; j ++)
        if (b[i] != b[j])
          ans = max(ans, 2*cnt[b[j]] + (rpos[b[i]] > rpos[b[j]]));
    }
    printf("%d\n", ans);
  }

  return 0;
}