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
      p[i]--;
    }

    set<int> done;
    vector<int> ans;
    bool can = true;
    for (int i = 0; i < n && can; i++)
      if (p[i] < i)
      {
        int base = p[i];
        for (int j = i - 1; j >= base; j--)
          if (done.count(j))
          {
            can = false;
            break;
          }
          else
          {
            done.insert(j);
            swap(p[j], p[j + 1]);
            DEBUG printf("\tswap(%d, %d) [%d, %d]\n", j, j + 1, p[j] + 1, p[j + 1] + 1);
            ans.push_back(j + 1);
          }
      }

    can &= ans.size() == n - 1;
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