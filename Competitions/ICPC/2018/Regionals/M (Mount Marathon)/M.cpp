#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  deque<pair<int, int>> cards;
  for (int i = 0, c; i < n; i ++)
  {
    scanf("%d", &c);
    cards.push_back({c, c});
  }

  for (int i = 0; i < cards.size() - 1; i ++)
    if (cards[i].second >= cards[i + 1].first)
    {
      cards[i + 1].first = cards[i].first;
      cards.erase(cards.begin()+i);
      i --;
    }
  DEBUG for (int i = 0; i < cards.size(); i ++)
    printf("\t(%d, %d)\n", cards[i].first, cards[i].second);
  printf("%d\n", (int) cards.size());
  return(0);
}