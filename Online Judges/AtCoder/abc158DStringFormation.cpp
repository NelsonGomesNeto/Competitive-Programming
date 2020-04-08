#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6;
char ss[maxN];
list<char> s; bool fliped = false;

int main()
{
  while (scanf(" %s", ss) != EOF)
  {
    s.clear(), fliped = false;
    for (int i = 0; ss[i]; i ++)
      s.push_back(ss[i]);

    int q; scanf("%d", &q);
    while (q --)
    {
      int op; scanf("%d", &op);
      if (op == 1)
        fliped = !fliped;
      else
      {
        int f; char c; scanf("%d %c", &f, &c);
        if (f == 1)
        {
          if (!fliped)
            s.push_front(c);
          else
            s.push_back(c);
        }
        else
        {
          if (!fliped)
            s.push_back(c);
          else
            s.push_front(c);
        }
      }
    }
    if (fliped)
      reverse(s.begin(), s.end());

    for (char c: s)
      printf("%c", c);
    printf("\n");
  }
  return 0;
}