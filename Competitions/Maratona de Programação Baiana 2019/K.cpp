#include <bits/stdc++.h>
#define lli long long int
using namespace std;

struct score
{
  int points, w, goals; string name;
  bool operator<(const score &s) const
  {
    return(points < s.points
    || (points == s.points && w < s.w)
    || (points == s.points && w == s.w && goals < s.goals)
    || (points == s.points && w == s.w && goals == s.goals && name > s.name));
  }
};
map<string, score> teams;

int main()
{
  string a, b, c, d;
  cin >> a >> b >> c >> d;
  teams[a] = score({0, 0, 0, a});
  teams[b] = score({0, 0, 0, b});
  teams[c] = score({0, 0, 0, c});
  teams[d] = score({0, 0, 0, d});

  int n; scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    int aa, bb;
    cin >> a >> aa >> b >> bb;
    teams[a].points += aa > bb ? 3 : aa == bb ? 1 : 0;
    teams[a].w += aa > bb;
    teams[a].goals += aa - bb;
    teams[b].points += bb > aa ? 3 : bb == aa ? 1 : 0;
    teams[b].w += bb > aa;
    teams[b].goals += bb - aa;
  }

  vector<score> t;
  for (auto &i: teams) t.push_back(i.second);
  sort(t.begin(), t.end()); reverse(t.begin(), t.end());
  cout << t[0].name << endl << t[1].name << endl;

  return(0);
}