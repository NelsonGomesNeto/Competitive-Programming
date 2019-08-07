#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int minimum = 0, now = 0, enters, leaves;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &leaves, &enters);
    now -= leaves; now = max(now, 0);
    now += enters;
    minimum = max(minimum, now);
  }
  printf("%d\n", minimum);

  return(0);
}