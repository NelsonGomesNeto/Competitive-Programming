#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 30; int n;
struct Trial
{
  int digits[12], corrects;
  void read()
  {
    for (int i = 0; i < 12; i++) scanf("%01d", &digits[i]);
    scanf("%d", &corrects);
  }
  void print(bool showCorrects = true)
  {
    for (int i = 0; i < 12; i++) printf("%01d", digits[i]);
    if (showCorrects) printf(" %d\n", corrects);
    else printf("\n");
  }
  bool operator<(const Trial &other) const
  {
    return corrects > other.corrects;
  }
};
Trial trials[maxN];

vector<pair<int, int>> possiblesFrequency[12];
vector<int> possibles[12];
int nxt[13];
vector<int> curr;
struct Ans
{
  vector<int> corrects;
  Trial ans;
  bool operator<(const Ans &other) const
  {
    return corrects < other.corrects;
  }
};
vector<Ans> leftAns, rightAns;
int cutPoint;
void solveLeft(int i, Trial &hehe)
{
  if (i == cutPoint)
  {
    leftAns.push_back(Ans{curr, hehe});
    return;
  }

  for (int d: possibles[i])
  {
    bool valid = true;
    for (int j = 0; j < n; j++)
    {
      curr[j] -= (d == trials[j].digits[i]);
      if (curr[j] < 0)
        valid = false;
    }
    if (valid)
    {
      hehe.digits[i] = d;
      solveLeft(i + 1, hehe);
    }
    for (int j = 0; j < n; j++)
      curr[j] += (d == trials[j].digits[i]);
  }
}
void solveRight(int i, Trial &hehe)
{
  if (i == cutPoint - 1)
  {
    Ans FOI = Ans{curr, hehe};
    auto it = lower_bound(leftAns.begin(), leftAns.end(), FOI);
    if (it != leftAns.end() && it->corrects == curr)
    {
      Ans foi = *it;
      leftAns.clear();
      leftAns.push_back(foi);
      rightAns.push_back(FOI);
    }
    // bool found = false;
    // for (int j = 0; j < leftAns.size() && !found; j++)
    // {
    //   found = true;
    //   for (int p = 0; p < n && found; p++)
    //     if (leftAns[j].corrects[p] + curr[p] != trials[p].corrects)
    //       found = false;
    //   if (found)
    //     rightAns.push_back(Ans{curr, hehe});
    // }
    return;
  }

  for (int d: possibles[i])
  {
    bool valid = true;
    for (int j = 0; j < n; j++)
    {
      curr[j] += (d == trials[j].digits[i]);
      if (curr[j] > trials[j].corrects)
        valid = false;
    }
    if (valid)
    {
      hehe.digits[i] = d;
      solveRight(i - 1, hehe);
    }
    for (int j = 0; j < n; j++)
      curr[j] -= (d == trials[j].digits[i]);
  }
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++) trials[i].read();
    sort(trials, trials+n);

    for (int i = 0; i < 12; i++)
    {
      for (int d = 0; d <= 9; d++)
      {
        bool cant = false;
        for (int j = n - 1; j >= 0 && trials[j].corrects == 0; j--)
          if (trials[j].digits[i] == d)
            cant = true;
        if (!cant)
        {
          int frequency = 0;
          for (int j = 0; j < n && trials[j].corrects > 0; j++)
            frequency += trials[j].digits[i] == d;
          possiblesFrequency[i].push_back(make_pair(frequency, d));
        }
      }
      sort(possiblesFrequency[i].begin(), possiblesFrequency[i].end(), greater<pair<int, int>>());
      for (auto &p: possiblesFrequency[i])
        possibles[i].push_back(p.second);
    }
    int possibleSum = 0, totalPossibleSum = 0;
    for (int i = 0; i < 12; i++)
      totalPossibleSum += possibles[i].size();
    int best = 1e9;
    for (int i = 0; i < 12; i++)
    {
      possibleSum += possibles[i].size();
      int curr = abs(possibleSum - (totalPossibleSum - possibleSum));
      if (curr < best)
        best = curr, cutPoint = i;
    }

    DEBUG
      for (int i = 0; i < 12; i++)
      {
        printf("Possibilities %d:", (int)possiblesFrequency[i].size());
        for (auto &p: possiblesFrequency[i])
          printf(" (%d, %d)", p.first, p.second);
        printf("\n");
      }

    leftAns.clear(), rightAns.clear();
    curr = vector<int>(n, 0);
    for (int i = 0; i < n; i++)
      curr[i] = trials[i].corrects;
    Trial a;
    solveLeft(0, a);
    sort(leftAns.begin(), leftAns.end());
    curr = vector<int>(n, 0);
    Trial b;
    solveRight(11, b);

    Trial finalAns;
    for (int k = 0; k < cutPoint; k++)
      finalAns.digits[k] = leftAns[0].ans.digits[k];
    for (int k = 11; k >= cutPoint; k--)
      finalAns.digits[k] = rightAns[0].ans.digits[k];
    finalAns.print(false);
  }
  return 0;
}