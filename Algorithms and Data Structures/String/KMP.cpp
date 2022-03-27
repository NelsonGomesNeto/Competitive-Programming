#include <bits/stdc++.h>
#define lli long long int
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
    i ++, j ++;
    if (j == sub.size())
    {
      occurrences.push_back(i - j);
      j = pi[j];
    }
  }
  return occurrences;
}

const int maxN = 1e5; int n, m;
char ss[maxN + 1];
string s, t;

int main()
{
  scanf(" %s", ss);
  s = string(ss);
  scanf(" %s", ss);
  t = string(ss);

  vector<int> pi = prefixFunction(t);

  vector<int> occurrences = kmpSearch(s, t, pi);
  printf("%d occurrences\n", (int) occurrences.size());
  for (int i = 0; i < occurrences.size(); i ++)
    printf("%d%c", occurrences[i], i < occurrences.size() - 1 ? ' ' : '\n');

  return(0);
}