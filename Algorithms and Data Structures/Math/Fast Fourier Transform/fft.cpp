#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

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
    double ang = 2 * PI / len * (invert ? -1 : 1);
    complex<double> wlen(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len)
    {
      complex<double> w(1);
      for (int j = 0; j < (len >> 1); j++)
      {
        complex<double> u = a[i + j], v = a[i + j + (len >> 1)] * w;
        a[i + j] = u + v;
        a[i + j + (len >> 1)] = u - v;
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

void printArr(vector<int> arr)
{
  for (int i = 0; i < arr.size(); i++)
    printf("%d%c", arr[i], i < arr.size() - 1 ? ' ' : '\n');
}
void printArr(vector<complex<double>> arr)
{
  for (int i = 0; i < arr.size(); i++)
  {
    printf("(%.3lf, %.3lfi)%c", arr[i].real(), arr[i].imag(), i < arr.size() - 1 ? ' ' : '\n');
    // printf("(%.3lf + %.3lf*i)*x^%d%s", arr[i].real(), arr[i].imag(), arr.size() - i - 1, i < arr.size() - 1 ? " + " : "\n");
  }
}

int main()
{
  int n, m;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    for (int i = 0; i < m; i++)
      scanf("%d", &b[i]);

    vector<complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    printf("roots: "); printArr(fa);
    fft(fa, false);
    printf("roots: "); printArr(fb);

    vector<int> res = multiply(a, b);
    printArr(res);
  }
  return 0;
}