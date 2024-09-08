#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    stack<pair<int, int>> s;
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
      if (!s.empty() && a[i] == s.top().first)
      {
        if (a[i] == s.top().second + 1)
        {
          cnt -= s.top().second;
          s.pop();
        }
        else
          s.top().second++, cnt++;
      }
      else
      {
        s.push({a[i], 1});
        cnt++;
      }
      printf("%d\n", cnt);
    }
  }
  return 0;
}