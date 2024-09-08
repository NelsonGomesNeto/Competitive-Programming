#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n;
vector<int> a;

int main()
{
  while (~scanf("%d", &n))
  {
    a.clear();
    a.resize(n);
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);

    while (true)
    {
      bool changed = false;
      for (int i = 1; i < a.size(); ++i)
        if (abs(a[i - 1] - a[i]) > 1)
        {
          vector<int> toAdd;
          int l = a[i - 1], r = a[i];
          if (l > r) swap(l, r);
          for (int j = l + 1; j < r; ++j)
            toAdd.push_back(j);

          if (a[i - 1] > a[i]) reverse(toAdd.begin(), toAdd.end());

          a.insert(a.begin() + i, toAdd.begin(), toAdd.end());

          changed = true;
          break;
        }
      if (!changed) break;
    }

    for (int i = 0; i < a.size(); ++i)
      printf("%d%c", a[i], i + 1 < a.size() ? ' ' : '\n');
  }
  return 0;
}
