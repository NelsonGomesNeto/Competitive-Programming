#include <bits/stdc++.h>
using namespace std;
#define trioint pair<int, pair<int, int> >
int t[(int) 3e6], o[(int) 3e6], c[(int) 3e6];

void createSegmentTree(char array[], int i, int lo, int hi)
{
  if (lo == hi)
  {
    t[i] = c[i] = o[i] = 0;
    if (array[lo] == '(')
      o[i] = 1;
    else
      c[i] = 1;
    return;
  }
  int mid = (lo + hi) / 2;
  createSegmentTree(array, 2*i + 1, lo, mid);
  createSegmentTree(array, 2*i + 2, mid + 1, hi);
  int temp = min(o[2*i + 1], c[2*i + 2]);
  t[i] = t[2*i + 1] + t[2*i + 2] + temp;
  o[i] = o[2*i + 1] + o[2*i + 2] - temp;
  c[i] = c[2*i + 1] + c[2*i + 2] - temp;
}

trioint gs(int i, int lo, int hi, int qlo, int qhi)
{
  if (lo >= qlo && hi <= qhi)
  {
    trioint ans; ans.first = t[i]; ans.second.first = o[i]; ans.second.second = c[i];
    return(ans);
  }
  else if (lo > qhi || hi < qlo)
  {
    trioint ans; ans.first = 0; ans.second.first = 0; ans.second.second = 0;
    return(ans);
  }
  int mid = (lo + hi) / 2, temp;
  trioint a = gs(2*i + 1, lo, mid, qlo, qhi), b = gs(2*i + 2, mid + 1, hi, qlo, qhi), ans;
  temp = min(a.second.first, b.second.second);
  ans.first = a.first + b.first + temp;
  ans.second.first = a.second.first + b.second.first - temp;
  ans.second.second = a.second.second + b.second.second - temp;
  return(ans);
}

trioint getSum(int size, int lo, int hi)
{
  trioint ans; ans.first = 0; ans.second.first = 0; ans.second.second = 0;
  if (lo < 0 || hi > size - 1 || lo > hi) return(ans);
  return(gs(0, 0, size - 1, lo, hi));
}

int main()
{
  char bracket[(int) 1e6]; scanf("%s", bracket);
  createSegmentTree(bracket, 0, 0, strlen(bracket) - 1);
  int size = strlen(bracket);
  int queries; scanf("%d", &queries);
  while (queries -- > 0)
  {
    int lo, hi; scanf("%d %d", &lo, &hi); lo --; hi --;
    printf("%d\n", 2 * getSum(size, lo, hi).first);
  }
  return(0);
}