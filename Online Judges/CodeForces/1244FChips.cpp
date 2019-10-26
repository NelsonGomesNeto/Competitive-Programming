#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli k;
char s[maxN + 1];
bool unstable[maxN];

int circ(int i, int sz = n)
{
  return ((i % sz) + sz) % sz;
}

char flip(char a)
{
  return a == 'W' ? 'B' : 'W';
}

int main()
{
  while (scanf("%d %lld", &n, &k) != EOF)
  {
    scanf(" %s", s);
    int u = 0;
    for (int i = 0; i < n; i ++)
      u += (unstable[i] = s[circ(i - 1)] != s[i] && s[circ(i + 1)] != s[i]);
    if (u == n)
    {
      if (k & 1)
        for (int i = 0; i < n; i ++)
          s[i] = flip(s[i]);
      printf("%s\n", s);
    }
    else
    {
      DEBUG {
        printf("%s\n", s);
        for (int i = 0; i < n; i ++)
          printf("%d%s", unstable[i], i < n - 1 ? "" : "\n");
      }
      for (int i = 0; i < n; i ++)
        if (unstable[i])
        {
          int start = i, end = i, d = 0;
          while (unstable[circ(start - 1)]) unstable[start = circ(start - 1)] = false, d ++;
          while (unstable[circ(end + 1)]) unstable[end = circ(end + 1)] = false, d ++;
          unstable[i] = false;

          int kk = k;
          for (; kk && d > 0; kk --, end = circ(end - 1), start = circ(start + 1), d -= 2)
            s[end] = s[circ(end + 1)], s[start] = s[circ(start - 1)];
          if (kk && start == end)
          {
            if (s[start] != s[circ(start - 1)] && s[start] != s[circ(start + 1)])
              s[start] = flip(s[start]);
            end = circ(end - 1), start = circ(start + 1), kk --, d -= 2;
          }
          if (k & 1LL)
          {
            for (; d > 0; end = circ(end - 1), start = circ(start + 1), d -= 2)
              s[end] = flip(s[end]), s[start] = flip(s[start]);
            if (start == end)
              s[start] = flip(s[start]);
          }
        }
      printf("%s\n", s);
    }
  }
  return 0;
}