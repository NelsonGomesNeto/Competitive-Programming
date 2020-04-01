#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxA = 100 + 1;
struct Pos { int i, j; };
Pos pos[maxA];
bool marked[3][3];

bool won()
{
  for (int i = 0; i < 3; i ++)
  {
    int s1 = 0, s2 = 0;
    for (int j = 0; j < 3; j ++)
      s1 += marked[i][j], s2 += marked[j][i];
    if (s1 == 3 || s2 == 3) return true;
  }
  int s1 = 0, s2 = 0;
  for (int i = 0; i < 3; i ++)
    s1 += marked[i][i], s2 += marked[i][2 - i];
  return s1 == 3 || s2 == 3;
}

int main()
{
  memset(pos, -1, sizeof(pos));
  for (int i = 0; i < 3; i ++)
    for (int j = 0; j < 3; j ++)
    {
      int a; scanf("%d", &a);
      pos[a] = {i, j};
    }

  int n; scanf("%d", &n);
  while (n --)
  {
    int b; scanf("%d", &b);
    if (pos[b].i != -1)
      marked[pos[b].i][pos[b].j] = true;
  }
  printf("%s\n", won() ? "Yes" : "No");

  return 0;
}