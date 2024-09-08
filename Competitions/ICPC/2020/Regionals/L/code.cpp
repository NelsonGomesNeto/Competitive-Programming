#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4; int n, x;
struct Act
{
  int s, d;
  void read() { scanf("%d %d", &s, &d); }
  bool operator<(const Act &other) const { return s < other.s; };
};
Act acts[maxN];

int main()
{
  while (~scanf("%d %d", &n, &x))
  {
    for (int i = 0; i < n; i++)
      acts[i].read();

    pair<int, int> ans = make_pair((int)1e9, (int)1e9);
    for (int i = 0; i <= 8 * 60; i++)
    {
      pair<int, int> curr = make_pair(0, i);
      for (int j = 0; j < n; j++)
      {
        int b = 0;

        // i + k * x >= s
        // (s - i) / x
        int init = max(0, acts[j].s - i);
        int k = init / x;
        if (i + k * x < acts[j].s) k++;

        int now = i + k * x;
        int rem = acts[j].s + acts[j].d - now;

        if (rem >= 0) b += rem / x + 1;

        DEBUG printf("\t%d %d - %d %d\n", i, b, now, rem);

        curr.first += b;
      }
      ans = min(ans, curr);
    }

    printf("%d %d\n", ans.second, ans.first);
  }
  return 0;
}