#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

vector<int> prefixFunction(vector<int>& s)
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

vector<int> kmpSearch(vector<int>& s, vector<int>& sub, vector<int>& pi)
{
  vector<int> occurrences;
  for (int i = 0, j = 0; i < s.size();)
  {
    while (j >= 0 && s[i] != sub[j]) j = pi[j];
    ++i, ++j;
    if (j == sub.size())
    {
      occurrences.push_back(i - j);
      j = pi[j];
    }
  }
  return occurrences;
}

const int maxN = 5e5; int n; lli k;
vector<int> a, aa, b;

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d %lld", &n, &k);
    a.clear(), b.clear();
    a.resize(n), b.resize(n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &b[i]);

    aa = a;
    for (int card : a) aa.push_back(card);
    vector<int> pi = prefixFunction(b);
    vector<int> occurrences = kmpSearch(aa, b, pi);

    bool can;
    if (n == 2)
    {
      if (a == b)
        can = ~k & 1;
      else
        can = !occurrences.empty() && (k & 1);
      // Chapter 2 check: If b[0] == b[1]: any K will do (if a == b).
      if (b[0] == b[1] && a == b)
        can = true;
    }
    else
    {
      if (a == b)
      {
        can = k != 1;
        // Chapter 2 check: It's possible that after one move: you
        // with the matching stacks.
        can |= occurrences.size() > 2;
      }
      else
        can = k > 0 && !occurrences.empty();
    }
    printf("Case #%d: %s\n", testCase, can ? "YES" : "NO");
    DEBUG {
      printf("\t%d %lld\n", n, k);
      printf("\t");
      for (int i = 0; i < n; ++i) printf("%d%c", a[i], i + 1 < n ? ' ' : '\n');
      printf("\t");
      for (int i = 0; i < n; ++i) printf("%d%c", b[i], i + 1 < n ? ' ' : '\n');
      printf("\t");
      for (int i = 0; i < aa.size(); ++i) printf("%d%c", aa[i], i + 1 < aa.size() ? ' ' : '\n');
      printf("\t");
      for (int o : occurrences) printf("%d ", o);
      printf("\n");
    }
  }
  return 0;
}
