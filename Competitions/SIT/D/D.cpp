#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, a, b;
char s[maxN + 1];

int main()
{
  while (~scanf("%d %d %d", &n, &a, &b))
  {
    scanf(" %s", s);

    vector<pair<int, int>> available;
    for (int i = 0; i < n; i++)
    {
      if (s[i] == '0')
      {
        int j = i;
        while (j + 1 < n && s[j + 1] == '0') j++;

        available.push_back({j - i + 1, i});

        i = j;
      }
    }

    vector<int> ans[2];
    for (auto &[ava, idx]: available)
    {
      DEBUG printf("\t%d %d\n", ava, idx);
      int sz = ava, curr = idx;
      while (sz > 1 && a)
      {
        ans[0].push_back(curr);
        ans[0].push_back(curr + 1);
        sz -= 2, curr += 2, a--;
      }

      while (sz > 0 && b)
      {
        ans[1].push_back(curr);
        sz -= 1, curr += 1, b--;
      }
    }

    if (!a && !b)
    {
      printf("YES\n");
      for (int i = 0; i < 2; i++)
      {
        for (int j = 0; j < ans[i].size(); j += 1 + !i)
        {
          if (j) printf("\n");
          printf("%d", ans[i][j] + 1);
          if (i == 0) printf(" %d", ans[i][j + 1] + 1);
        }
        printf("\n");
      }
    }
    else
      printf("NO\n");
  }
  return 0;
}