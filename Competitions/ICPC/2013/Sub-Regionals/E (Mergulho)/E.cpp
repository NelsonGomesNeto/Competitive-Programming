#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e4;
bool returned[maxN];

int main()
{
  int n, r;
  while (scanf("%d %d", &n, &r) != EOF)
  {
    memset(returned, false, sizeof(returned));
    for (int i = 0, u; i < r; i ++)
    {
      scanf("%d", &u); u --;
      returned[u] = true;
    }

    bool allBack = true;
    for (int i = 0; i < n; i ++)
      if (!returned[i])
        allBack = false;
    if (allBack) printf("*\n");
    else
    {
      bool first = true;
      for (int i = 0; i < n; i ++)
        if (!returned[i])
        {
          if (first) printf("%d");
          else printf("%d ", i + 1);
          first = false;
        }
      printf("\n");
    }
  }

  return(0);
}