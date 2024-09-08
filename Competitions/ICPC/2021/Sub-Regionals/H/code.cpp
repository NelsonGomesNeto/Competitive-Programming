#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, k;

struct Ball
{
  int i, c;
  void read() { scanf("%d %d", &i, &c); i--, c--; }
};
Ball bs[maxN];
set<int> colPos[maxN];

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    for (int i = 0; i < k; i++) colPos[i].clear();

    for (int i = 0; i < n; i++)
    {
      bs[i].read();
      colPos[bs[i].c].insert(i);
    }

    bool can = true;
    for (int i = 0; i < n; i++)
      if (!colPos[bs[i].c].count(bs[i].i))
        can = false;
    printf("%s\n", can ? "Y" : "N");
  }
  return 0;
}
