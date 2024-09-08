#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  Instead of minimizing the amount of moved books
  Maximze the amount of unmoved books

  A book will stay in the same place if for all books of it's color
  We moved all books from other colors in between.

  
*/

const int maxN = 5e5; int n;
int a[maxN];

vector<int> pos[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i <= n; i++)
      pos[i].clear();

    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i]--;
      pos[a[i]].push_back(i);
    }

    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
      bool sorted = true;
      for (int j = 1; j < pos[i].size(); j++)
        if (pos[i][j - 1] + 1 != pos[i][j])
          sorted = false;
      if (!sorted)
      {
        if (pos[i].back() == n - 1)
        {
          int toSort = pos[i].size();
          for (int j = pos[i].size(), at = n - 1; j >= 0; j--, at--)
            if (pos[i][j] == at)
              toSort--;
          ans += toSort;
        }
        else
          ans += pos[i].size();
      }
    }
  }
  return 0;
}
