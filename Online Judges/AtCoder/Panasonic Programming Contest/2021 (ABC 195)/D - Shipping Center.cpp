#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, m, q;
struct Baggage
{
  int size, value;
  void read() { scanf("%d %d", &size, &value); }
  bool operator<(const Baggage &other) const { return value > other.value || (value == other.value && size < other.size); }
};
Baggage items[maxN]; int boxes[maxN];


int main()
{
  while (~scanf("%d %d %d", &n, &m, &q))
  {
    for (int i = 0; i < n; i++)
      items[i].read();
    sort(items, items+n);
    for (int i = 0; i < m; i++)
      scanf("%d", &boxes[i]);

    for (int qq = 0; qq < q; qq++)
    {
      int lo, hi; scanf("%d %d", &lo, &hi); lo--, hi--;

      bool got[m]; memset(got, false, sizeof(got));
      int ans = 0;
      for (int i = 0; i < n; i++)
      {
        int bestBox = -1;
        for (int j = 0; j < m; j++)
          if (!got[j] && (j < lo || j > hi) && items[i].size <= boxes[j])
            if (bestBox == -1 || boxes[j] < boxes[bestBox])
              bestBox = j;
        if (bestBox != -1)
          got[bestBox] = true, ans += items[i].value;
      }

      printf("%d\n", ans);
    }
  }
  return 0;
}