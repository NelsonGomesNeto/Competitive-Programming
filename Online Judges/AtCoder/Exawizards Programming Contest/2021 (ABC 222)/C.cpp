#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50, maxM = 100; int n, m;
char a[2*maxN][maxM + 1];

struct Player
{
  int i, score;
  bool operator<(const Player &other) const
  {
    return score < other.score || (score == other.score && i > other.i);
  }
};

// G > C, C > P, P > G
int mapMove[256];
int check(int i, int j, int round)
{
  DEBUG printf("\t\t%c - %d | %c - %d\n", a[i][round], mapMove[a[i][round]], a[j][round], mapMove[a[j][round]]);
  if ((mapMove[a[i][round]] + 1) % 3 == mapMove[a[j][round]])
    return 1;
  swap(i, j);
  if ((mapMove[a[i][round]] + 1) % 3 == mapMove[a[j][round]])
    return -1;
  return 0;
}

int main()
{
  mapMove['G'] = 0, mapMove['C'] = 1, mapMove['P'] = 2;

  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < 2*n; i++)
      scanf(" %s", a[i]);

    priority_queue<Player> pq, nxt;
    for (int i = 0; i < 2*n; i++) pq.push(Player{i, 0});

    for (int i = 0; i < m; i++)
    {
      while (!nxt.empty()) nxt.pop();

      while (!pq.empty())
      {
        Player a = pq.top(); pq.pop();
        Player b = pq.top(); pq.pop();

        int res = check(a.i, b.i, i);
        DEBUG printf("\t%d - %d %d - %d\n", i, a.i + 1, b.i + 1, res);
        if (res == 1) a.score++;
        else if (res == -1) b.score++;

        nxt.push(a);
        nxt.push(b);
      }

      pq = nxt;
    }

    while (!pq.empty())
    {
      Player a = pq.top(); pq.pop();
      DEBUG printf("%d - %d\n", a.i + 1, a.score);
      printf("%d\n", a.i + 1);
    }
  }
  return 0;
}