#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 1e4, maxP = 20; int n, p;
int cards[maxN];
multiset<int> discard;
list<int> players[maxP];

int main()
{
  while (scanf("%d %d", &n, &p) && n + p)
  {
    DEBUG printf("<%d %d>\n", n, p);
    discard.clear();
    for (int i = 0; i < p; i ++) players[i].clear();

    for (int i = 0; i < n; i ++)
      scanf("%d", &cards[i]);

    for (int i = 0, at = 0; i < n; i ++)
    {
      bool repeat = false;
      if (!discard.empty() && discard.find(cards[i]) != discard.end())
      {
        players[at].push_back(cards[i]);
        players[at].push_back(cards[i]);
        discard.erase(discard.find(cards[i]));
        repeat = true;
      }
      if (!repeat)
        for (int j = 0; j < p; j ++)
          if (j != at && !players[j].empty() && players[j].back() == cards[i])
          {
            players[at].splice(players[at].end(), players[j]);
            players[at].push_back(cards[i]);
            repeat = true;
          }
      if (!repeat && !players[at].empty() && players[at].back() == cards[i])
      {
        players[at].push_back(cards[i]);
        repeat = true;
      }
      if (!repeat)
      {
        discard.insert(cards[i]);
        at = (at + 1) % p;
      }

      DEBUG {
        printf("%d\n\t", cards[i]);
        printf("%d ", (int) discard.size());
        for (int k = 0; k < p; k ++) printf("%d%c", (int) players[k].size(), k < p - 1 ? ' ' : '\n');
      }
    }

    list<int> winners; int winnersSize = 0;
    for (int i = 0; i < p; i ++)
    {
      if (players[i].size() > winnersSize)
        winnersSize = players[i].size(), winners.clear();
      if (players[i].size() == winnersSize)
        winners.push_back(i);
    }
    printf("%d ", winnersSize);
    int i = 0;
    for (int w: winners)
      printf("%d%c", w + 1, i ++ < winners.size() - 1 ? ' ' : '\n');
  }
  return(0);
}