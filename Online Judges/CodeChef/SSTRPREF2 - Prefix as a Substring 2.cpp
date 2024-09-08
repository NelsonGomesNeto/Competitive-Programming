#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n;
char ss[maxN + 1];
string readString() { scanf(" %s", ss); return string(ss); }
string x, s1, s2;

vector<int> prefixFunction(string &str)
{
  vector<int> pi(str.size() + 1);
  pi[0] = -1;
  for (int i = 0, j = -1; i < str.size();)
  {
    while (j >= 0 && str[i] != str[j]) j = pi[j];
    pi[++i] = ++j;
  }
  return pi;
}
lli ans;
lli acc[maxN + 1];
vector<int> kmpSearch(string &str, string &subStr, bool prefix)
{
  DEBUG printf("%s %s\n", str.c_str(), subStr.c_str());
  vector<int> pi = prefixFunction(subStr);
  vector<int> occurrences;
  set<int> cnt;
  for (int i = 0, j = 0; i < str.size();)
  {
    while (j >= 0 && str[i] != subStr[j]) j = pi[j];
    i++, j++;
    // s[i - j : i - 1] == sub[0 : j - 1], when j >= 1
    // so we can make: s[i - j : i - j], s[i - j : i - j + 1], ..., s[i - j : i - 1]
    DEBUG printf("\t%d - %d | %s - %s\n", i, j, str.substr(i - j, j).c_str(), subStr.substr(0, j).c_str());
    if (j >= 1)
    {
      if (prefix)
      {
        int jj = j, delta = 0;
        while (jj > 0)
        {
          jj = pi[jj];
          delta++;
        }
        acc[i - 1] += delta;
        // acc[i]--;
      }
      else
      {
        ans += acc[i - j - 1];
      }
    }
    cnt.insert(j);
    if (j == subStr.size())
    {
      occurrences.push_back(i - j);
      j = pi[j];
    }
  }
  ans += cnt.size();
  return occurrences;
}

int main()
{
  while (~scanf("%d", &n))
  {
    s1 = readString();
    s2 = readString();
    x = readString();

    string revx = x;
    reverse(revx.begin(), revx.end());
    string revs2 = s2;
    reverse(revs2.begin(), revs2.end());

    ans = 0;

    fill(acc, acc+x.size()+1, 0);
    kmpSearch(x, s1, true);
    // for (int i = 0; i < x.size(); i++) acc[i + 1] += acc[i];
    DEBUG {
      for (int i = 0; i <= x.size(); i++)
        printf("%2d%c", i, i < x.size() ? ' ' : '\n');
      for (int i = 0; i <= x.size(); i++)
        printf("%2lld%c", acc[i], i < x.size() ? ' ' : '\n');
    }
    kmpSearch(x, s2, false);

    ans--;

    printf("%lld\n", ans);
    // return 0;
  }
  return 0;
}