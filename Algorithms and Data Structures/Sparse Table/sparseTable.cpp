#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;
const int maxSize = 1e6, maxLog = (int) floor(log2(1e6)) + 1;
lli logdp[maxSize + 1];

void printArray(lli a[], int n)
{
  for (int i = 0; i < n; i ++) printf("%lld%c", a[i], i < n - 1 ? ' ' : '\n');
}

struct Data
{
  lli value;
  Data operator+(const Data &other)
  {
    return Data{min(value, other.value)};
  }
};
const Data nil = {(lli)1e18};

template<class T>
struct SparseTable
{
  int size, logn;
  T nil;
  vector<T> data;
  vector<vector<T>> st;
  SparseTable() { }
  SparseTable(int size, T nil) : size(size), nil(nil)
  {
    logn = floor(log2(size)) + 1;
    data.resize(size);
    st.resize(size, vector<T>(logn + 1));
  }
  void build()
  {
    for (int i = 0; i < size; i++)
      st[i][0] = data[i];
    for (int j = 1; j <= logn; j++)
      for (int i = 0, shift = (1 << (j - 1)); i + shift < size; i++)
        st[i][j] = st[i][j - 1] + st[i + shift][j - 1];
  }
  T query(int lo, int hi)
  {
    int qs = logdp[hi - lo + 1];
    return st[lo][qs] + st[hi - (1 << qs) + 1][qs];
    // T ans = nil;
    // for (int j = logn; j >= 0; j --)
    //   if (lo + (1 << j) - 1 <= hi)
    //   {
    //     ans = ans + st[lo][j];
    //     lo += (1 << j);
    //   }
    // return ans;
  }
};
SparseTable<Data> sparseTable;

int main()
{
  logdp[1] = 0;
  for (int i = 2; i <= maxSize; i ++) logdp[i] = logdp[i >> 1] + 1;

  int n; scanf("%d", &n);
  lli array[n]; for (int i = 0; i < n; i ++) scanf("%lld", &array[i]);

  sparseTable = SparseTable<Data>(n, nil);
  for (int i = 0; i < n; i++)
    sparseTable.data[i].value = array[i];
  sparseTable.build();
  // printf("size: %d, logn: %d\n", n, logn);

  // for (int i = 0; i < n; i ++) printArray(sparseTable[i], logn + 1);

  int lo, hi;
  while (scanf("%d %d", &lo, &hi) != EOF)
    printf("[%d, %d] = %lld\n", lo, hi, sparseTable.query(lo, hi).value);

  return(0);
}