#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n; lli l, r;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d %lld %lld", &n, &l, &r);

    lli curr = 1; int start;
    for (start = 1; start <= n; start++)
    {
      lli now = 2*(n - start);
      // printf("\t%d - %lld\n", start, now);
      if (curr + now > l) break;
      curr += now;
    }
    if (start > n) start = 1;

    int u = start, v = start + ((l - curr) / 2) + 1; bool turn = (l - curr) & 1;
    vector<int> ans;
    for (lli i = l; i <= r; i++, turn = !turn)
    {
      if (turn)
        ans.push_back(v++);
      else
        ans.push_back(u);
      if (v > n)
      {
        u++;
        if (u >= n) u = 1;
        v = u + 1;
        turn = true;
      }
    }

    for (int i = 0; i < ans.size(); i++)
      printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
  }
  return 0;
}
/*
3
1 2 1 3
    2 3
      1

4

1 2 1 3 1 4
    2 3 2 4
        3 4
          1
*/
