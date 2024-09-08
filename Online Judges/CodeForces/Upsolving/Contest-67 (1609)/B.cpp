#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, q;
char s[maxN + 1];

struct Query
{
  int pos; char c;
  void read() { scanf("%d %c", &pos, &c); pos--; }
};
Query queries[maxN];

int main()
{
  while (~scanf("%d %d", &n, &q))
  {
    scanf(" %s", s);
    int cnt = 0;
    for (int i = 1; i + 1 < n; i++)
      if (s[i] == 'b' && s[i - 1] == 'a' && s[i + 1] == 'c')
        cnt++;

    for (int i = 0; i < q; i++)
    {
      queries[i].read();
      int p = queries[i].pos;
      char prev = s[p];
      if (prev == 'a')
      {
        if (p + 2 < n && s[p + 1] == 'b' && s[p + 2] == 'c')
          cnt--;
      }
      else if (prev == 'b')
      {
        if (p - 1 >= 0 && p + 1 < n && s[p - 1] == 'a' && s[p + 1] == 'c')
          cnt--;
      }
      else
      {
        if (p - 2 >= 0 && s[p - 2] == 'a' && s[p - 1] == 'b')
          cnt--;
      }

      s[queries[i].pos] = queries[i].c;

      if (p + 2 < n && s[p + 1] == 'b' && s[p + 2] == 'c' && queries[i].c == 'a')
        cnt++;
      if (p - 1 >= 0 && p + 1 < n && s[p - 1] == 'a' && s[p + 1] == 'c' && queries[i].c == 'b')
        cnt++;
      if (p - 2 >= 0 && s[p - 2] == 'a' && s[p - 1] == 'b' && queries[i].c == 'c')
        cnt++;
      printf("%d\n", cnt);
    }
  }
  return 0;
}
