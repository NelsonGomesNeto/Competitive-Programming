#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int mod = 127;

char decode(char c, int x, int y)
{
  return (c * x + y) % mod;
}

const int maxN = 1e5;
int n, x, y;
int s[maxN];
string ans;

int main()
{
  while (~scanf("%d %d %d", &n, &x, &y))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &s[i]);

    ans.clear();
    ans.resize(n);
    for (int i = 0; i < n; ++i)
      ans[i] = decode(s[i], x, y);

    printf("%s\n", ans.c_str());
  }
  return 0;
}
