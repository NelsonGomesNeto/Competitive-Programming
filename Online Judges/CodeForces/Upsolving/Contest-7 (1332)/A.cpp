#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int o[4]; for (int i = 0; i < 4; i++) scanf("%d", &o[i]);
    int x, y, x1, y1, x2, y2; scanf("%d %d %d %d %d %d", &x, &y, &x1, &y1, &x2, &y2);
    bool ans = true;
    if (x2 - x1 == 0 && (o[0] > 0 || o[1] > 0))
      ans = false;
    if (x2 - x1 > 0 && ((o[0] > o[1] && x - (o[0] - o[1]) < x1)) || (o[1] > o[0] && x + (o[1] - o[0]) > x2))
      ans = false;
    if (y2 - y1 == 0 && (o[2] > 0 || o[3] > 0))
      ans = false;
    if (y2 - y1 > 0 && ((o[2] > o[3] && y - (o[2] - o[3]) < y1)) || (o[3] > o[2] && y + (o[3] - o[2]) > y2))
      ans = false;
    printf("%s\n", ans ? "YES" : "NO");
  }
  return 0;
}
