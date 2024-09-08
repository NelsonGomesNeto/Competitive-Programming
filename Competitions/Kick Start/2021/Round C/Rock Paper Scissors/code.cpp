#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 60;
int w, e;
char choices[4] = "RPS";
double memo[maxN][maxN][maxN]; int path[maxN][maxN][maxN];

double solve(int r = 0, int p = 0, int s = 0)
{
  int i = r + p + s;
  if (i == maxN) return 0;
  double &ans = memo[r][p][s]; int &choice = path[r][p][s];
  if (ans != -1) return ans;

  double rock, paper, scissors;
  ans = 0;
  if (i == 0)
  {
    double prob = 1.0 / 3;
    rock = solve(r + 1, p, s) + prob * (w + e);
    paper = solve(r, p + 1, s) + prob * (w + e);
    scissors = solve(r, p, s + 1) + prob * (w + e);
  }
  else
  {
    double rp = (double)s/i, pp = (double)r/i, sp = (double)p/i;
    rock = solve(r + 1, p, s) + sp*w + rp*e;
    paper = solve(r, p + 1, s) + rp*w + pp*e;
    scissors = solve(r, p, s + 1) + pp*w + sp*e;
  }
  if (rock >= paper && rock >= scissors) choice = 0;
  else if (paper >= rock && paper >= scissors) choice = 1;
  else choice = 2;
  ans = max({rock, paper, scissors});

  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  int x; scanf("%d", &x);
  double avg = 0;
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &w, &e);

    for (int i = 0; i < maxN; i++)
      for (int j = 0; j < maxN; j++)
        for (int k = 0; k < maxN; k++)
          memo[i][j][k] = path[i][j][k] = -1;
    double best = solve();
    avg += best;
    DEBUG printf("\t%lf\n", best);

    string ans = "";
    for (int r = 0, p = 0, s = 0; r + p + s < maxN;)
    {
      int &choice = path[r][p][s];
      assert(choice >= 0 && choice <= 2);
      ans += choices[choice];
      if (choice == 0) r++;
      else if (choice == 1) p++;
      else s++;
    }

    printf("Case #%d: %s\n", tt, ans.c_str());
  }
  DEBUG printf("%lf\n", avg / t);
  return 0;
}