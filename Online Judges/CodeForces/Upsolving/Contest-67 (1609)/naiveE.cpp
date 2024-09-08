#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, q;
char ss[maxN + 1];
string s, aux;
set<int> pos[3];

struct Query
{
  int pos; char c;
  void read() { scanf("%d %c", &pos, &c); pos--; }
};
Query queries[maxN];

int main()
{
  int pundim = 0;
  while (~scanf("%d %d", &n, &q))
  {
    if (pundim++) printf("--------\n");
    pos[0].clear(), pos[1].clear(), pos[2].clear();

    scanf(" %s", ss);
    s = string(ss);

    for (int i = 0; i < q; i++)
    {
      queries[i].read();
      int p = queries[i].pos;
      char c = queries[i].c;
      s[p] = c;

      int ans = 1e9;
      for (int toRem = 0; toRem < 3; toRem++)
        for (int toReplace = 'a'; toReplace <= 'c'; toReplace++)
        {
          if (toRem == toReplace - 'a') continue;

          aux = s;
          int curr = 0;
          bool changes;
          do
          {
            changes = false;
            for (int a = 0; a < n && !changes; a++)
              if (s[a] == 'a')
                for (int b = a + 1; b < n && !changes; b++)
                  if (s[b] == 'b')
                    for (int c = b + 1; c < n && !changes; c++)
                      if (s[c] == 'c')
                      {
                        curr++, changes = true;
                        if (toRem == 0) s[a] = toReplace;
                        else if (toRem == 1) s[b] = toReplace;
                        else s[c] = toReplace;
                      }
          } while (changes);

          s = aux;
          ans = min(ans, curr);
        }
      printf("%d\n", ans);
    }
  }
  
  return 0;
}
