#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int cx, cy;
struct Point
{
  int x, y, idx;
  void read() { scanf("%d %d", &x, &y); cx+=x, cy+=y; }
  bool operator<(const Point &other) const { return x < other.x || (x == other.x && y < other.y); }
};
Point groups[3][maxN];

int main()
{
  auto rng = default_random_engine {};

  scanf("%d", &n);
  cx = cy = 0;
  for (int g = 0; g < 3; g++)
  {
    for (int i = 0; i < n; i++)
    {
      groups[g][i].read();
      groups[g][i].idx = i;
    }
    shuffle(groups[g], groups[g]+n, rng);
  }

  for (int i = 0; i < n; i++)
    printf("%d %d %d\n", groups[0][i].idx + 1, groups[1][i].idx + 1, groups[1][i].idx + 1);

  return 0;
}