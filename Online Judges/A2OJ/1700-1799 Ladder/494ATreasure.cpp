#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
char s[maxN + 1];

int main()
{
  while (scanf("%s", s) != EOF)
  {
    getchar();
    n = strlen(s);

    bool can = true;

    int done = 0, sharps = 0, open = 0, close = 0;
    for (int i = 0; i < n; i ++)
      sharps += s[i] == '#', open += s[i] == '(', close += s[i] == ')';

    int op = 0, cl = 0, ans[sharps];
    for (int i = 0; i < n; i ++)
    {
      op += s[i] == '(';
      cl += s[i] == ')';
      if (s[i] == '#')
      {
        if (done + 1 == sharps)
        {
          if (open <= close) can = false;
          ans[done ++] = open - close, cl += open - close;
          close = open;
        }
        else
          ans[done ++] = 1, close ++, cl ++;
      }
      if (cl > op) can = false;
    }
    if (close != open) can = false;

    if (can)
      for (int i = 0; i < sharps; i ++)
        printf("%d\n", ans[i]);
    else
      printf("-1\n");
  }
  return 0;
}