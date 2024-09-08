#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  minimum sum = 0 (0 + 0)
  maximum sum = 18 (9 + 9)
  0 - 0 + 0
  1 - 1 + 0 or 0 + 1
  2
  3
  4
  5 - ...
  6
  7
  8
  9 - 9 + 0 or 0 + 9 or 4 + 5 or 5 + 4
 10 - 9 + 1 or 1 + 9 or 4 + 6 or 6 + 4
 11
 12
 13
 14
 15
 16
 17
 18
*/

const int maxN = 2e5; int n;
char ss[maxN + 1];
string s;

int toNum(char d)
{
  return d - '0';
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", ss);
    s = ss;

    bool sumGreaterThan9 = false;
    for (int i = s.size() - 1; i >= 1; i--)
    {
      int newSum = toNum(s[i - 1]) + toNum(s[i]);
      if (newSum >= 10)
        sumGreaterThan9 = true;
    }

    int biggestSum = 0, pos = 0;
    if (sumGreaterThan9)
    {
      for (int i = 1; i < s.size(); i++)
      {
        int newSum = toNum(s[i - 1]) + toNum(s[i]);
        if (newSum >= 10)
          biggestSum = newSum, pos = i;
      }
    }
    else
    {
      for (int i = 1; i >= 1; i--)
      {
        int newSum = toNum(s[i - 1]) + toNum(s[i]);
        if (newSum >= biggestSum)
          biggestSum = newSum, pos = i;
      }
    }

    for (int i = 0; i < s.size(); i++)
      if (i + 1 == pos)
        printf("%d", biggestSum), i++;
      else
        printf("%c", s[i]);
    printf("\n");
  }
  return 0;
}
