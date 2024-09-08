#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
char s[101];

int main()
{
  while (~scanf("%d", &n))
  {
    set<string> mails;
    for (int j = 0; j < n; j++)
    {
      scanf(" %s", s);
      string mail = "";
      int i = 0;
      while (s[i] != '+' && s[i] != '@')
      {
        if (s[i] != '.')
          mail += s[i];
        i++;
      }
      while (s[i] != '@') i++;
      while (s[i]) mail += s[i++];

      DEBUG printf("%s - %s\n", s, mail.c_str());

      mails.insert(mail);
    }
    printf("%d\n", (int)mails.size());
  }
  return 0;
}