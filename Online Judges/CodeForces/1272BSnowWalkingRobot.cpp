#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
char seq[maxN + 1], todo[maxN + 1];
int cnt[256];
vector<char> all = {'R', 'U', 'L', 'D'};

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    memset(cnt, 0, sizeof(cnt));
    scanf(" %s", seq); n = strlen(seq);
    for (int i = 0; i < n; i ++)
      cnt[seq[i]] ++;

    int rl = min(cnt['R'], cnt['L']), ud = min(cnt['U'], cnt['D']);
    if (rl == 0) ud = min(ud, 1);
    if (ud == 0) rl = min(rl, 1);
    int ans = 2*rl + 2*ud;
    printf("%d\n", ans);
    if (ans)
    {
      int at = 0;
      for (char now: all)
        if (now == 'R' || now == 'L')
          for (int k = 0; k < rl; k ++)
            todo[at ++] = now;
        else
          for (int k = 0; k < ud; k ++)
            todo[at ++] = now;
      todo[at] = '\0';
      printf("%s\n", todo);
    }
  }
  return 0;
}
