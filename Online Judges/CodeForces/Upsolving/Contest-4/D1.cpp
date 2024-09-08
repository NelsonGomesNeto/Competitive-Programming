#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1;
char ss[maxN];
string s;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf(" %s", ss);
    s = string(ss);

    string ans = "";
    int i, j;
    for (i = 0, j = s.size() - 1; i <= j && s[i] == s[j]; i++, j--);
    i --, j++;

    if (i == j)
    {
      printf("%s\n", s.c_str());
      continue;
    }

    int iBest = i;
    for (int ii = i + 1; ii < j; ii++)
    {
      bool valid = true;
      for (int jj = i + 1, kk = ii; jj < kk; jj++, kk--)
        if (s[jj] != s[kk])
          valid = false;
      if (valid)
        iBest = ii;
    }

    int jBest = j;
    for (int jj = j - 1; jj > i; jj--)
    {
      bool valid = true;
      for (int ii = j - 1, kk = jj; ii > kk; ii--, kk++)
        if (s[ii] != s[kk])
          valid = false;
      if (valid)
        jBest = jj;
    }

    DEBUG printf("\t%d %d %d %d\n", i, j, iBest, jBest);

    if ((iBest - i) >= (j - jBest))
      ans = s.substr(0, iBest + 1) + s.substr(j);
    else
      ans = s.substr(0, i + 1) + s.substr(jBest);
    printf("%s\n", ans.c_str());
  }
  return 0;
}

/*
abcdfdcecba
abcecdfdcba
*/