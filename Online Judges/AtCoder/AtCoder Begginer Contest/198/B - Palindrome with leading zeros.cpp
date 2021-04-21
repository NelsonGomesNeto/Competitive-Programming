#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10;
char ss[maxN];
string s;

bool palindrome(string &str)
{
  for (int i = 0, j = str.size() - 1; i < j; i++, j--)
    if (str[i] != str[j])
      return false;
  return true;
}

int main()
{
  while (~scanf(" %s", ss))
  {
    s = string(ss);
    while (!palindrome(s) && s.size() < 20)
      s = '0' + s;

    printf("%s\n", palindrome(s) ? "Yes" : "No");
  }
  return 0;
}