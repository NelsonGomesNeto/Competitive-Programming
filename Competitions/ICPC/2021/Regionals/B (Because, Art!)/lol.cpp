#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const ldouble PI = acosl(-1);
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

  for (int len = 2; len <= n; len <<= 1)
  {
    ldouble ang = 2 * PI / len * (invert ? -1 : 1);
    complex<ldouble> wlen(cosl(ang), sinl(ang));
    for (int i = 0; i < n; i += len)
    {
      complex<ldouble> w(1);
      for (int j = 0; j < (len >> 1); j++)
      {
        complex<ldouble> u = a[i + j], v = a[i + j + (len >> 1)] * w;
        a[i + j] = u + v;
        a[i + j + (len >> 1)] = u - v;
        w *= wlen;
      }
    }
  }

  if (invert)
    for (complex<ldouble> &x: a)
      x /= n;
}
template <typename T>
vector<ldouble> multiply(const vector<T> &a, const vector<T> &b)
{
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

const int maxN = 1e5; int n;
int f[maxN], c[maxN];
vector<int> remf, remc;
lli minimum[maxN], maximum[maxN];

void solveMaximum()
{
  int clo = 0, chi = n - 1, flo = 0, fhi = n - 1, i = 0;
  lli sum1 = 0;
  for (; i < n; ++i)
  {
    if (c[clo] * f[flo] < 0 && c[chi] * f[fhi] < 0)
      break;

    if (c[clo] * f[flo] > c[chi] * f[fhi])
    {
      sum1 += c[clo] * f[flo];
      ++clo, ++flo;
    }
    else
    {
      sum1 += c[chi] * f[fhi];
      --chi, --fhi;
    }

    maximum[i] = sum1;
  }

  DEBUG {
    printf("c:");
    for (int j = clo; j <= chi; ++j)
      printf(" %d", c[j]);
    printf("\nf:");
    for (int j = flo; j <= fhi; ++j)
      printf(" %d", f[j]);
    printf("\n");
  }
  remf.clear(), remc.clear();
  for (int j = clo; j <= chi; ++j) remc.push_back(c[j]);
  for (int j = flo; j <= fhi; ++j) remf.push_back(f[j]);
  if (remc.empty()) return;

  vector<ldouble> res2;
  reverse(remf.begin(), remf.end());
  if (remc[0] * remf[0] > remc.back() * remf.back())
  {

  }
  else
  {
    reverse(remc.begin(), remc.end());
    reverse(remf.begin(), remf.end());    
  }
  res2 = multiply(remc, remf);
//   reverse(remc.begin(), remc.end());
//   reverse(remf.begin(), remf.end());
//   vector<ldouble> res3 = multiply(remc, remf);

  int base = i;
  for (int sz = 0; i < n; ++i, ++sz)
  {
    // lli sum2 = base ? maximum[base - 1] : 0;
    // for (int j = 0; j <= sz; ++j)
    //   sum2 += remc[j] * remf[remf.size() - 1 - sz + j];
    lli sum2 = (base ? maximum[base - 1] : 0) + roundl(res2[sz]);

    // lli sum3 = base ? maximum[base - 1] : 0;
    // for (int j = 0; j <= sz; ++j)
    //   sum3 += remc[remc.size() - 1 - j] * remf[sz - j];
    // lli sum3 = (base ? maximum[base - 1] : 0) + roundl(res3[sz]);

    // maximum[i] = max(sum2, sum3);
    maximum[i] = sum2;
  }
}

void solveMinimum()
{
  int clo = 0, chi = n - 1, flo = 0, fhi = n - 1, i = 0;
  lli sum1 = 0;
  for (; i < n; ++i)
  {
    if (c[clo] * f[fhi] > 0 && c[chi] * f[flo] > 0)
      break;

    if (c[clo] * f[fhi] < c[chi] * f[flo])
    {
      sum1 += c[clo] * f[fhi];
      ++clo, --fhi;
    }
    else
    {
      sum1 += c[chi] * f[flo];
      --chi, ++flo;
    }

    minimum[i] = sum1;
  }

  DEBUG {
    printf("c:");
    for (int j = clo; j <= chi; ++j)
      printf(" %d", c[j]);
    printf("\nf:");
    for (int j = flo; j <= fhi; ++j)
      printf(" %d", f[j]);
    printf("\n");
  }
  remf.clear(), remc.clear();
  for (int j = clo; j <= chi; ++j) remc.push_back(c[j]);
  for (int j = flo; j <= fhi; ++j) remf.push_back(f[j]);
  if (remc.empty()) return;

  vector<ldouble> res2;
  if (remc[0] * remf[0] < remc.back() * remf.back())
  {

  }
  else
  {
    reverse(remc.begin(), remc.end());
    reverse(remf.begin(), remf.end());    
  }
  res2 = multiply(remc, remf);
  
//   reverse(remc.begin(), remc.end());
//   reverse(remf.begin(), remf.end());
//   vector<ldouble> res3 = multiply(remc, remf);

  int base = i;
  for (int sz = 0; i < n; ++i, ++sz)
  {
    // lli sum2 = base ? minimum[base - 1] : 0;
    // for (int j = 0; j <= sz; ++j)
    //   sum2 += remc[j] * remf[sz - j];
    lli sum2 = (base ? minimum[base - 1] : 0) + roundl(res2[sz]);
    // if (sum2 != sum2fft)
    // {
    //   complex<ldouble> a = remc[0], b = remf[0];
    //   DEBUG printf("%d - %lld %.5Lf - %lld %.5Lf\n", sz, sum2, res[sz], remc[0] * remf[0], (a * b).real());
    //   fflush(stdout);
    //   // assert(false);
    // }
    // sum2 = sum2fft;

    // lli sum3 = base ? minimum[base - 1] : 0;
    // for (int j = 0; j <= sz; ++j)
    //   sum3 += remc[remc.size() - 1 - j] * remf[remf.size() - 1 - sz + j];
    // lli sum3 = (base ? minimum[base - 1] : 0) + roundl(res3[sz]);

    // printf("\t%lld %lld %.5lf\n", sum2, sum3, minimum[base - 1] + res[sz]); fflush(stdout);

    // minimum[i] = min(sum2, sum3);
    minimum[i] = sum2;
  }
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &f[i]);
    for (int i = 0; i < n; ++i)
      scanf("%d", &c[i]);

    sort(f, f+n);
    sort(c, c+n);

    solveMinimum();
    solveMaximum();

    for (int i = 0; i < n; ++i)
      printf("%lld %lld\n", minimum[i], maximum[i]);
  }
  return 0;
}