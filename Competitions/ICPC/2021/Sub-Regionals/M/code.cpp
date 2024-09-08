#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxQ = 1e5; int q;
int t[maxQ], x[maxQ];
vector<int> tree[maxQ + 1];
bool visited[maxQ + 1];

int main()
{
  while (~scanf("%d", &q))
  {
    for (int i = 0; i <= q; i++) tree[i].clear(), visited[i] = false;

    for (int i = 0; i < q; i++)
      scanf("%d %d", &t[i], &x[i]);

    int curr = 1, currIdx = 1;
    for (int i = 0; i < q; i++)
    {
      if (t[i] == 1)
      {
        currIdx++;
        tree[x[i]].push_back(currIdx);
      }
      else
      {
        if (x[i] == curr)
        {

        }
        else
        {
          visited[x[i]] = true;
        }

        printf("%d\n", curr);
      }
    }
  }
  return 0;
}