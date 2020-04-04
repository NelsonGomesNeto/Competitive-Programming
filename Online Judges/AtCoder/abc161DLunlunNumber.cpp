#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxK = 1e5;
lli ans[maxK + 1];

int main()
{
  priority_queue<lli, vector<lli>, greater<lli>> q;
  for (int i = 1; i <= 9; i ++) q.push(i);
  int d = 0;
  while (!q.empty() && d <= maxK)
  {
    lli u = q.top(); q.pop();
    ans[d++] = u;
    int b = u % 10;
    if (q.size() <= maxK)
    {
      for (int j = -1; j <= 1; j++)
        if (b + j >= 0 && b + j <= 9)
          q.push(u * 10 + b + j);
    }
  }

  lli k;
  while (scanf("%lld", &k) != EOF)
    printf("%lld\n", ans[k - 1]);

  return 0;
}