#include <bits/stdc++.h>
using namespace std;

struct team
{
  int points, games, scoredGoals, concededGoals, balance;
  string name, lowName;
  double percentage;
};

bool comp(team &a, team &b)
{
  return(a.points > b.points || (a.points == b.points && a.balance > b.balance) || (a.points == b.points && a.balance == b.balance && a.scoredGoals > b.scoredGoals) || (a.points == b.points && a.balance == b.balance && a.scoredGoals == b.scoredGoals && a.lowName < b.lowName));
}

void createTeam(team &t, string name)
{
  t.name = name; t.lowName = name;
  for (auto &c: t.lowName)
    c = tolower(c);
  t.points = t.games = t.scoredGoals = t.concededGoals = t.balance = 0;
  t.percentage = -1;
}

void afterMatch(team &ta, team &tb, int ga, int gb)
{
  ta.points += (ga > gb) ? 3 : ga == gb;
  tb.points += (gb > ga) ? 3 : ga == gb;
  ta.games ++; tb.games ++;
  ta.scoredGoals += ga; tb.concededGoals += ga;
  tb.scoredGoals += gb; ta.concededGoals += gb;
  ta.balance = ta.scoredGoals - ta.concededGoals;
  tb.balance = tb.scoredGoals - tb.concededGoals;
  ta.percentage = 100.0 * (double) ta.points / (3*ta.games);
  tb.percentage = 100.0 * (double) tb.points / (3*tb.games);
}

void printTeam(team t)
{
  cout << setw(16) << t.name;
  printf("%4d%4d%4d%4d%4d", t.points, t.games, t.scoredGoals, t.concededGoals, t.balance);
  if (t.percentage == -1) printf("    N/A");
  else printf("%s%.2lf", t.percentage == 100 ? " " : t.percentage >= 10 ? "  " : "   ", t.percentage);
  printf("\n");
}

int main()
{
  int teams, games, r = 0;
  while (scanf("%d %d", &teams, &games) && !(!teams && !games))
  {
    if (r ++) printf("\n");

    map<string, team*> mapping;
    team t[teams]; string name;
    for (int i = 0; i < teams; i ++)
    {
      cin >> name;
      createTeam(t[i], name);
      mapping[name] = &t[i];
    }

    string a, b; int ga, gb;
    for (int i = 0; i < games; i ++)
    {
      cin >> a; scanf("%d - %d", &ga, &gb); cin >> b;
      //cout << mapping[a].name << " " << ga << " - " << gb << " " << mapping[b].name << endl;
      afterMatch(*mapping[a], *mapping[b], ga, gb);
    }

    sort(t, t+teams, comp);
    int pos = 1;
    for (int i = 0; i < teams; i ++)
    {
      if (!i) printf(" 1.");
      else
      {
        if (!(t[i - 1].points == t[i].points && t[i - 1].balance == t[i].balance && t[i - 1].scoredGoals == t[i].scoredGoals))
          printf("%2d.", i + 1);
        else
          printf("   ");
      }
      printTeam(t[i]);
    }
  }
  return(0);
}
