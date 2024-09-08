#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n;
char s[101];

char isVowel(char c)
{
  c = tolower(c);
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", s);
      int chain = 0;
      bool hard = false;
      for (int j = 0; s[j]; j++)
      {
        if (!isVowel(s[j])) chain++;
        else chain = 0;
        if (chain == 3)
          hard = true;
      }
      printf("%s %s\n", s, hard ? "nao eh facil" : "eh facil");
    }
  }
  return 0;
}