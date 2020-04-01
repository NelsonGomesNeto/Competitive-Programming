#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int digits(int num)
{
  int d = num == 0;
  while (num)
    num /= 10, d ++;
  return d;
}

int main()
{
  int n, m;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    vector<int> ans(n, -1);
    bool can = true;
    while (m --)
    {
      int s, c; scanf("%d %d", &s, &c);
      if (ans[s - 1] != -1 && ans[s - 1] != c)
        can = false;
      ans[s - 1] = c;
    }

    if (ans[0] == -1)
      ans[0] = n == 1 ? 0 : 1;
    for (int i = 1; i < n; i ++)
      if (ans[i] == -1)
        ans[i] = 0;
    reverse(ans.begin(), ans.end());

    int num = 0;
    for (int i = 0, p = 1; i < n; i ++, p *= 10)
      num += p * ans[i];
    if (can)
      can = digits(num) == n;
    printf("%d\n", can ? num : -1);
  }
  return 0;
}