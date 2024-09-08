#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  The answer will always be: (2^n - 1), (r) or (r + 1)
  WHAT? Yeah haha, but let's prove it

  if (l == r)
    then you can't do anything
    ans = r
  else if (r & 2^(n - 1)) != (l & 2^(n - 1)):
    then you can use f(2^(n - 1), 2^(n - 1) - 1) = 2^n - 1
    cute
    ans = 2^n - 1
  else if (r & 1 or l + 1 == r):
    in the case r & 1:
      
    in the case l + 1 == r, (r & 1) == 0 is also true:
      f(l, r) would make you lose the most significant bit (n - 1)
      So f(r, r) is better
    ans = r
  else:
    in this case r is even (r & 1) == 0 AND l <= r - 2:
      
    ans = r + 1
*/

const int maxN = 1e6; int n;
char s[maxN + 1];
string l, r;

string addOne(string str)
{
  for (int i = str.size() - 1; i >= 0; i--)
    if (str[i] == '0')
    {
      str[i] = '1';
      break;
    }
    else
      str[i] = '0';
  return str;
}

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", s);
    l = string(s);
    scanf(" %s", s);
    r = string(s);

    if (l == r)
      printf("%s\n", r.c_str());
    else if (r[0] != l[0])
    {
      for (int i = 0; i < n; i++)
        printf("1");
      printf("\n");
    }
    else if (r.back() == '1' || addOne(l) == r)
      printf("%s\n", r.c_str());
    else
      printf("%s\n", addOne(r).c_str());
  }
  return 0;
}
