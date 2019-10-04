#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  deque<int> q; set<int> has;
  for (int i = 0; i < n; i ++)
  {
    int a; scanf("%d", &a);
    if (has.count(a)) continue;
    else
    {
      if (q.size() == k)
      {
        has.erase(q.back());
        q.pop_back();
      }
      q.push_front(a);
      has.insert(q.front());
    }
  }
  printf("%d\n", (int) q.size());
  for (int i = 0; i < q.size(); i ++)
    printf("%d%c", q[i], i < q.size() - 1 ? ' ' : '\n');
  return 0;
}
