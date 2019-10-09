#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
struct Card { int white, black; void read() { scanf("%d %d", &white, &black); } };
Card cards[maxN];
int cnt[2][2*maxN];
map<int, int> colorMap;
vector<int> colors, uniqueColors;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(cnt, 0, sizeof(cnt)), colors.clear(), colorMap.clear();
    for (int i = 0; i < n; i ++)
    {
      cards[i].read();
      colors.push_back(cards[i].white), colors.push_back(cards[i].black);
    }
    sort(colors.begin(), colors.end());
    for (int c: colors)
      if (!colorMap.count(c))
        colorMap[c] = colorMap.size();
    for (int i = 0; i < n; i ++)
    {
      cards[i].white = colorMap[cards[i].white], cards[i].black = colorMap[cards[i].black];
      cnt[0][cards[i].white] ++;
      if (cards[i].white != cards[i].black) cnt[1][cards[i].black] ++;
    }
    // uniqueColors = colors;
    // sort(uniqueColors.begin(), uniqueColors.end());
    // uniqueColors.resize(distance(uniqueColors.begin(), unique(uniqueColors.begin(), uniqueColors.end())));
    // for (int i = 0; i < n; i ++)
    // {
    //   cards[i].white = lower_bound(uniqueColors.begin(), uniqueColors.end(), cards[i].white) - uniqueColors.begin();
    //   cards[i].black = lower_bound(uniqueColors.begin(), uniqueColors.end(), cards[i].black) - uniqueColors.begin();
    //   cnt[0][cards[i].white] ++;
    //   if (cards[i].white != cards[i].black) cnt[1][cards[i].black] ++;
    // }

    int ans = 1e9;
    // for (int c = 0; c < uniqueColors.size(); c ++)
    for (int c = 0; c < colorMap.size(); c ++)
      if (cnt[0][c] + cnt[1][c] >= ((n + 1) >> 1))
        ans = min(ans, max(0, ((n + 1) >> 1) - cnt[0][c]));
    if (ans == 1e9) ans = -1;
    printf("%d\n", ans);
  }
  return 0;
}