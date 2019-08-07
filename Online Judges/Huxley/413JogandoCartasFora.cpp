#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) && n)
  {
    deque<int> card(n);
    for (int i = 0; i < n; i ++)
      card[i] = 1 + i;

    vector<int> discarted;
    while (card.size() >= 2)
    {
      discarted.push_back(card[0]);
      card.pop_front();
      card.push_back(card[0]);
      card.pop_front();
    }
    printf("Discarded cards:");
    for (int i = 0; i < discarted.size(); i ++)
      printf(" %d%s", discarted[i], i < discarted.size() - 1 ? "," : "\0");
    printf("\nRemaining card: %d\n", card[0]);
  }
  return(0);
}