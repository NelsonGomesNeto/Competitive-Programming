#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n; int t;
struct Card
{
  int color;
  int rank;
};
Card cards[maxN];

int main()
{
  while (~scanf("%d %d", &n, &t))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &cards[i].color);
    for (int i = 0; i < n; ++i)
      scanf("%d", &cards[i].rank);

    int target = cards[0].color;
    for (int i = 0; i < n; ++i)
      if (cards[i].color == t)
        target = t;

    int winner = -1;
    for (int i = 0; i < n; ++i)
      if (cards[i].color == target && (winner == -1 || cards[winner].rank < cards[i].rank))
        winner = i;
    printf("%d\n", winner + 1);
  }
  return 0;
}
