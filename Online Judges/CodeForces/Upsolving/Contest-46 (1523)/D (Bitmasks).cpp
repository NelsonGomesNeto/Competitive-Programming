#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxC = 60; int n, requiredFriends, m, p;
char s[maxN][maxC + 1];
vector<int> coinPos;

vector<bitset<maxN>> coins;
bitset<maxN> fullMask;
int best; lli bestMask;
void solve(int i = 0, bitset<maxN> curr = fullMask, lli currChoices = 0, int currCount = 0)
{
  if (curr.count() >= requiredFriends)
  {
    if (currCount > best)
      best = currCount, bestMask = currChoices;
  }
  else
    return;
  if (i == coins.size())
    return;

  int ci = coinPos[i];

  bitset<maxN> aux = curr & coins[i];
  if (aux == curr)
    solve(i + 1, aux, currChoices | (1LL << ci), currCount + 1);
  else
  {
    solve(i + 1, curr, currChoices, currCount);
    solve(i + 1, aux, currChoices | (1LL << ci), currCount + 1);
  }
}

int main()
{
  while (~scanf("%d %d %d", &n, &m, &p))
  {
    requiredFriends = ((n + 1) >> 1);

    fullMask = 0;
    for (int i = 0; i < n; i++) fullMask[i] = 1;

    for (int i = 0; i < n; i++)
      scanf(" %s", s[i]);

    for (int i = 0; i < m; i++)
    {
      bitset<maxN> now = 0; int cnt = 0;
      for (int j = 0; j < n; j++)
        if (s[j][i] == '1')
          now[j] = 1, cnt++;
      if (cnt >= requiredFriends)
        coins.push_back(now), coinPos.push_back(i);
    }

    best = -1;
    solve();
    for (int i = 0; i < m; i++)
      printf("%lld", (bestMask >> i) & 1);
    printf("\n");
  }
  return 0;
}