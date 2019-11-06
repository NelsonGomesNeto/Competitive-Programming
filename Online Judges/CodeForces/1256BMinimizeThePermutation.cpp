#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    vector<int> a;
    for (int i = 0; i < n; i ++)
    {
      int aa; scanf("%d", &aa);
      a.push_back(aa);
    }

    bool done[n - 1]; memset(done, false, sizeof(done));
    for (int j = 0; j < n; j ++)
      for (int i = n - 2; i >= 0; i --)
        if (a[i] > a[i + 1] && !done[i])
          swap(a[i], a[i + 1]), done[i] = true;
    for (int i = 0; i < n; i ++)
      printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}