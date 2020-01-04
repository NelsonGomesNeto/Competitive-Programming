#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
char s[maxN + 2];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    scanf(" %s", s);
    vector<int> ans;
    int at = n;
    while (at > m)
    {
      bool done = false;
      for (int j = m; j >= 1; j --)
        if (s[at - j] == '0')
        {
          at -= j;
          ans.push_back(j);
          done = true;
          break;
        }
      if (!done)
        break;
    }
    if (at > m) printf("-1\n");
    else
    {
      ans.push_back(at);
      reverse(ans.begin(), ans.end());
      for (int i = 0; i < ans.size(); i ++)
        printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
    }
  }
  return 0;
}