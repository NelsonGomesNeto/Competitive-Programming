#include <bits/stdc++.h>
#define lli long long int
using namespace std;

struct Card
{
  char number, suit;
  void print(char end = '\n') { printf("%c%c%c", number, suit, end); }
  bool read() { scanf("%c%c", &number, &suit); return true; }
  bool match(Card &other) { return number == other.number || suit == other.suit; }
};
Card cards[52];
deque<stack<Card>> c;

int main()
{
  while (cards[0].read() && cards[0].number != '#')
  {
    c.clear();
    for (int i = 1; i < 52; i ++)
    {
      getchar();
      cards[i].read();
    }
    getchar();

    for (int i = 0; i < 52; i ++) c.push_back(stack<Card>({cards[i]}));

    for (int i = 0; i < c.size(); i ++)
      if (i - 3 >= 0 && c[i].top().match(c[i - 3].top()))
      {
        c[i - 3].push(c[i].top()); c[i].pop();
        if (c[i].empty()) c.erase(c.begin() + i);
        i = -1;
      }
      else if (i - 1 >= 0 && c[i].top().match(c[i - 1].top()))
      {
        c[i - 1].push(c[i].top()); c[i].pop();
        if (c[i].empty()) c.erase(c.begin() + i);
        i = -1;
      }

    printf("%d %s sobrando:", (int) c.size(), c.size() == 1 ? "pilha" : "pilhas");
    for (auto &s: c) printf(" %d", (int) s.size());
    printf("\n");
  }
  return(0);
}