#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5;
char ss[maxN + 1];

bool isPalindrome(string &str)
{
  for (int i = 0, j = str.size() - 1; i < j; i++, j--)
    if (str[i] != str[j])
      return false;
  return true;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", ss);
    string s = "a" + string(ss);
    string t = string(ss) + "a";

    if (!isPalindrome(s))
      printf("YES\n%s\n", s.c_str());
    else if (!isPalindrome(t))
      printf("YES\n%s\n", t.c_str());
    else
      printf("NO\n");
  }
  return 0;
}
