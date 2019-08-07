#include <bits/stdc++.h>
using namespace std;
int n, a, b, c, d, start, len;

int evaluate(int events[][2], int k)
{
  int rating = 0, i;
  for (i = 0; i < n; i ++)
  {
    if (events[i][0] >= k + len) break;
    if (events[i][0] >= k)
    {
      if (events[i][1] == 1)
        rating += c;
      else
        rating -= d;
      if (rating < 0) return(0);
    }
    else
    {
      if (events[i][1] == 1)
        rating += a;
      else
        rating -= b;
      if (rating < 0) return(0);
    }
  }
  return(1);
}

int binSearch(int events[][2], int lo, int hi)
{
  if (lo >= hi) return(lo);
  int mid = (lo + hi) / 2;
  if (evaluate(events, mid))
    return(binSearch(events, lo, mid));
  else
    return(binSearch(events, mid + 1, hi));
}

int main()
{
  scanf("%d %d %d %d %d %d %d", &n, &a, &b, &c, &d, &start, &len);
  int events[n][2], i;
  for (i = 0; i < n; i ++)
    scanf("%d %d", &events[i][0], &events[i][1]);

  int answer = binSearch(events, 0, events[n - 1][0] + 10);

  printf("%d\n", answer == events[n - 1][0] + 10 ? -1 : answer);

  return(0);
}