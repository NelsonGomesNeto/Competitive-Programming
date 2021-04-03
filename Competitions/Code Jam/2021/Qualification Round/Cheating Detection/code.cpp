#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100, maxM = 1e4; int n = 100, m = 1e4, p;
const int extremeProblems = 1000;
const int neighbors = 2;
char s[maxN][maxM + 1];

struct Competidor
{
  int idx, corrects, wrongs;
  bool operator<(const Competidor &other) const { return corrects < other.corrects; }
};
Competidor competidors[maxN];

struct Problem
{
  int idx, corrects, wrongs;
  bool operator<(const Problem &other) const { return corrects < other.corrects; }
};
Problem problems[maxM];

double sumEasy[maxN], sumHard[maxN];

int main()
{
  std::default_random_engine generator;
  std::uniform_int_distribution<int> coin(0, 1);

  int t; scanf("%d", &t);
  scanf("%d", &p);

  for (int tt = 1; tt <= t; tt++)
  {
    for (int i = 0; i < n; i++)
      competidors[i] = Competidor{i, 0, 0};
    for (int j = 0; j < m; j++)
      problems[j] = Problem{j, 0, 0};
    
    for (int i = 0; i < n; i++)
      scanf(" %s", s[i]);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (s[i][j] == '1')
          problems[j].corrects++, competidors[i].corrects++;
        else
          problems[j].wrongs++, competidors[i].wrongs++;
    sort(problems, problems+m);
    reverse(problems, problems+m);
    sort(competidors, competidors+n);
    reverse(competidors, competidors+n);

    for (int i = 0; i < n; i++)
    {
      sumEasy[competidors[i].idx] = sumHard[competidors[i].idx] = 0;
      for (int j = 0; j < extremeProblems; j++)
        sumEasy[competidors[i].idx] += s[competidors[i].idx][problems[j].idx] == '1';
      for (int j = 0; j < extremeProblems; j++)
      {
        // harder problems should be more valuable, it helps but it's not required for it to pass
        sumHard[competidors[i].idx] += (extremeProblems - j) * (s[competidors[i].idx][problems[m - j - 1].idx] == '1');
      }
    }

    int ans = 0;
    double cheaterDelta = -1e18;
    for (int i = 0; i < n; i++)
    {
      int lo = i - (neighbors >> 1), hi = i + (neighbors >> 1);
      while (lo < 0)
        lo++, hi++;

      double delta = 0;
      double averageEasy = 0, averageHard = 0;
      for (int j = lo; j <= hi; j++)
        if (j != i)
        {
          // delta += sumEasy[competidors[i].idx] - sumEasy[competidors[j].idx] + sumHard[competidors[i].idx] - sumHard[competidors[j].idx];
          averageEasy += sumEasy[competidors[j].idx];
          averageHard += sumHard[competidors[j].idx];
        }
      averageEasy /= neighbors, averageHard /= neighbors;

      delta += sumEasy[competidors[i].idx] - averageEasy + sumHard[competidors[i].idx] - averageHard;
 
      if (delta > cheaterDelta)
        cheaterDelta = delta, ans = competidors[i].idx;
    }

    printf("Case #%d: %d\n", tt, ans + 1);
  }
  return 0;
}