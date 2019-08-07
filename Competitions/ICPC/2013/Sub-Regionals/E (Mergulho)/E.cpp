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
      for (int i = 0; i < n; i ++)
        if (!returned[i])
          printf("%d ", i + 1);
      printf("\n");
    }
  }

  return(0);
}