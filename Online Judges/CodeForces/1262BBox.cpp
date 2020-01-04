#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int q[maxN], ans[maxN];
set<int> todo;

bool valid()
{
  int now = 0;
  for (int i = 0; i < n; i ++)
  {
    now = max(now, ans[i]);
    if (now != q[i])
      return false;
  }
  return true;
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
      scanf("%d", &q[i]), todo.insert(i + 1);

    ans[0] = q[0], todo.erase(q[0]);
    for (int i = 1; i < n; i ++)
    {
      if (q[i] == q[i - 1])
      {
        ans[i] = *todo.begin();
        todo.erase(todo.begin());
      }
      else
        ans[i] = q[i], todo.erase(q[i]);
    }
    if (valid())
      for (int i = 0; i < n; i ++)
        printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
    else
      printf("-1\n");
  }
  return 0;
}
