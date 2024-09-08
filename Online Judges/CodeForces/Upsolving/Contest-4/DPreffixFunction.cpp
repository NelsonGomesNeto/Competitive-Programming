#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1;
char ss[maxN];

vector<int> prefixFunction(string str)
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

string prefixPalindrome(string str)
{
  vector<int> pi = prefixFunction(str);
  return str.substr(0, pi[str.size()]);
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf(" %s", ss);
    string s = string(ss);

    int lo = 0, hi = s.size() - 1;
    while (lo <= hi && s[lo] == s[hi]) lo++, hi--;

    if (lo >= hi)
    {
      printf("%s\n", s.c_str());
      continue;
    }
    lo--, hi++;

    string middle = s.substr(lo + 1, hi - lo - 1);
    string revMiddle = middle;
    reverse(revMiddle.begin(), revMiddle.end());
    string prefix = prefixPalindrome(middle + '#' + revMiddle), suffix = prefixPalindrome(revMiddle + '#' + middle);

    string ans;
    if (prefix.size() >= suffix.size())
      ans = s.substr(0, lo + 1) + prefix + s.substr(hi);
    else
      ans = s.substr(0, lo + 1) + suffix + s.substr(hi);
    printf("%s\n", ans.c_str());
  }
  return 0;
}