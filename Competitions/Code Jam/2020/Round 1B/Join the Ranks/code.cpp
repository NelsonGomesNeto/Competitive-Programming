#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

void print(vector<int> &cards)
{
  for (int i = 0; i < cards.size(); i++)
    printf("%d%c", cards[i], i < cards.size() - 1 ? ' ' : '\n');
}

bool done(vector<int> &cards)
{
  for (int i = 1; i < cards.size(); i++)
    if (cards[i - 1] > cards[i])
      return false;
  return true;
}

void execute(vector<int> &cards, int a, int b)
{
  vector<int> aux;
  for (int i = a, bb = b; bb > 0; bb--, i++) aux.push_back(cards[i]);
  for (int i = 0; i < a; i++) aux.push_back(cards[i]);
  for (int i = a + b; i < cards.size(); i++) aux.push_back(cards[i]);
  cards = aux;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int r, s; scanf("%d %d", &r, &s);
    vector<int> cards;
    for (int i = 0; i < s; i++)
      for (int j = 0; j < r; j++)
        cards.push_back(j);
    DEBUG print(cards);

    vector<pair<int, int>> ans;
    while (!done(cards))
    {
      // 01 20 12
      //   m  n
      // 2 0011 2
      // 001122
      vector<int> aux = cards;
      int m = 0;
      while (m < cards.size() && cards[m] == cards[0]) m++;
      int n = cards.size() - 1;
      while (n >= 0 && cards[n] == cards.back()) n--;
      execute(aux, m, n - m + 1);
      if (done(aux))
      {
        ans.push_back({m, n - m + 1});
        break;
      }

      //  i j    k
      // 01 2345 6789
      // 01 2340 1234
      int i = 0;
      while (i < cards.size() && cards[i] == cards[0]) i++;
      int j = i;
      while (j < cards.size() && cards[j] == cards[i]) j++;
      int k = j;
      while (k < cards.size() && cards[k] != cards[i]) k++;

      ans.push_back({j, k - j});
      execute(cards, j, k - j);

      DEBUG print(cards);
    }

    printf("Case #%d: %d\n", tt, (int)ans.size());
    for (auto &p: ans) printf("%d %d\n", p.first, p.second);
  }
  return 0;
}
/*
012012
200112
*/