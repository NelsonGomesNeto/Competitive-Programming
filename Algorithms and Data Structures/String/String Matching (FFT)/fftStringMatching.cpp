#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  String Matching can me formulatted as polynomial multiplication problem.

  A(x) * B(x) = C(x)
    A(x) coefficients is "a", B(x) is "b" and C(x) is "c"

  If you look at the coefficients of C(x):
  c[i] = sum(a[j] * b[i - j], where j in [0 : i])

  Suppose we have a magical way 

*/

void printPolynomial(vector<complex<double>> &p)
{
  for (int i = 0; i < p.size(); i++)
    printf("%.2lf%c", p[i].real(), i < p.size() - 1 ? ' ' : '\n');
}
void printPolynomial(vector<double> &p)
{
  for (int i = 0; i < p.size(); i++)
    printf("%.2lf%c", p[i], i < p.size() - 1 ? ' ' : '\n');
}

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

const int alphabetSize = 26; const char startingLetter = 'a';
const double eps = 1e-12;
const int maxN = 1e6;
char ss[maxN + 1];

string s, t;
vector<complex<double>> getPolynomial(string &str, bool negative = false)
{
  vector<complex<double>> poly(str.size());
  for (int i = 0; i < str.size(); i++)
  {
    double angle = 2 * PI * (str[i] - startingLetter) / alphabetSize;
    if (str[i] == '*') poly[i] = 0;
    else poly[i] = complex<double>(cos(angle), negative ? -sin(angle) : sin(angle));
  }
  return poly;
}
vector<int> stringMatching(string &ss, string &tt)
{
  string revtt = tt;
  reverse(revtt.begin(), revtt.end());
  int wildCards = 0;
  for (char c: tt) wildCards += c == '*';

  vector<complex<double>> sPolynomial = getPolynomial(ss);
  vector<complex<double>> tPolynomial = getPolynomial(revtt, true);

  vector<double> stPolynomial = multiply(sPolynomial, tPolynomial);

  vector<int> ans(stPolynomial.size());
  for (int i = 0; i < ans.size(); i++)
    ans[i] = abs(stPolynomial[i] - (tt.size() - wildCards)) <= eps;
  return ans;
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

int main()
{
  while (~scanf(" %s", ss))
  {
    s = string(ss);
    scanf(" %s", ss);
    t = string(ss);
    printf("%s\n%s\n", s.c_str(), t.c_str());

    set<char> letters;
    for (char c: s) letters.insert(c);
    for (char c: t) letters.insert(c);

    vector<int> ans = letters.size() <= 2 ? binaryStringMatching(s, t) : stringMatching(s, t);

    printf("matchings:\n");
    for (int i = 0; i < ans.size(); i++)
      printf("%3d%c", i, i < ans.size() - 1 ? ' ' : '\n');
    for (int i = 0; i < ans.size(); i++)
      printf("%3d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
    for (int i = 0; i + t.size() - 1 < s.size(); i++)
      printf("s[%d : %d] = %s | %d\n", i, i + (int)t.size() - 1, s.substr(i, t.size()).c_str(), ans[i + t.size() - 1]);
    printf("%s\n", string(20, '-').c_str());
  }
  return 0;
}