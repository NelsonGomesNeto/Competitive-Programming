#include <bits/stdc++.h>
#define lli long long int
using namespace std;
lli inf = 100000000000;

int main()
{
  int size, k; scanf("%d %d", &size, &k);
  lli array[size], i;
  for (i = 0; i < size; i ++)
    scanf("%I64d", &array[i]);

  lli answer;
  if (k == 1)
  {
    answer = inf;
    for (i = 0; i < size; i ++)
      answer = min(answer, array[i]);
  }
  else if (k == 2)
    answer = max(array[0], array[size - 1]);
  else
  {
    answer = -inf;
    for (i = 0; i < size; i ++)
      answer = max(answer, array[i]);
  }

  printf("%I64d\n", answer);

  return(0);
}

6
11 6 6 9 10 10