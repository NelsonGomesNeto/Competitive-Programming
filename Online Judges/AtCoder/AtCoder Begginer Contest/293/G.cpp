#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n, q;
int a[maxN];

vector<int> pos[maxN];

int main()
{
  while (~scanf("%d %d", &n, &q))
  {
    for (int i = 0; i < maxN; ++i) pos[i].clear();

    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &a[i]);
      --a[i];
      pos[i].push_back(i);
    }

    for (int i = 0; i < q; ++i)
    {
      int l, r;
      scanf("%d %d", &l, &r);
      --l, --r;


    }
  }
  return 0;
}
