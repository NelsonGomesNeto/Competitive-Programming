#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)

int main()
{
  int size; scanf("%d", &size);
  int array[size];
  for (int i = 0; i < size; i ++) scanf("%d", &array[i]);

  int left[size], right[size]; left[0] = left[size - 1] = 1; right[0] = right[size - 1] = 1;
  for (int i = 1, j = size - 2; i < size - 1; i ++, j --)
  {
    if (array[i] > array[i - 1])
      left[i] = left[i - 1] + 1;
    else
      left[i] = 1;
      
    if (array[j] < array[j + 1])
      right[j] = right[j + 1] + 1;
    else
      right[j] = 1;
  }

  DEBUG for (int i = 0; i < size; i ++) printf("%d%c", left[i], i < size - 1 ? ' ' : '\n');
  DEBUG for (int i = 0; i < size; i ++) printf("%d%c", right[i], i < size - 1 ? ' ' : '\n');

  int best = 1 + (size > 1);
  for (int i = 1; i < size - 1; i ++)
    if (array[i - 1] < array[i + 1] - 1)
      best = max(best, left[i - 1] + 1 + right[i + 1]);
    else
    {
      best = max(best, left[i] + 1);
      best = max(best, 1 + right[i]);
    }

  printf("%d\n", best);

  return(0);
}