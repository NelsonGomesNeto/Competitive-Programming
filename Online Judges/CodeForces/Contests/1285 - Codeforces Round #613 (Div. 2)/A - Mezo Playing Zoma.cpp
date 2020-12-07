#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5 + 1; int n;
char s[maxN];
int cnt[256];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    cnt['L'] = cnt['R'] = 0;
    scanf(" %s", s);
    for (int i = 0; i < n; i ++)
      cnt[s[i]] ++;

    int ans = cnt['L'] + cnt['R'] + 1;
    printf("%d\n", ans);
  }
  return 0;
}
