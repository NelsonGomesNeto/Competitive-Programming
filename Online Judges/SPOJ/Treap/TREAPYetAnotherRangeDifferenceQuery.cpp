#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int minimumNil = 1e9 + 1, maximumNil = -1;

int randPriority() { return rand() * 65536 + rand(); }
struct Treap
{
  int key, priority, size = 1, index, minimum, maximum, nextDiff, rangeMinDiff;
  Treap *l = NULL, *r = NULL;
  Treap(int key, int priority = randPriority()) : key(key), priority(priority)
  {
    minimum = maximum = key;
    nextDiff = rangeMinDiff = minimumNil;
  }
  void print(char end='\0') { printf("(%2d, %11d, %2d | %3d %3d %3d %3d)%c", key, priority, size, minimum, maximum, nextDiff, rangeMinDiff, end); }
};
Treap *treap;
void updateNode(Treap *&t)
{
  if (t)
  {
    t->size = 1 + (t->l ? t->l->size : 0) + (t->r ? t->r->size : 0);
    t->minimum = min({t->key, t->l ? t->l->minimum : minimumNil, t->r ? t->r->minimum : minimumNil});
    t->maximum = max({t->key, t->l ? t->l->maximum : maximumNil, t->r ? t->r->maximum : maximumNil});
    t->rangeMinDiff = min({t->nextDiff, t->l ? t->l->rangeMinDiff : minimumNil, t->r ? t->r->rangeMinDiff : minimumNil});
  }
}
void split(Treap *t, int key, Treap *&l, Treap *&r)
{
  if (!t) l = r = NULL;
  else if (key < t->key) split(t->l, key, l, t->l), r = t;
  else split(t->r, key, t->r, r), l = t;
}
void insert(Treap *&t, Treap *item)
{
  if (!t) t = item;
  else if (t->key == item->key);
  else if (item->priority > t->priority)
  {
    split(t, item->key, item->l, item->r);
    t = item;
  }
  else insert(item->key < t->key ? t->l : t->r, item);
  updateNode(t);
}
void merge(Treap *&t, Treap *l, Treap *r)
{
  if (!l || !r) t = l ? l : r;
  else if (l->priority > r->priority) merge(l->r, l->r, r), t = l;
  else merge(r->l, l, r->l), t = r;
}
void erase(Treap *&t, int key)
{
  if (t == NULL) return;
  if (t->key == key) merge(t, t->l, t->r);
  else erase(key < t->key ? t->l : t->r, key);
  updateNode(t);
}
void print(Treap *t, int depth = 0)
{
  if (!t) return;
  print(t->r, depth + 1);
  for (int i = 0; i < depth; i++) printf("    ");
  t->print('\n');
  print(t->l, depth + 1);
}
Treap* find(Treap *&t, int key, int before = 0)
{
  if (!t) return NULL;
  t->index = before + (t->l ? t->l->size : 0);
  if (t->key == key) return t;
  return find(key < t->key ? t->l : t->r, key, key < t->key ? before : t->index + 1);
}
Treap* findByIndex(Treap *&t, int index, int before = 0)
{
  int currentIndex = before + (t->l ? t->l->size : 0);
  if (index == currentIndex) return t;
  if (t->l && index < currentIndex) return findByIndex(t->l, index, before);
  return findByIndex(t->r, index, currentIndex + 1);
}

int getMinimum(Treap *&t, int qlo, int qhi, int lo, int hi)
{
  if (hi < qlo || lo > qhi) return minimumNil;
  if (lo >= qlo && hi <= qhi) return t->minimum;
  int currentIndex = lo + (t->l ? t->l->size : 0);
  return min(
  {
    getMinimum(t->l, qlo, qhi, lo, currentIndex - 1),
    currentIndex >= qlo && currentIndex <= qhi ? t->key : minimumNil,
    getMinimum(t->r, qlo, qhi, currentIndex + 1, hi)
  });
}
int getMaximum(Treap *&t, int qlo, int qhi, int lo, int hi)
{
  if (hi < qlo || lo > qhi) return maximumNil;
  if (lo >= qlo && hi <= qhi) return t->maximum;
  int currentIndex = lo + (t->l ? t->l->size : 0);
  return max(
  {
    getMaximum(t->l, qlo, qhi, lo, currentIndex - 1),
    currentIndex >= qlo && currentIndex <= qhi ? t->key : maximumNil,
    getMaximum(t->r, qlo, qhi, currentIndex + 1, hi)
  });
}
int getMinDiff(Treap *&t, int qlo, int qhi, int lo, int hi)
{
  if (hi < qlo || lo > qhi) return minimumNil;
  if (lo >= qlo && hi <= qhi) return t->rangeMinDiff;
  int currentIndex = lo + (t->l ? t->l->size : 0);
  return min(
  {
    getMinDiff(t->l, qlo, qhi, lo, currentIndex - 1),
    currentIndex >= qlo && currentIndex <= qhi ? t->nextDiff : minimumNil,
    getMinDiff(t->r, qlo, qhi, currentIndex + 1, hi)
  });
}

int main()
{
  int q; scanf("%d", &q);
  while (q--)
  {
    char op[2]; scanf(" %s", op);
    if (op[0] == 'I')
    {
      int key; scanf("%d", &key);
      insert(treap, new Treap(key));

      Treap *t = find(treap, key);
      if (t->index - 1 >= 0)
      {
        Treap *prv = findByIndex(treap, t->index - 1);
        prv->nextDiff = abs(t->key - prv->key);
        insert(treap, prv);
      }
      if (t->index + 1 < treap->size)
      {
        Treap *nxt = findByIndex(treap, t->index + 1);
        t->nextDiff = abs(t->key - nxt->key);
        insert(treap, t);
      }
    }
    else if (op[0] == 'D')
    {
      int key; scanf("%d", &key);
      Treap *t = find(treap, key);
      if (t != NULL)
      {
        erase(treap, key);
        if (treap->size >= 2 && t->index - 1 >= 0)
        {
          Treap *prv = findByIndex(treap, t->index - 1);
          Treap *nxt = findByIndex(treap, t->index);
          prv->nextDiff = abs(nxt->key - prv->key);
          insert(treap, prv);
        }
      }
    }
    else if (op[0] == 'N')
    {
      int lo, hi; scanf("%d %d", &lo, &hi);
      if (lo == hi) printf("-1\n");
      else
      {
        int minDiff = getMinDiff(treap, lo, hi - 1, 0, treap->size - 1);
        DEBUG {
          printf("--------------\n");
          print(treap);
          printf("N(%d, %d) = %d\n", lo, hi, minDiff);
          printf("--------------\n");
        } else
          printf("%d\n", minDiff);
      }
    }
    else if (op[0] == 'X')
    {
      int lo, hi; scanf("%d %d", &lo, &hi);
      if (lo == hi) printf("-1\n");
      else
      {
        int minimum = getMinimum(treap, lo, hi, 0, treap->size - 1);
        int maximum = getMaximum(treap, lo, hi, 0, treap->size - 1);
        DEBUG {
          printf("--------------\n");
          print(treap);
          printf("X(%d, %d) = %d\n", lo, hi, maximum - minimum);
          printf("--------------\n");
        } else
          printf("%d\n", maximum - minimum);
      }
    }
  }
  return 0;
}