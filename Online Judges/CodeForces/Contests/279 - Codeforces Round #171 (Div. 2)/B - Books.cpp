#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, t; scanf("%d %d", &n, &t);
  int book[n];
  for (int i = 0; i < n; i ++)
    scanf("%d", &book[i]);

  int lo = 0, hi = 0, read = 0, freeTime = t;
  for (int i = 0; i < n; i ++)
  {
    if (freeTime - book[i] >= 0)
      freeTime -= book[hi ++];
    else
    {
      freeTime += book[lo ++];
      i --;
    }
    read = max(read, hi - lo);
  }

  printf("%d\n", read);

  return(0);
}