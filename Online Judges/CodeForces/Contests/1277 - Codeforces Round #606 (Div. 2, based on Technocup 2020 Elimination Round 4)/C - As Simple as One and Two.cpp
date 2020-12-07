#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char s[maxN];
bool removed[maxN];

int main()
{
  int tests; scanf("%d", &tests);
  while (tests --)
  {
    scanf(" %s", s); n = strlen(s);
    vector<int> ans;
    for (int i = 0; i < n; i ++) removed[i] = false;

    for (int i = 2; i < n; i ++)
    {
      if (s[i - 2] == 't' && s[i - 1] == 'w' && s[i] == 'o')
      {
        if (i + 2 < n && s[i + 1] == 'n' && s[i + 2] == 'e')
          ans.push_back(i), removed[i] = true;
        else
          ans.push_back(i - 1), removed[i - 1] = true;
      }
      if (s[i - 2] == 'o' && s[i - 1] == 'n' && s[i] == 'e' && !removed[i - 2])
        ans.push_back(i - 1), removed[i - 1];
    }

    printf("%d\n", (int) ans.size());
    if (ans.empty()) printf("\n");
    else for (int i = 0; i < ans.size(); i ++) printf("%d%c", ans[i] + 1, i < ans.size() - 1 ? ' ' : '\n');
  }
  return 0;
}
