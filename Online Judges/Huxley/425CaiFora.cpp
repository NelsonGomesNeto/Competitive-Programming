#include <bits/stdc++.h>
using namespace std;

const int maxN = 20; int n;
struct Player
{
  char name[17];
};
vector<Player> players;
int cards[52];

int main()
{
  while (scanf("%d", &n) && n)
  {
    players.clear();
    players.resize(n);
    for (int i = 0; i < n; i ++)
      scanf(" %s", players[i].name);
    for (int i = 0; i < 52; i ++)
      scanf("%d", &cards[i]);
    int at = 0;
    while (at + players.size() < 52)
    {
      list<int> toRemove; int smallest = 24;
      for (int i = 0; i < players.size(); i ++, at ++)
      {
        if (cards[at] < smallest)
          toRemove.clear(), smallest = cards[at];
        if (cards[at] == smallest)
          toRemove.push_back(i);
      }
      if (toRemove.size() == players.size()) break;
      reverse(toRemove.begin(), toRemove.end());
      for (int i: toRemove)
        players.erase(players.begin() + i);
    }
    for (int i = 0; i < players.size(); i ++)
      printf("%s%c", players[i].name, i < players.size() - 1 ? ' ' : '\n');
  }
  return 0;
}