#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5; int q;
vector<int> ans;
struct Rule
{
  int from, to;
};
vector<Rule> rules[maxN];
int numberMap[maxN + 1];

int main()
{
  while (~scanf("%d", &q))
  {
    for (int i = 0; i <= maxN; i++) numberMap[i] = i;

    ans.clear();
    for (int i = 0; i < q; i++)
    {
      int op, x; scanf("%d %d", &op, &x);
      if (op == 1)
      {
        ans.push_back(x);
      }
      else
      {
        int y; scanf("%d", &y);
        rules[i].push_back(Rule{x, y});
      }
    }
  }
  return 0;
}
