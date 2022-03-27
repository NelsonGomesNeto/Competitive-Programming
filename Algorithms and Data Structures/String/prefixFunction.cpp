#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tricks with Prefix Function:
  Biggest Palindrome in Prefix: a + '#' + rev(a)
*/

const int maxN = 1e6; int n;
char ss[maxN + 1];
string s;

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

int main()
{
  scanf("%s", ss);
  s = string(ss);
  n = s.size();

  vector<int> pi = prefixFunction(s);
  printf("%s\n", s.c_str());
  printf("    "); for (int i = 0; i <= n; i ++) printf("  %c%c", s[i], i < n ? ' ' : '\n');
  for (int i = 0; i <= n; i ++) printf("%3d%c", i, i < n ? ' ' : '\n');
  for (int i = 0; i <= n; i ++) printf("%3d%c", pi[i], i < n ? ' ' : '\n');

  return 0;
}