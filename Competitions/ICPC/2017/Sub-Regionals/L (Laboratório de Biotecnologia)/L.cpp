#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
char s[maxN + 1];

const double PI = acos(-1);

void fft(vector<complex<double>> &a, bool invert)
{
  int n = a.size();

  for (int i = 1, j = 0; i < n; i++)
  {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1)
      j ^= bit;
    j ^= bit;

    if (i < j)
      swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1)
  {
    int len2 = len >> 1;
    double ang = 2 * PI / len * (invert ? -1 : 1);
    complex<double> wlen(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len)
    {
      complex<double> w(1), t;
      for (int j = i, end = len2 + i; j < end; j++)
      {
        complex<double> u = a[j], v = a[j + len2] * w;
        a[j] = u + v;
        a[j + len2] = u - v;
        w *= wlen;
      }
    }
  }

  if (invert)
    for (complex<double> &x: a)
      x /= n;
}

template <typename T>
vector<double> multiply(const vector<T> &a, const vector<T> &b)
{
  vector<complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < a.size() + b.size()) 
    n <<= 1;
  fa.resize(n);
  fb.resize(n);

  fft(fa, false);
  fft(fb, false);
  for (int i = 0; i < n; i++)
    fa[i] *= fb[i];
  fft(fa, true);

  vector<double> result(n);
  for (int i = 0; i < n; i++)
  {
    result[i] = fa[i].real();
    // result[i] = round(fa[i].real());
  }
  return result;
}


int main()
{
  while (~scanf(" %s", s))
  {
    int n = strlen(s);

    int totalSum = 0;
    for (int i = 0; i < n; i++)
      totalSum += s[i] - 'a' + 1;
    
    vector<bool> a(totalSum + 1);
    vector<bool> b(totalSum + 1);
    int sum = 0;
    a[0] = true, b[totalSum] = true;
    for (int i = 0; i < n; i++)
    {
      sum += s[i] - 'a' + 1;
      a[sum] = b[totalSum - sum] = true;
    }
    vector<double> ans = multiply(a, b);

    int res = 0;
    for (int i = totalSum + 1; i < ans.size(); i++)
      res += round(ans[i]) > 0;
    printf("%d\n", res);
  }
  return 0;
}