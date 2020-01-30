#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, k;
char letters[4] = "SET";
set<string> all;
string cards[maxN];

char getDifferent(char a, char b)
{
  for (int i = 0; i < 3; i ++)
    if (letters[i] != a && letters[i] != b)
      return letters[i];
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    all.clear();
    char card[k + 1];
    for (int i = 0; i < n; i ++)
    {
      scanf("%s", card);
      cards[i] = string(card);
      all.insert(cards[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i ++)
      for (int j = i + 1; j < n; j ++)
      {
        string wanted = cards[i];
        for (int o = 0; o < k; o ++)
          if (cards[i][o] == cards[j][o])
            wanted[o] = cards[i][o];
          else
            wanted[o] = getDifferent(cards[i][o], cards[j][o]);
        ans += all.count(wanted) != 0;
      }
    printf("%d\n", ans / 3);
  }
  return 0;
}
