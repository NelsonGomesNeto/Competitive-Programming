#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
const lli copies = 1e10;
char t[maxN + 1];
string s = "110";

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    scanf(" %s", t);

    bool has = false;
    int minStart = 2;
    int sz = n + 100;
    for (int start = 0; start < 3; start++)
    {
      bool has2 = true;
      for (int i = 0; i < n; i++)
        if (t[i] != s[(start + i) % 3])
          has2 = false;
      has |= has2;
      if (has2) minStart = min(minStart, start), sz = min(sz, start + n);
    }

    lli ans = copies;
    if (!has) ans = 0;
    else ans -= (sz - 1) / 3;
    if (n == 1) ans = (1 + (t[0] == '1'))*copies;
    printf("%lld\n", ans);
  }
  return 0;
}