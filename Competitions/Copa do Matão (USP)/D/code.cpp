#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

vector<int> prefixFunction(string &s)
{
  vector<int> pi(s.size() + 1);
  pi[0] = -1;
  for (int i = 0, j = -1; i < s.size();)
  {
    while (j >= 0 && s[i] != s[j]) j = pi[j];
    pi[++i] = ++j;
  }
  return pi;
}
vector<int> kmpSearch(string &s, string &sub, vector<int> &pi)
{
  vector<int> occurrences;
  for (int i = 0, j = 0; i < s.size();)
  {
    while (j >= 0 && s[i] != sub[j]) j = pi[j];
    i++, j++;
    if (j == sub.size())
    {
      occurrences.push_back(i - j);
      // j = pi[j];
      j = 0;
    }
  }
  return occurrences;
}

const int maxN = 1e6; int n;
char ss[maxN + 1];
string s;

int main()
{
  while (~scanf(" %s", ss))
  {
    s = string(ss);
    n = s.size();

    vector<int> divisors;
    for (int d = 1; d*d <= n; d++)
    {
      if (n % d == 0)
      {
        divisors.push_back(d);
        int dd = n / d;
        if (dd != d && n % dd == 0)
          divisors.push_back(dd);
      }
    }

    s += s;
    vector<int> pi = prefixFunction(s);

    int ans = 1;
    for (int d: divisors)
    {
      if (d == n) continue;
      // starting positions
      for (int i = 0; i < d; i++)
      {
        string sub = s.substr(0, d);
        vector<int> occurrences = kmpSearch(s, sub, pi);
        if (occurrences.size() >= 2 * n / d - (i > 0))
        {
          DEBUG printf("\t%d %d - %d\n", i, d, (int)occurrences.size());
          ans += n;
        }
        break;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}