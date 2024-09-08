#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int a[maxN];

void makeUnique(vector<int> &arr)
{
  arr.resize(distance(arr.begin(), unique(arr.begin(), arr.end())));
}

deque<int> pos[maxN + 1];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i <= n; i++)
      pos[i].clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      pos[a[i]].push_back(i);
    }

    vector<int> ans[2];
    int turn = 0;
    for (int i = 0; i < n; i++)
    {
      if (ans[turn].empty() || ans[turn].back() == a[i])
        ans[turn].push_back(a[i]);
      else if (ans[!turn].empty() || ans[!turn].back() == a[i])
        ans[!turn].push_back(a[i]);
      else if (i != n - 1
                && !ans[turn].empty() && !ans[!turn].empty()
                && (!pos[ans[turn].back()].empty()
                      && (pos[ans[!turn].back()].empty()
                          || (pos[ans[turn].back()] < pos[ans[!turn].back()])
                         )
                    )
              )
        ans[!turn].push_back(a[i]);
      else
        ans[turn].push_back(a[i]);

      pos[a[i]].pop_front();
    }

    DEBUG
      for (int i = 0; i < 2; i++)
      {
        printf("\t");
        for (int j = 0; j < ans[i].size(); j++)
          printf("%d ", ans[i][j]);
        printf("\n");
      }

    makeUnique(ans[turn]);
    makeUnique(ans[!turn]);

    printf("%ld\n", ans[turn].size() + ans[!turn].size());
  }
  return 0;
}
