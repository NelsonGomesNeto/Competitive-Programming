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

/*

*/

vector<double> interpolate(vector<double> &x, vector<double> &y)
{
  interpolateRec(x, y, 0, x.size());
}
vector<double> interpolateRec(vector<double> &x, vector<double> &y, int lo, int hi)
{
  if (hi - lo == 1)
  {

  }
}

const int maxN = 1e6; int n;
vector<double> p, x, y;

int main()
{
  while (~scanf("%d", &n))
  {
    p.clear(); p.resize(n);

    x.clear(); x.resize(n);
    for (int i = 0; i < n; i++) scanf("%lf", &x[i]);

    y.clear(); y.resize(n);
    for (int i = 0; i < n; i++) scanf("%lf", &y[i]);

    for (int i = 0; i < n; i++)
      printf("f(%lf) = %lf\n", x[i], y[i]);
  }
  return 0;
}