#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4; int n;
char s[maxN + 1];

int main()
{
  while (scanf("%s", s) != EOF)
  {
    getchar();
    n = strlen(s);
    vector<lli> inv;
    for (int i = 0; i < n - 1; i ++)
      if (s[i] != s[i + 1])
        inv.push_back(-(2*(i + 1) + 1));

    if (inv.empty())
    {
      printf("0\n%d\n", s[0] == 'H' ? 1 : -1);
      continue;
    }

    vector<lli> ans, aux;
    ans.push_back(1);
    ans.push_back(inv[0]);
    for (int j = 1; j < inv.size(); j ++)
    {
      aux = ans;
      ans.push_back(ans.back() * inv[j]);
      for (int i = 1; i < aux.size(); i ++)
        ans[i] += aux[i - 1] * inv[j];
    }

    if (s[n - 1] == 'A')
      for (int i = 0; i < ans.size(); i ++)
        ans[i] *= -1;

    printf("%d\n", (int) ans.size() - 1);
    for (int i = 0; i < ans.size(); i ++)
      printf("%lld%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
  }
  return 0;
}