#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
char ss[maxN + 1];

vector<int> prefixFunction(string &pattern)
{
  vector<int> pi(pattern.size() + 1);
  pi[0] = -1;
  for (int i = 0, j = -1; i < pattern.size();)
  {
    while (j >= 0 && pattern[i] != pattern[j]) j = pi[j];
    pi[++ i] = ++ j;
  }
  return pi;
}
bool kmpSearch(string &str, string &pattern, vector<int> &pi)
{
  int occurrences = 0;
  for (int i = 0, j = 0; i < str.size();)
  {
    while (j >= 0 && str[i] != pattern[j]) j = pi[j];
    i ++, j ++;
    if (j == pattern.size())
    {
      occurrences++;
      j = pi[j];
    }
    if (occurrences > 1)
      return true;
  }
  return false;
}

int main()
{
  while (~scanf(" %s", ss))
  {
    string s = string(ss);

    string ans = ""; int startPos = s.size();
    unordered_map<string, vector<int>> cnt;
    for (int sz = 1; sz <= s.size() && ans.empty(); sz++)
    {
      cnt.clear();
      for (int i = 0; i + sz <= s.size(); i++)
      {
        string t = s.substr(i, sz);
        cnt[t].push_back(i);
      }

      for (auto &p: cnt)
        if (p.second.size() == 1 && p.second[0] < startPos)
        {
          startPos = p.second[0];
          ans = p.first;
        }
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}