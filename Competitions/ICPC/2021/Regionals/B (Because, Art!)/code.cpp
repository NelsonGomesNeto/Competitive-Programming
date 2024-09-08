#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

namespace FFT
{
  const ldouble PI = acosl(-1);
  const ldouble PI2 = 2*PI;
  vector<vector<complex<ldouble>>> memoW[2];
  int maxSize = 0;

  void precalc(int n)
  {
    int nn = 1, p = 0;
    while (nn < n + n)
      nn <<= 1, ++p;
    maxSize = nn;
    memoW[0].resize(p);
    memoW[1].resize(p);

    for (int len = 2, lenp = 0; len <= maxSize; len <<= 1, ++lenp)
    {
      memoW[0][lenp].resize(len >> 1);
      memoW[1][lenp].resize(len >> 1);
      ldouble ang = PI2 / len;
      ldouble c = cosl(ang), s = sinl(ang);
      complex<ldouble> wlen(c, s), wlenInvert(c, -s);
      memoW[0][lenp][0] = memoW[1][lenp][0] = 1;
      for (int j = 1; j < (len >> 1); ++j)
      {
        memoW[0][lenp][j] = memoW[0][lenp][j >> 1] * memoW[0][lenp][j >> 1];
        memoW[1][lenp][j] = memoW[1][lenp][j >> 1] * memoW[1][lenp][j >> 1];
        if (j & 1) memoW[0][lenp][j] *= wlen, memoW[1][lenp][j] *= wlenInvert;
      }
    }
  }

  void fft(vector<complex<ldouble>> &a, bool invert)
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

    for (int len = 2, lenp = 0; len <= n; len <<= 1, ++lenp)
      for (int i = 0; i < n; i += len)
      {
        int j = 0;
        for (const auto& w: memoW[invert][lenp])
        {
          complex<ldouble> u = a[i + j], v = a[i + j + (len >> 1)] * w;
          a[i + j] = u + v;
          a[i + j + (len >> 1)] = u - v;
          ++j;
        }
      }

    if (invert)
      for (complex<ldouble> &x: a)
        x /= n;
  }
  template <typename T>
  vector<ldouble> multiply(const vector<T> &a, const vector<T> &b)
  {
    assert(maxSize > 0);

    vector<complex<ldouble>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
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

    vector<ldouble> result(n);
    for (int i = 0; i < n; i++)
    {
      result[i] = fa[i].real();
      // result[i] = roundl(fa[i].real());
    }
    return result;
  }
}

const int maxN = 1e5; int n;
int f[maxN], c[maxN];
vector<int> remf, remc;
lli minimum[maxN], maximum[maxN];

void solveMaximum()
{
  int clo = 0, chi = n - 1, flo = 0, fhi = n - 1, i = 0;
  lli sum = 0;
  for (; i < n; ++i)
  {
    int loCf = c[clo] * f[flo], hiCf = c[chi] * f[fhi];
    if (loCf < 0 && hiCf < 0)
      break;

    if (loCf > hiCf)
    {
      sum += loCf;
      ++clo, ++flo;
    }
    else
    {
      sum += hiCf;
      --chi, --fhi;
    }

    maximum[i] = sum;
  }

  remf.clear(), remc.clear();
  remc.reserve(n - i), remf.reserve(n - i);
  for (int j = clo; j <= chi; ++j) remc.push_back(c[j]);
  for (int j = flo; j <= fhi; ++j) remf.push_back(f[j]);
  if (remc.empty()) return;

  reverse(remf.begin(), remf.end());
  if (remc[0] * remf[0] < remc.back() * remf.back())
  {
    reverse(remc.begin(), remc.end());
    reverse(remf.begin(), remf.end());
  }
  vector<ldouble> remRes = FFT::multiply(remc, remf);

  for (int sz = 0; i < n; ++i, ++sz)
    maximum[i] = sum + roundl(remRes[sz]);
}

void solveMinimum()
{
  int clo = 0, chi = n - 1, flo = 0, fhi = n - 1, i = 0;
  lli sum = 0;
  for (; i < n; ++i)
  {
    int lohiCf = c[clo] * f[fhi], hiloCf = c[chi] * f[flo];
    if (lohiCf > 0 && hiloCf > 0)
      break;

    if (lohiCf < hiloCf)
    {
      sum += lohiCf;
      ++clo, --fhi;
    }
    else
    {
      sum += hiloCf;
      --chi, ++flo;
    }

    minimum[i] = sum;
  }

  remf.clear(), remc.clear();
  remc.reserve(n - i), remf.reserve(n - i);
  for (int j = clo; j <= chi; ++j) remc.push_back(c[j]);
  for (int j = flo; j <= fhi; ++j) remf.push_back(f[j]);
  if (remc.empty()) return;

  if (remc[0] * remf[0] > remc.back() * remf.back())
  {
    reverse(remc.begin(), remc.end());
    reverse(remf.begin(), remf.end());
  }
  vector<ldouble> remRes = FFT::multiply(remc, remf);

  for (int sz = 0; i < n; ++i, ++sz)
    minimum[i] = sum + roundl(remRes[sz]);
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // while (~scanf("%d", &n))
  while (cin >> n)
  {
    FFT::precalc(n);

    for (int i = 0; i < n; ++i)
      // scanf("%d", &f[i]);
      cin >> f[i];
    for (int i = 0; i < n; ++i)
      // scanf("%d", &c[i]);
      cin >> c[i];

    sort(f, f+n);
    sort(c, c+n);

    solveMinimum();
    solveMaximum();

    for (int i = 0; i < n; ++i)
      // printf("%lld %lld\n", minimum[i], maximum[i]);
      cout << minimum[i] << " " << maximum[i] << "\n";
  }
  return 0;
}