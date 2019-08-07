#include <stdio.h>
#define ull long long int

ull reducted(ull size)
{
  if (size % 4 == 1)
    return(0);
  else if (size % 4 == 0)
    return(3);
  else if (size % 4 == 2)
    return(1);
  else
    return(2);
}

ull mult(ull j, ull a)
{
  if (a == 0) return(0);
  ull res = mult(j, a / 2) % 1000000007;
  if (a & 1)
    return((((res + res) % 1000000007) + j) % 1000000007);
  return((res + res) % 1000000007);
}

void doReduction(ull a[], ull size)
{
  ull i, times = reducted(size), j, k;
  for (i = 0, k = 1; i < times; i ++)
  {
    for (j = 0; j < size - i - 1; j ++, k *= -1)
    {
      a[j] = (a[j] + (mult(k, a[j + 1])));
      if (a[j] < 0) a[j] += 1000000007;
      a[j] %= 1000000007;
    }
  }
}

ull binomial2(ull n, ull k)
{
  if (k < 0 || k > n) return(0);
  if (k == 0 || k == n) return(1);
  k = k < n - k ? k : n - k;
  ull c = 1, i;
  for (i = 0; i < k; i ++)
    c = mult(c, (n - i)) / (i + 1);
  return(c);
}

ull binomial(ull n, ull k)
{
  ull c = 1, i;
  if (k > n - k) k = n - k;
  for (i = 1; i <= k; i ++, n --)
    c = (ull) (mult(c/i, n) + mult(c%i, n) / i) % 1000000007;

  return(c % 1000000007);
}

ull doSum(ull a[], ull size)
{
  ull i, k, mid = size / 2; ull sum = 0, j;
  ull pot = (size - 1) / 2;
  for (i = 0, k = 0; i < size; i += 2, k ++)
  {
    j = binomial2(pot, k);
    //printf("%llu %llu\n", j, a[i]);
    sum += mult(j, a[i]);
    if (sum < 0) sum += 1000000007;
    sum %= 1000000007;
  }

  if (sum < 0) sum += 1000000007;

  return(sum % 1000000007);
}

int main()
{
  ull numbers; scanf("%lld", &numbers);
  ull array[numbers], i;
  for (i = 0; i < numbers; i ++)
    scanf("%lld", &array[i]);

  doReduction(array, numbers);

  printf("%lld\n", doSum(array, numbers - reducted(numbers)));

  return(0);
}