#include <stdio.h>

int evaluate(int b[], int k, int size)
{
  int jump = 0, i = 0;
  while (i < size && jump < b[size - 1])
  {
    if (b[i] - jump > k)
      return(0);
    if (b[i] - jump == k)
      k --;

    jump = b[i ++];
  }
  return(1);
}

int min(int a, int b)
{
  return(a > b ? b : a);
}

int guessBug(int b[], int k, int prev, int bigGood, int size)
{
  if (k - prev >= -1 && k - prev <= 1)
  {
    if (evaluate(b, k, size))
      return(k);
    else
      return(bigGood);
  }

  if (!evaluate(b, k, size))
    return(guessBug(b, (k + prev) / 2, prev, bigGood, size));
  else
    return(guessBug(b, k / 2, k, min(bigGood, k), size));

  return(k);
}

int guess(int b[], int begin, int end, int size)
{
  if (begin == end)
    return(begin);

  int mid = (end + begin) / 2;
  if (evaluate(b, mid, size))
    return(guess(b, begin, mid, size));
  else
    return(guess(b, mid + 1, end, size));
}

int wtfGuess(int b[], int size)
{
  int max = b[0], i;
  for (i = 1; i < size; i ++)
    if (b[i] - b[i - 1] > max)
      max = b[i] - b[i - 1];

  if (!evaluate(b, max, size))
    max ++;

  return(max);
}

int main()
{
  int tests, run = 0;
  scanf("%d", &tests);
  while (run ++ < tests)
  {
    int size; scanf("%d", &size);
    int bamboo[size], i;
    for (i = 0; i < size; i ++)
      scanf("%d", &bamboo[i]);

    // int k = bamboo[size - 1];
    // int best = guess(bamboo, 1, k, size);
    int best = wtfGuess(bamboo, size);

    printf("Case %d: %d\n", run, best);
  }
  return(0);
}
