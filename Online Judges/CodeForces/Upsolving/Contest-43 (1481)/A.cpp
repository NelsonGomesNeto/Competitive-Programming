#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
char s[maxN + 1];
int cnt[256];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int px, py; scanf("%d %d", &px, &py);
    scanf(" %s", s);

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; s[i]; i++)
      cnt[s[i]]++;

    bool can = true;
    if (px >= 0) can &= cnt['R'] >= px;
    else can &= cnt['L'] >= -px;
    if (py >= 0) can &= cnt['U'] >= py;
    else can &= cnt['D'] >= -py;
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
