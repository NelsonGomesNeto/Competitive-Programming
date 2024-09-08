#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n;
int p[maxN];

vector<vector<int>> queries; vector<int> res;
int query(vector<int> &q)
{
  printf("?");
  for (int i: q) printf(" %d", i);
  printf("\n"); fflush(stdout);

  int k; scanf("%d", &k); k--;
  return k;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) p[i] = i;

    queries.clear(), res.clear();
    for (int hehe = 0; hehe < 2; hehe++)
    {
      for (int i = 1; i <= n - 1; i++) // n - 1 queries
      {
        queries.push_back(vector<int>());
        for (int j = 0; j + 1 < n; j++)
          queries.back().push_back(hehe ? 1 : i + 1);
        queries.back().push_back(hehe ? i + 1 : 1);

        res.push_back(query(queries.back()));
      }
    }

    p[n - 1] = n - 1;
    for (int i = 0; i < res.size(); i++)
    {
      if (res[i] < 0)
      {
        p[n - 1] = i;
        break;
      }
    }

    DEBUG printf("# found: %d\n", p[n - 1]); fflush(stdout);

    for (int i = 0; i < res.size(); i++)
      if (res[i] >= 0)
        p[res[i]] = p[n - 1] - queries[i][res[i]] + queries[i][n - 1];

    printf("!");
    for (int i = 0; i < n; i++)
      printf(" %d", p[i] + 1);
    printf("\n"); fflush(stdout);
  }
  return 0;
}
