#include <bits/stdc++.h>
using namespace std;
int MAX = 100001;

int main()
{
  int n; scanf("%d", &n);
  int i, num, biggest = 0; long long int freq[MAX], dp[MAX];
  memset(freq, 0, sizeof(freq));
  for (i = 0; i < n; i ++)
  {
    scanf("%d", &num);
    biggest = max(biggest, num);
    freq[num] ++;
  }

  dp[0] = 0; dp[1] = freq[1];

  for (i = 2; i <= biggest; i ++)
    dp[i] = max(dp[i - 2] + (freq[i]*i), dp[i - 1]);

  printf("%lld\n", dp[biggest]);

  return(0);
}