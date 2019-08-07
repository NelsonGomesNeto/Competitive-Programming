#include <bits/stdc++.h>
#define lli long long int

int main()
{
  lli n, k, s; scanf("%lld %lld %lld", &n, &k, &s);
  if ((n - 1) * k < s || k > s)
    printf("NO\n");
  else
  {
    printf("YES\n");
    lli at = 1, biggest = n - 1, now = 0;
    lli jumping = s / biggest + (s % biggest != 0);
    if (jumping < k || jumping * biggest > s) jumping --;
    while (jumping * biggest + (k - jumping) > s) jumping --;
    for (int i = 0; i < jumping; i ++)
    {
      at = at == 1 ? n : 1;
      printf("%lld ", at);
      now += biggest;
    }

    lli next = at == 1 ? 2 : n - 1, prev = at;
    for (int i = jumping; i < k - 1; i ++)
    {
      at = at != next ? next: prev;
      printf("%lld ", at);
      now ++;
    }

    if (now < s)
      printf("%lld\n", at > 2 ? at - (s - now) : at + (s - now));
  }

  return(0);
}
