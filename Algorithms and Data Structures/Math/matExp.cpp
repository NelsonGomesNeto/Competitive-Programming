#include <bits/stdc++.h>
#define lli long long int

lli matMult(lli a[3][3], lli b[3][3])
{
  lli aux[3][3]; memset(aux, 0, sizeof(aux));
  for (int i = 0; i < 3; i ++)
    for (int j = 0; j < 3; j ++)
      for (int k = 0; k < 3; k ++)
        aux[i][j] = (aux[i][j] + a[i][k] * b[k][j] % mod) % mod;
  memcpy(a, aux, sizeof(aux));
}

lli matExp(int n)
{
  lli ans[3][3]; memset(ans, 0, sizeof(ans)); for (int i = 0; i < 3; i ++) ans[i][i] = 1;
  lli x[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}}; // base Matrix, could have been passed as a parameter
  while (n)
  {
    if (n & 1) matMult(ans, x);
    matMult(x, x), n >>= 1;
  }
  lli sum = 0; for (int i = 0; i < 3; i ++) for (int j = 0; j < 3; j ++) sum = (sum + ans[i][j]) % mod;
  return(sum);
}

int main()
{

  return(0);
}
