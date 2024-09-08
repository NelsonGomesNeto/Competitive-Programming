#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int p[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &p[i]);
      // p[i]--;
    }

    vector<int> ans;
    bool can = true;
    for (int k = 0; k < n; k++)
      for (int i = 0; i < n; i++)
        if (p[i] < i)
        {
          int base = p[i];
          for (int j = i - 1; j >= base; j--)
            // if (done.count(j))
            // {
            //   can = false;
            //   break;
            // }
            // else
            {
              swap(p[j], p[j + 1]);
              DEBUG printf("\tswap(%d, %d) [%d, %d]\n", j, j + 1, p[j] + 1, p[j + 1] + 1);
              ans.push_back(j);
            }
        }

    for (int i = 0; i < n; i++)
      printf("%d%c", p[i] + 1, i < n - 1 ? ' ': '\n');

    // can &= ans.size() == n - 1;
    for (int i = 0; i < n; i++)
      if (i != p[i])
        can = false;

    if (can)
    {
      for (int i = 0; i < ans.size(); i++)
        printf("%d\n", ans[i]);
    }
    else printf("-1\n");
  }
  return 0;
}