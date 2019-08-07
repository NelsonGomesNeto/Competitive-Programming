#include <bits/stdc++.h>
using namespace std;

int main()
{
  int c; scanf("%d", &c);
  int ret[c][4];
  for (int j = 0; j < c; j ++)
    for (int i = 0; i < 4; i ++)
      scanf("%d", &ret[j][i]);

  vector<pair<int, int> > stars;
  int x, y;
  while (1)
  {
    if (scanf("%d %d", &x, &y) && (x == 0 && y == 0)) break;
    stars.push_back({x, y});
  }

  int done[(int) stars.size()]; memset(done, 0, sizeof(done));
  for (int i = 0; i < c; i ++)
  {
    int s = 0;
    for (int j = 0; j < stars.size(); j ++)
    {
      // if (done[j]) continue;
      x = stars[j].first; y = stars[j].second;
      if (x >= ret[i][0] && x <= ret[i][1] && y >= ret[i][2] && y <= ret[i][3])
      {
        done[j] = 1;
        s ++;
      }
    }
    printf("CEU #%d: %d estrelas\n", i + 1, s);
  }
  return(0);
}