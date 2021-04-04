#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const double PI = acos(-1);

void fft(vector<complex<double>> &a, bool invert)
{
  int n = a.size();
  if (n == 1) return;

  vector<complex<double>> a0(n / 2), a1(n / 2);
  for (int i = 0; 2 * i < n; i++)
    a0[i] = a[2*i], a1[i] = a[2*i + 1];
  fft(a0, invert);
  fft(a1, invert);

  double angle = 2 * PI / n * (invert ? -1 : 1);
  complex<double> w(1), wn(cos(angle), sin(angle));
  for (int i = 0; 2 * i < n; i++)
  {
    a[i] = a0[i] + w * a1[i];
    a[i + n/2] = a0[i] - w * a1[i];

    if (invert)
      a[i] /= 2, a[i + (n >> 1)] /= 2;

    w *= wn;
  }
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

vector<double> getPolynomialBinary(string &str, char baseLetter)
{
  vector<double> pol(str.size());
  for (int i = 0; i < str.size(); i++)
    pol[i] = str[i] == baseLetter ? -1 : 1;
  return pol;
}
vector<int> binaryStringMatching(string &ss, string &tt)
{
  string revtt = tt;
  reverse(revtt.begin(), revtt.end());

  char baseLetter = ss[0];
  vector<double> sPolynomial = getPolynomialBinary(ss, baseLetter);
  vector<double> tPolynomial = getPolynomialBinary(revtt, baseLetter);

  vector<double> stPolynomial = multiply(sPolynomial, tPolynomial);

  vector<int> ans(stPolynomial.size());
  for (int i = 0; i < ans.size(); i++)
    ans[i] = ((int)round(stPolynomial[i]) + tt.size()) >> 1;
  return ans;
}

const int maxN = 1e6; int n;
char ss[maxN + 1];
string s, t;

int main()
{
  while (~scanf(" %s", ss))
  {
    s = string(ss);
    scanf(" %s", ss);
    t = string(ss);

    vector<int> matching = binaryStringMatching(s, t);

    int ans = 1e7;
    for (int i = 0; i + t.size() - 1 < s.size(); i++)
      ans = min(ans, (int)t.size() - matching[t.size() - 1 + i]);
    printf("%d\n", ans);

    DEBUG {
      printf("matchings:\n");
      for (int i = 0; i < matching.size(); i++)
        printf("%3d%c", i, i < matching.size() - 1 ? ' ' : '\n');
      for (int i = 0; i < matching.size(); i++)
        printf("%3d%c", matching[i], i < matching.size() - 1 ? ' ' : '\n');
      for (int i = 0; i + t.size() - 1 < s.size(); i++)
        printf("s[%d : %d] = %s | %d\n", i, i + (int)t.size() - 1, s.substr(i, t.size()).c_str(), matching[i + t.size() - 1]);
      printf("%s\n", string(20, '-').c_str());
    }
  }
  return 0;
}