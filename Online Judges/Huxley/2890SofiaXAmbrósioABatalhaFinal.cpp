#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, r;
struct Card
{
  int atk, life, jump;
  void read() { scanf("%d %d %d", &atk, &life, &jump); }
  int turnsToKill(Card &other) { return other.life / atk + (other.life % atk != 0); }
};
Card sofia[maxN][maxN], ambrosio[maxN][maxN];
struct Pos
{
  int i, j;
  void add(int k) { i += (j + k) / n; j = (j + k) % n; }
  void print(string name) { printf("%s: (%d, %d)\n", name.c_str(), i, j); }
  bool operator>=(const Pos &other) { return i > other.i || (i == other.i && j >= other.j); } 
};
Pos sp, ap, start = {0, 0}, winp;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        sofia[i][j].read();
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        ambrosio[i][j].read();
    DEBUG {
      for (int i = 0; i < n; i ++)
          for (int j = 0; j < n; j ++)
            printf("(%d, %d, %d)%c", sofia[i][j].atk, sofia[i][j].life, sofia[i][j].jump, j < n - 1 ? ' ' : '\n');
      for (int i = 0; i < n; i ++)
          for (int j = 0; j < n; j ++)
            printf("(%d, %d, %d)%c", ambrosio[i][j].atk, ambrosio[i][j].life, ambrosio[i][j].jump, j < n - 1 ? ' ' : '\n');
    }
    
    scanf("%d", &r);

    int winner = -1;
    winp = {n - 1, n - 1};
    sp = ap = start;
    while (r -- && winner == -1)
    {
      int sturns = sofia[sp.i][sp.j].turnsToKill(ambrosio[ap.i][ap.j]);
      int aturns = ambrosio[ap.i][ap.j].turnsToKill(sofia[sp.i][sp.j]);

      if (sturns <= aturns)
        sp.add(sofia[sp.i][sp.j].jump);
      else
        ap.add(ambrosio[ap.i][ap.j].jump);

      if (sp >= winp)
        winner = 0, sp = winp;
      else if (ap >= winp)
        winner = 1, ap = winp;
    }
    sp.print("Sofia");
    ap.print("Ambrosio");
    if (winner == -1)
      printf("Ninguem venceu\n");
    else
      printf("%s venceu\n", winner == 0 ? "Sofia" : "Ambrosio");
  }
  return 0;
}