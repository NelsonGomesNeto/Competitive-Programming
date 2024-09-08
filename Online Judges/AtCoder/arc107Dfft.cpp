#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;
const int maxDiv = 1 << 11;

// maximum divisor will be: 2^11 = 2048 (so make it the common divisor)
const int optionsSize = 12;

const int maxN = 3e3, maxK = 3000 * 2048;
int n, k;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<lli> multiply(vector<lli> const& a, vector<lli> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
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

    vector<lli> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    k *= maxDiv;

    vector<lli> a(n + 1);
    for (int i = 0; i <= n; i++)
      a[i] = 1;

    for (int i = 1; i < optionsSize; i++)
    {
      vector<lli> b(maxK + 1)
      for (int j = 1; )

    }

    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}