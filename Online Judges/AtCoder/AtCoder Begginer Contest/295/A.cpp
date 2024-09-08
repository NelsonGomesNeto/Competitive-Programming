#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxS = 50;
char ss[maxS + 1];
const set<string> needed = {
  "and", "not", "that", "the", "you"
};

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    bool ans = false;
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      ans |= needed.count(string(ss));
    }
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
