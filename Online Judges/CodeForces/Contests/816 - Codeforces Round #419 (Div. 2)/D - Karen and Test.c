#include <stdio.h>

int doReduction(int a[], int size)
{
  int i, times = size, j, k = 1;
  while (times >= 2 && times % 3 != 0)
  {
    for (j = 0; j < times - 1; j ++, k *= -1)
    {
      a[j] = (a[j] + (k * a[j + 1]));
      if (a[j] < 0) a[j] += 1000000007;
      a[j] %= 1000000007;
      printf("%d ", a[j]);
    }
    printf("\n");
    times --;
  }
  printf("%d\n", times);
  return(times);
}

long long int group(int a[], int size)
{
  int i, j, k, mid = (size / 2); long long int sumLeft = 0, sumRight = 0;
  for (i = 0, j = 1, k = 1; i < size; i += 2, j += 2)
  {
    sumLeft += k * a[i]; sumLeft %= 1000000007;
    if (j < size)
      sumRight += k * a[j]; sumRight %= 1000000007;
    if (j < mid) k ++;
    else k --;
    printf("%d ", k);
  } printf("\n");
  if (sumLeft < 0) sumLeft += 1000000007;
  if (sumRight < 0) sumRight += 1000000007;

  return((sumLeft + sumRight) % 1000000007);
}

int main()
{
  int numbers; scanf("%d", &numbers);
  int array[numbers], i;
  for (i = 0; i < numbers; i ++)
    scanf("%d", &array[i]);

  int newSize = doReduction(array, numbers);

  printf("%Ld\n", group(array, newSize));

  return(0);
}
