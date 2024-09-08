#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
5 3 2

2 3 5

5 1 9

1 5 9
*/

const int maxQ = 2e5; int q;
list<int> l;
multiset<int> s;

int main()
{
  while (~scanf("%d", &q))
  {
    l.clear(), s.clear();
    for (int i = 0; i < q; i++)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        int x; scanf("%d", &x);
        l.push_back(x);
      }
      else if (op == 2)
      {
        if (s.empty())
        {
          DEBUG printf("\t%d\n", (int)l.size());
          printf("%d\n", l.front());
          l.pop_front();
        }
        else
        {
          printf("%d\n", *s.begin());
          s.erase(s.begin());
        }
      }
      else
      {
        for (int i: l)
          s.insert(i);
        l.clear();
      }
    }
  }
  return 0;
}