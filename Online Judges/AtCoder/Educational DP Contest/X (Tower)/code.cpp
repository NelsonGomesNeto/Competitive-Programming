#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3, maxStrenght = 2e4 + 1, maxWeightSum = 1e7 + 1; int n;
const lli inf = 1e15;
struct Block
{
  int weight, strenght; lli value;
  void read() { scanf("%d %d %lld", &weight, &strenght, &value); }
  bool operator<(const Block &other) const { return weight + strenght > other.weight + other.strenght; }
};
Block blocks[maxN];

lli memo[maxN][maxStrenght + 1];
lli solve(int i = 0, int strenght = maxStrenght)
{
  if (i == n) return 0;
  lli &ans = memo[i][strenght];
  if (ans != -1) return ans;

  ans = solve(i + 1, strenght);
  if (strenght >= blocks[i].weight)
    ans = max(ans, blocks[i].value + solve(i + 1, min(blocks[i].strenght, strenght - blocks[i].weight)));
  return ans;
}

lli memo2[maxN][maxStrenght + 1];
lli solve2()
{
  memset(memo2, 0, sizeof(memo2));
  for (int i = maxStrenght; i >= blocks[0].weight; i--)
    memo2[0][i] = blocks[0].value;

  for (int i = 1; i < n; i++)
    for (int j = 0; j <= maxStrenght; j++)
    {
      memo2[i][j] = memo2[i - 1][j];
      if (j >= blocks[i].weight)
        memo2[i][j] = max(memo2[i][j], blocks[i].value + memo2[i - 1][min(j - blocks[i].weight, blocks[i].strenght)]);
    }
  lli ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j <= maxStrenght; j++)
      ans = max(ans, memo2[i][j]);
  return ans;
}

lli memo3[maxStrenght + 1];
lli solve3()
{
  memset(memo3, 0, sizeof(memo3));
  for (int i = 0; i < n; i++)
    for (int wsum = min(blocks[i].strenght, maxStrenght - blocks[i].weight); wsum >= 0; wsum--)
      memo3[wsum + blocks[i].weight] = max(memo3[wsum + blocks[i].weight], memo3[wsum] + blocks[i].value);
  return *max_element(memo3, memo3+maxStrenght+1);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      blocks[i].read();
    sort(blocks, blocks+n);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}