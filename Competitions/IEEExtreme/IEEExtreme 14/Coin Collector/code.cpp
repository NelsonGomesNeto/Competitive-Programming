#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3 + 1; int n, m;
const lli inf = 1e10;
string sets[3][3] = {{"Zulian", "Razzashi", "Hakkari"},
                     {"Sandfury", "Skullsplitter", "Bloodscalp"},
                     {"Gurubashi", "Vilebranch", "Witherbark"}};
unordered_map<string, int> cardIdx, cardSet;

char ss[100];
struct Card
{
  int k, p;
  bool operator<(const Card &other) const { return p < other.p; }
};
vector<Card> cards[3][3];
lli prices[3][maxN];
lli memoprices[3][3][maxN];

int main()
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      cardIdx[sets[i][j]] = j, cardSet[sets[i][j]] = i;

  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        cards[i][j].clear();
    for (int i = 0; i < m; i++)
    {
      int k, p; scanf(" %s %d %d", ss, &k, &p);
      string s = string(ss);
      cards[cardSet[s]][cardIdx[s]].push_back({k, p});
    }
    DEBUG
      for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
          for (Card &c: cards[i][j])
            printf("\t%d %d - %d %d\n", i, j, c.k, c.p);

    // precalculate the price to buy x times the set i
    memset(memoprices, 0, sizeof(memoprices));
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        for (int x = 1; x < maxN; x++)
          memoprices[i][j][x] = inf;

    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        for (Card &c: cards[i][j])
          for (int x = maxN; x >= 1; x--)
            memoprices[i][j][x] = min(memoprices[i][j][x], c.p + memoprices[i][j][max(0, x - c.k)]);

    for (int i = 0; i < 3; i++)
      for (int x = 0; x < maxN; x++)
      {
        prices[i][x] = 0;
        for (int j = 0; j < 3; j++)
          prices[i][x] += memoprices[i][j][x];
      }

    lli ans = inf;
    for (int i = 0; i <= n; i++)
      for (int j = 0; i + j <= n; j++)
      {
        int k = n - (i + j);
        DEBUG printf("%d %d %d | %lld %lld %lld\n", i, j, k, prices[0][i], prices[1][j], prices[2][k]);
        ans = min(ans, prices[0][i] + prices[1][j] + prices[2][k]);
      }
    if (ans >= inf)
      printf("impossible\n");
    else
      printf("%lld\n", ans);
  }

  return 0;
}