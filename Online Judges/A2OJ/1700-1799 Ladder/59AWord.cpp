#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char s[101];
  scanf("%s", s);
  int n = strlen(s), upper = 0;
  for (int i = 0; s[i]; i ++)
    upper += s[i] >= 'A' && s[i] <= 'Z';

  if (upper > (n >> 1)) 
    for (int i = 0; s[i]; i ++)
      s[i] = toupper(s[i]);
  else
    for (int i = 0; s[i]; i ++)
      s[i] = tolower(s[i]);
  printf("%s\n", s);

  return 0;
}