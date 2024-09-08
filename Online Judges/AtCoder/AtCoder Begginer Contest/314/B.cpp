#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n;
vector<int> a[maxN];

int main()
{
  while (~scanf("%d", &n)) {
    for (int i = 0; i < n; ++i) {
      int c;
      scanf("%d", &c);
      a[i].clear();
      a[i].resize(c);
      for (int& aa : a[i]) scanf("%d", &aa);
    }

    int x;
    scanf("%d", &x);

    vector<pair<int, int>> ans;
    for (int i = 0; i < n; ++i) {
      bool betted_on_x = false;
      for (int aa : a[i]) betted_on_x |= aa == x;
      if (betted_on_x)
        ans.push_back(make_pair((int)a[i].size(), i));
    }
    sort(ans.begin(), ans.end());
    vector<pair<int, int>> fewer;
    for (int i = 0; i < ans.size(); ++i)
    {
      if (ans[i].first > ans[0].first)
        break;
      fewer.push_back(ans[i]);
    }
    ans = fewer;

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); ++i)
      printf("%d%c", ans[i].second + 1, i + 1 < ans.size() ? ' ' : '\n');
  }
  return 0;
}
