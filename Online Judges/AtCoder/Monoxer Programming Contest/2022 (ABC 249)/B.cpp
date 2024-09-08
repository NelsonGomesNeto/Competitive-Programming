#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
char ss[maxN + 1];
string s;
int cnt[256];

int main()
{
  while (~scanf(" %s", ss))
  {
    fill(cnt, cnt+256, 0);
    s = string(ss);

    for (char c : s)
      ++cnt[c];

    bool hasUpper = false, hasLower = false;
    bool hasRepeats = (*max_element(cnt, cnt+256)) > 1;

    for (int i = 'a'; i <= 'z'; ++i)
      if (cnt[i] >= 1)
        hasLower = true;
    for (int i = 'A'; i <= 'Z'; ++i)
      if (cnt[i] >= 1)
        hasUpper = true;

    bool valid = hasUpper && hasLower && !hasRepeats;
    DEBUG printf("\t%d %d %d\n", hasUpper, hasLower, hasRepeats);
    printf("%s\n", valid ? "Yes" : "No");
  }
  return 0;
}
