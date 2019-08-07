#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)

int solve(int i, int size, int string[])
{
  int ans = 0, sum = 0;
  map<int, int> sumToIndex;
  for (i = 0; i < size; i ++)
  {
    sum += string[i];
    if (sum == 0) ans = i + 1;
    if (sumToIndex.count(sum) == 0)
      sumToIndex[sum] = i;
    else
      ans = max(ans, i - sumToIndex[sum]);
  }
  return(ans);
}

int main()
{
  int size; scanf("%d", &size);
  int string[size], num, i;
  for (i = 0; i < size; i ++)
  {
    scanf("%01d", &num);
    if (num) string[i] = 1;
    else string[i] = -1;
  }

  int answer = solve(0, size, string);

  printf("%d\n", answer);

  return(0);
}
