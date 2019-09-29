#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;
 
const int maxN = 1e5; int n;
int a[maxN], nxt[maxN], prv[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    queue<int> q, nq;

    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      prv[i] = i - 1, nxt[i] = i + 1;
    }
    for (int i = n - 1; i > 0; i --)
      if (i && a[prv[i]] > a[i])
        q.push(i);

    int ans = 0, alive = n;
    while (!q.empty())
    {
      ans ++;
      while (!q.empty())
      {
        int toKill = q.front();
        nxt[prv[toKill]] = nxt[toKill];
        prv[nxt[toKill]] = prv[toKill];
        if(prv[toKill] >= 0 && nxt[toKill] < n && a[prv[toKill]] > a[nxt[toKill]])
          nq.push(nxt[toKill]);
        q.pop(), alive --;
      }
      while (!nq.empty())
      {
        q.push(nq.front());
        nq.pop();
      }
    }

    printf("%d\n", ans);
  }
 
  return 0;
}