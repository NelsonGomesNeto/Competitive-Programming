#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

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

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
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

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

void printArr(vector<int> arr)
{
  for (int i = 0; i < arr.size(); i++)
    printf("%d%c", arr[i], i < arr.size() - 1 ? ' ' : '\n');
}
void printArr(vector<cd> arr)
{
  for (int i = 0; i < arr.size(); i++)
    printf("(%lf, %lf i)%c", arr[i].real(), arr[i].imag(), i < arr.size() - 1 ? ' ' : '\n');
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

    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    printArr(fa);
    fft(fa, false);
    printArr(fb);

    vector<int> res = multiply(a, b);
    printArr(res);
  }
  return 0;
}