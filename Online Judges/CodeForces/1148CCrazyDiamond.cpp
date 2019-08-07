#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 3e5; int n;
int p[maxN], ori[maxN];
vector<pair<int, int>> operations;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &p[i]);
    p[i] --;
    ori[i] = p[i];
  }

  bool ss = false;
  while (!ss)
  {
    for (int i = 0; i < n; i ++)
    {
      if (p[i] != i && 2*abs(p[i] - i) >= n)
      {
        operations.push_back({i + 1, p[i] + 1});
        swap(p[p[i]], p[i]);
      }
      else if (p[i] != i)
      {
        if (i < (n >> 1) && p[i] < (n >> 1))
        {
          operations.push_back({i + 1, n});
          operations.push_back({p[i] + 1, n});
          operations.push_back({i + 1, n});
        }
        else if (i < (n >> 1) && p[i] >= (n >> 1))
        {
          operations.push_back({1, p[i] + 1});
          operations.push_back({1, n});
          operations.push_back({i + 1, n});
          operations.push_back({1, n});
          operations.push_back({1, p[i] + 1});
        }
        else if (i >= (n >> 1) && p[i] >= (n >> 1))
        {
          operations.push_back({i + 1, 1});
          operations.push_back({p[i] + 1, 1});
          operations.push_back({i + 1, 1});
        }
        else
        {
          operations.push_back({1, i + 1});
          operations.push_back({1, n});
          operations.push_back({p[i] + 1, n});
          operations.push_back({1, n});
          operations.push_back({1, i + 1});
        }
        swap(p[p[i]], p[i]);
      }
    }
    ss = true;
    for (int i = 0; i < n; i ++) if (p[i] != i) ss = false;
  }

  for (auto o: operations) swap(ori[o.first - 1], ori[o.second - 1]);

  DEBUG {
    bool sorted = operations.size() <= 5*n;
    for (int i = 0; i < n; i ++)
    {
      if (ori[i] != i) sorted = false;
      printf("%d ", ori[i] + 1);
    }
    printf("-- %d\n", sorted);
    // printf("%d\n", sorted);
  }

  printf("%d\n", (int) operations.size());
  for (auto o: operations) printf("%d %d\n", o.first, o.second);

  return(0);
}