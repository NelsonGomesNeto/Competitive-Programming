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

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    vector<int> ans[2];
    int turn = 0;
    for (int i = 0; i < n; i++)
    {
      if (i + 1 < n && ((!ans[turn].empty() && ans[turn].back() == a[i + 1]) || (!ans[!turn].empty() && ans[!turn].back() == a[i + 1])))
      {
        if (!ans[turn].empty() && ans[turn].back() == a[i + 1])
          ans[turn].push_back(a[i]);
        else // (!ans[!turn].empty() && ans[!turn].back() == a[i + 1])
          ans[!turn].push_back(a[i]);
      }
      else if (!ans[turn].empty() && ans[turn].back() == a[i] && (ans[!turn].empty() || ans[!turn].back() != a[i]))
      {
        ans[!turn].push_back(a[i]);
        // turn = !turn;
      }
      else
        ans[turn].push_back(a[i]);
    }
    makeUnique(ans[turn]);
    makeUnique(ans[!turn]);

    printf("%ld\n", ans[turn].size() + ans[!turn].size());
  }
  return 0;
}
