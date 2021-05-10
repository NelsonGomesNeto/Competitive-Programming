#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5, maxIt = 50; int n, q;
int a[maxN];
vector<int> pos[maxN + 1];

int main()
{
  random_device rd;  //Will be used to obtain a seed for the random number engine
  mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

  while (~scanf("%d %d", &n, &q))
  {
    for (int i = 0; i <= n; i++)
      pos[i].clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      pos[a[i]].push_back(i);
    }

    for (int i = 0; i < q; i++)
    {
      int l, r; scanf("%d %d", &l, &r); l--, r--;
      uniform_int_distribution<> distrib(l, r);

      int mostRep, freq = -1;
      for (int it = 0; it < maxIt; it++)
      {
        int j = a[distrib(gen)];
        int curr = upper_bound(pos[j].begin(), pos[j].end(), r) - lower_bound(pos[j].begin(), pos[j].end(), l);
        if (curr > freq)
          freq = curr, mostRep = j;
      }

      DEBUG printf("\t%d %d\n", mostRep, freq);
      printf("%d\n", max(1, freq - (r - l + 1 - freq)));
    }
  }
  return 0;
}