#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int a[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; i++) pq.push(a[i]);

    bool can = true;
    bool leftOver = false;
    while (pq.size() > 2 - leftOver)
    {
      int l = pq.top(); pq.pop();
      int r = pq.top(); pq.pop();
      if (l == r) pq.push(l+1);
      else if (!leftOver)
      {
        pq.push(r);
        leftOver = true;
      }
      else
      {
        can = false;
        break;
      }
    }

    can &= pq.size() == 2 - leftOver;
    printf("%s\n", can ? "Y" : "N");
  }
  return 0;
}