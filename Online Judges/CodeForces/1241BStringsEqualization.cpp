#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    char s[2][101];
    scanf("%s %s", s[0], s[1]);
    // printf("%s - %s\n", s[0], s[1]);
    int cnt[2][256]; memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < 2; i ++)
      for (int j = 0; s[i][j]; j ++)
        cnt[i][s[i][j]] ++;

    bool can = false;
    for (int i = 0; i < 256; i ++)
      if ((cnt[0][i] > 0) && (cnt[1][i] > 0))
        can = true;
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
