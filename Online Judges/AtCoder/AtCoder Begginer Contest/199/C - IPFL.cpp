#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char s[2*maxN + 1];

int reversed(int a)
{
  return (a + n) % (2*n);
}

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", s);
    int q; scanf("%d", &q);

    bool flipped = false;

    while (q--)
    {
      int t, a, b; scanf("%d %d %d", &t, &a, &b);
      a--, b--;

      if (t == 1)
      {
        if (flipped)
        {
          a = reversed(a);
          b = reversed(b);
        }
        DEBUG printf("\t%d %d\n", a, b);
        swap(s[a], s[b]);
      }
      else
      {
        flipped = !flipped;
      }
    }

    if (flipped)
      for (int i = 0; i < n; i++)
        swap(s[i], s[i + n]);

    printf("%s\n", s);
  }
  return 0;
}