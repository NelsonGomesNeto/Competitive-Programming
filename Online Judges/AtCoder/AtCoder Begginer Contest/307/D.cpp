#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n;
char ss[maxN + 1];
string s;
int toRemove[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    fill(toRemove, toRemove+n, -1);
    scanf(" %s", ss);
    s = string(ss);

    stack<int> open;
    for (int i = 0; i < n; ++i)
    {
      const char c = s[i];
      if (c == '(') open.push(i);
      if (c == ')' && !open.empty())
      {
        toRemove[open.top()] = toRemove[i] = open.top();
        open.pop();
      }
    }

    DEBUG
    for (int i = 0; i < n; ++i)
      printf("\t%d %c %d\n", i, s[i], toRemove[i]);

    for (int i = 0; i < n; ++i)
      if (toRemove[i] == i)
      {
        int j = i;
        while (j + 1 < n && toRemove[j + 1] != i)
        {
          toRemove[j + 1] = i;
          ++j;
        }
        DEBUG printf("\t\t%d %d\n", i, j);
        i = j + 1;
      }

    DEBUG
    for (int i = 0; i < n; ++i)
      printf("\t%d %c %d\n", i, s[i], toRemove[i]);

    string ans;
    for (int i = 0; i < n; ++i)
      if (toRemove[i] == -1)
        ans.push_back(s[i]);
    printf("%s\n", ans.c_str());
  }
  return 0;
}
