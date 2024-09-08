#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
bool married[maxN];
vector<int> kingdoms[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    set<int> available;
    for (int i = 0; i < n; i++)
    {
      married[i] = false;
      available.insert(i);
      kingdoms[i].clear();
      int k; scanf("%d", &k);
      for (int j = 0; j < k; j++)
      {
        int u; scanf("%d", &u); u --;
        kingdoms[i].push_back(u);
      }
    }

    int add = -1, to = -1;
    for (int i = 0; i < n; i++)
    {
      for (int j: kingdoms[i])
        if (available.count(j))
        {
          married[i] = true;
          available.erase(j);
          break;
        }
    }
    if (!available.empty())
      for (int i = n - 1; i >= 0; i--)
        if (!married[i])
        {
          add = *available.begin();
          to = i;
          break;
        }

    if (add == -1)
      printf("OPTIMAL\n");
    else
      printf("IMPROVE\n%d %d\n", to + 1, add + 1);
  }
  return 0;
}
