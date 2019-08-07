#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
int segtree[9][(int) 4e5], aux[9], inRange[9], lazy[(int) 4e5];
int n, q;

void printSpacing(int depth)
{
  for (int i = 0; i < depth; i ++) printf("   ");
}

void printNotes(int i)
{
  for (int note = 0; note < 9; note ++) printf(" (%d, %d)", note, segtree[note][i]);
  printf(" | (%d)\n", lazy[i]);
}

void lazyUpdate(int lo, int hi, int i);

void printSegTree(int lo, int hi, int i, int depth)
{
  lazyUpdate(lo, hi, i);
  printSpacing(depth); printf("[%d, %d] =", lo, hi); printNotes(i);
  if (lo >= hi) return;
  int mid = (lo + hi) >> 1;
  printSegTree(lo, mid, 2*i, depth + 1);
  printSegTree(mid + 1, hi, 2*i + 1, depth + 1);
}

void build(int lo, int hi, int i)
{
  if (lo >= hi)
  {
    for (int note = 0; note < 9; note ++) segtree[note][i] = note == 1;
    return;
  }
  int mid = (lo + hi) >> 1;
  build(lo, mid, 2*i);
  build(mid + 1, hi, 2*i + 1);
  for (int note = 0; note < 9; note ++) segtree[note][i] = segtree[note][2*i] + segtree[note][2*i + 1];
}

void lazyUpdate(int lo, int hi, int i)
{
  if (lazy[i])
  {
    for (int note = 0; note < 9; note ++) aux[(note + lazy[i]) % 9] = segtree[note][i];
    for (int note = 0; note < 9; note ++) segtree[note][i] = aux[note];
    if (lo != hi) lazy[2*i] += lazy[i], lazy[2*i + 1] += lazy[i];
    lazy[i] = 0;
  }
}

void query(int qlo, int qhi, int lo, int hi, int i)
{
  lazyUpdate(lo, hi, i);
  if (lo > qhi || hi < qlo) return;
  if (lo >= qlo && hi <= qhi)
  {
    for (int note = 0; note < 9; note ++) inRange[note] += segtree[note][i];
    return;
  }
  int mid = (lo + hi) >> 1;
  query(qlo, qhi, lo, mid, 2*i);
  query(qlo, qhi, mid + 1, hi, 2*i + 1);
}

void update(int qlo, int qhi, int newNote, int lo, int hi, int i)
{
  lazyUpdate(lo, hi, i);
  if (lo > qhi || hi < qlo) return;
  if (lo >= qlo && hi <= qhi)
  {
    lazy[i] += newNote;
    lazyUpdate(lo, hi, i);
    return;
  }
  int mid = (lo + hi) >> 1;
  update(qlo, qhi, newNote, lo, mid, 2*i);
  update(qlo, qhi, newNote, mid + 1, hi, 2*i + 1);
  for (int note = 0; note < 9; note ++) segtree[note][i] = segtree[note][2*i] + segtree[note][2*i + 1];
}

int getNote(int lo, int hi)
{
  int note = -1, freq = -1; memset(inRange, 0, sizeof(inRange));
  query(lo, hi, 0, n - 1, 1);
  for (int i = 0; i < 9; i ++)
    if (inRange[i] >= freq)
      note = i, freq = inRange[i];
  return(note);
}

int main()
{
  scanf("%d %d", &n, &q); memset(lazy, 0, sizeof(lazy));
  build(0, n - 1, 1);

  int lo, hi;
  while (q --)
  {
    scanf("%d %d", &lo, &hi);
    // DEBUG printSegTree(0, n - 1, 1, 0);
    update(lo, hi, getNote(lo, hi), 0, n - 1, 1);
  }
  // DEBUG printSegTree(0, n - 1, 1, 0);
  for (int i = 0; i < n; i ++) printf("%d\n", getNote(i, i));
  return(0);
}