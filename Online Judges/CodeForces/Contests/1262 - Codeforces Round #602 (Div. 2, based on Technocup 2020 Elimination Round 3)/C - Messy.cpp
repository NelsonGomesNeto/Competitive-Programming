#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, k;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d", &n, &k);
    scanf(" %s", s);

    vector<pair<int, int>> op;
    int at = 0;
    while (k > 1)
    {
      char wanted = at & 1 ? ')' : '(';
      if (s[at] != wanted)
      {
        for (int j = at + 1; j < n; j ++)
          if (s[j] == wanted)
          {
            DEBUG printf("\t%d %d\n", at, j);
            op.push_back({at, j}), reverse(s+at, s+j+1);
            break;
          }
        DEBUG printf("%s\n", s);
      }
      k -= (at & 1);
      at ++;
    }
    // at ++;
    int ended = (n - at) >> 1;
    for (; ended; at ++, ended --)
      if (s[at] != '(')
      {
        for (int j = at + 1; j < n; j ++)
          if (s[j] == '(')
          {
            DEBUG printf("\t%d %d\n", at, j);
            op.push_back({at, j}), reverse(s+at, s+j+1);
            break;
          }
        DEBUG printf("%s\n", s);
      }
    DEBUG printf("---------\n");

    // printf("%s\n", s);
    printf("%d\n", (int) op.size());
    for (auto &o: op)
      printf("%d %d\n", o.first + 1, o.second + 1);
  }
  return 0;
}