#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 16;
char ss[maxN];
lli ll, rr;
vector<int> s;

vector<int> getDigits(lli num)
{
  vector<int> ans;
  while (num)
  {
    ans.push_back(num % 10);
    num /= 10;
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

string toString(vector<int> lol)
{
  string a;
  for (int l : lol) a += to_string(l);
  return a;
}

vector<int> limit;
lli memo[maxN + 1][maxN + 1][maxN + 1][2][2];
lli solve(int i = 0, int at = 0, int occurrences = 0, bool started = false, bool eq = true, string curr = "")
{
  occurrences += started ? at == s.size() : 0;
  DEBUG printf("\t%d %d %d %d | %s\n", i, at, occurrences, eq, curr.c_str());
  if (i == limit.size()) return occurrences;
  lli& ans = memo[i][at][occurrences][started][eq];
  if (ans != -1) return ans;

  ans = 0;
  for (int d = 0, end = eq ? limit[i] : 9; d <= end; ++d)
  {
    int newAt;
    if (at == s.size() || d != s[at])
    {
      // optmize with KMP
      deque<int> now;
      for (int j = 0; j < at; ++j) now.push_back(s[j]);
      now.push_back(d);
      if (at == s.size())
      {
        now.pop_front();
        newAt = at - 1;
        // DEBUG printf("\t\t%s | %s | %d | %d\n",
        //   toString(vector<int>(now.begin(), now.end())).c_str(),
        //   toString(vector<int>(s.begin(), s.begin() + newAt + 1)).c_str(),
        //   newAt,
        //   vector<int>(now.begin(), now.end()) != vector<int>(s.begin(), s.begin() + newAt + 1)
        // );
      }
      else
        newAt = at;

      while (newAt >= 0 && vector<int>(now.begin(), now.end()) != vector<int>(s.begin(), s.begin()+newAt+1))
      {
        --newAt;
        now.pop_front();
      }

      if (newAt < 0) newAt = 0;
      if (d == s[newAt]) ++newAt;
    }
    else
      newAt = at + 1;

    const bool newStarted = started | (d != 0);
    if (!newStarted)
      newAt = 0;
    ans += solve(i + 1, newAt, occurrences, newStarted, eq & (d == limit[i]), curr + to_string(d));
  }
  return ans;
}

lli g(lli x)
{
  limit = getDigits(x);
  memset(memo, -1, sizeof(memo));
  lli ans = solve();
  DEBUG printf("\tg(%lld) = %lld\n", x, ans);
  return ans;
}

int main()
{
  int t;
  while (~scanf("%d", &t))
  {
    for (int tt = 0; tt < t; ++tt)
    {
      scanf(" %s %lld %lld", ss, &ll, &rr);
      s.clear();
      for (int i = 0; ss[i]; ++i)
        s.push_back(ss[i] - '0');

      lli ans = g(rr) - g(ll - 1);
      printf("%lld\n", ans);
      // return 0;
    }
  }
  return 0;
}
