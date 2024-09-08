#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5;
char s[maxN + 1];
string has[3];
string all[4] = {"ABC", "ARC", "AGC", "AHC"};

int main()
{
  string ans;
  for (int i = 0; i < 3; i++)
  {
    scanf(" %s", s);
    has[i] = string(s);
  }

  for (int i = 0; i < 4; i++)
  {
    bool missing = true;
    for (int j = 0; j < 3; j++)
      if (has[j] == all[i])
        missing = false;
    if (missing)
      printf("%s\n", all[i].c_str());
  }

  return 0;
}