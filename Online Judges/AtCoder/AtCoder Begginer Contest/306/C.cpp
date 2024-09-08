#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
int n;
int a[3*maxN];
vector<int> pos[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < maxN; ++i)
      pos[i].clear();

    for (int i = 0; i < 3*n; ++i)
    {
      scanf("%d", &a[i]);
      --a[i];
    }
    for (int i = 0; i < 3*n; ++i)
      pos[a[i]].push_back(i);

    vector<int> ans;
    for (int i = 0; i < 3*n; ++i)
      if (pos[a[i]][1] == i)
        ans.push_back(a[i]);
    for (int i = 0; i < ans.size(); ++i)
      printf("%d%c", ans[i] + 1, i + 1 < ans.size() ? ' ' : '\n');
  }
  return 0;
}
