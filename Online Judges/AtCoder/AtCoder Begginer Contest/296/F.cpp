#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n;
int a[maxN], b[maxN];
int pb[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    map<int, int> aa, bb;
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &a[i]);
      --a[i];
      ++aa[a[i]];
    }
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &b[i]);
      --b[i];
      pb[b[i]] = i;
      ++bb[b[i]];
    }

    bool ans = false;
    if (aa == bb)
    {
      if (aa.size() < n)
        ans = true;
      else
      {
        for (int i = 0; i + 2 < n; ++i)
        {
          if (a[i] != b[i])
          {
            int y = pb[b[i]];
            int z = i + 1;
            if (z == y) ++z;
            swap(pb[b[i]], pb[b[y]]);
            swap(b[y], b[i]);
            swap(a[y], a[z]);
          }
        }
        ans = a[n - 2] == b[n - 2] && a[n - 1] == b[n - 1];
      }
    }

    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
