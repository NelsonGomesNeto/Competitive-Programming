#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 4e5; int n;
int p[maxN];

struct Ans
{
  int g, s, b;
  int value() { return g + s + b; }
  bool operator<(const Ans &other) const
  {
    return g + s + b < other.g + other.s + other.b;
  }
  void print() { printf("%d %d %d\n", g, s, b); }
};

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
      scanf("%d", &p[i]);

    int limit = (n >> 1) - 1;
    while (limit + 1 < n && limit > 0 && p[limit + 1] == p[limit]) limit --;

    Ans ans = Ans{0, 0, 0}, worst = Ans{-maxN, -maxN, -maxN};
    for (int i = 0; i < n; i ++)
    {
      Ans now = worst;
      int j = i;
      while (j + 1 < n && p[j + 1] == p[i]) j ++;
      now.g = j + 1;

      int k = j + now.g + 1;
      while (k + 1 < n && p[k + 1] == p[k]) k ++;
      now.s = k - j;

      int o = limit;
      now.b = o - k;
      if (now.s <= now.g || now.b <= now.g || now.value() > (n >> 1))
        now = worst;

      DEBUG {
        printf("\t%d %d %d %d | %d - ", i, j, k, o, now.value());
        now.print();
      }

      if (ans < now)
        ans = now;

      i = j;
    }
    ans.print();
  }
  return 0;
}
