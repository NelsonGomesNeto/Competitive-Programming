#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n, q;

multiset<int> boxes[maxN];
set<int> cards[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < maxN; ++i)
      boxes[i].clear(), cards[i].clear();

    scanf("%d", &q);
    while (q--)
    {
      int op;
      scanf("%d", &op);
      if (op == 1)
      {
        int i, j;
        scanf("%d %d", &i, &j);
        --i, --j;
        boxes[j].insert(i);
        cards[i].insert(j);
      }
      else if (op == 2)
      {
        int i;
        scanf("%d", &i);
        --i;

        bool first = true;
        for (const int c : boxes[i])
        {
          if (!first) printf(" ");
          first = false;
          printf("%d", c + 1);
        }
        printf("\n");
      } else
      {
        int i;
        scanf("%d", &i);
        --i;

        bool first = true;
        for (const int b : cards[i])
        {
          if (!first)
            printf(" ");
          first = false;
          printf("%d", b + 1);
        }
        printf("\n");
      }
    }
  }
  return 0;
}
