#include <bits/stdc++.h>
using namespace std;
int x, y, a, b;

void allGames(vector<pair<int, int> > &games, int i, int j)
{
  if (j >= i || i > x || j > y) return;
  for (int k = j; k <= min(y, i - 1); k ++)
    games.push_back({i, k});
  allGames(games, i + 1, j);
}

int main()
{
  scanf("%d %d %d %d", &x, &y, &a, &b);

  vector<pair<int, int> > games;
  allGames(games, max(a, b + 1), b);

  printf("%d\n", (int) games.size());
  for (auto i: games)
    printf("%d %d\n", i.first, i.second);

  return(0);
}