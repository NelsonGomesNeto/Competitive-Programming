#include <stdio.h>
#include <stdlib.h>

#define maxN 200001
typedef struct node NODE;
typedef long long int lli;

lli y[maxN], xx[maxN], x[maxN], ySize;
NODE *r[maxN], *l[maxN];

struct node {
    lli val, h;
    NODE *left, *right;
};

int getPos(lli data)
{
  int lo = 0, hi = ySize - 1;
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    if (y[mid] >= data) hi = mid;
    else lo = mid + 1;
  }
  return lo;
}
int upperBound(lli data)
{
  int lo = 0, hi = ySize - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (y[mid] <= data) lo = mid;
    else hi = mid - 1;
  }
  return lo + 1;
}

NODE *iterativeAdd(NODE *root, lli data) {
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->val = data;
    newNode->h = 1;

    int pos = getPos(data);
    if (r[pos] == NULL)
      r[pos] = newNode;
    else
    {
      printf("%lld", l[pos]->h + 1);
      newNode->h = r[pos]->h + 1;
      l[pos] = newNode;
      return root;
    }

    lli height = 0;
    if (root == NULL) {
        // printf("#1#");
        printf("1");
        l[pos] = newNode;
        return newNode;
    }

    // printf("%lld %lld %d\n", data, y[getPos(data) + 1], getPos(data) + 1);
    NODE *parent = NULL, *current = r[pos + 1];
    if (current == NULL) current = root, height = 1;
    else height = current->h;
    // printf("\t%lld %lld\n", current->val, height);
    // current = root;
    while (current != NULL) {
        parent = current;
        if (current->val < data) {
            current = current->right;
        } else {
            current = current->left;
        }
        ++height;
    }
    if (parent->val < data) {
        parent->right = newNode, newNode->h = height;
    } else {
        parent->left = newNode, newNode->h = height;
    }
    l[pos] = newNode;
    // printf("#%lld#", height);
    printf("%lld", height);
    return root;
}

int compare(const void *a, const void *b)
{
  return *((lli*)a) > *((lli*)b);
}

int main() {
    lli n;
    scanf("%lld" ,&n);
    int i;
    NODE *root = NULL;
    for (i = 0; i < n; ++i) {
        scanf("%lld", &x[i]);
        xx[i] = x[i];
    }
    qsort(xx, n, sizeof(lli), compare);

    for (i = 0; i < n;)
    {
      int j = i;
      while (j + 1 < n && xx[i] == xx[j + 1]) j ++;
      r[ySize] = NULL, l[ySize] = NULL;
      y[ySize++] = xx[i];
      i = j + 1;
    }
    r[ySize] = l[ySize] = NULL;

    // printf("%lld\n", ySize);
    // for (i = 0; i < ySize; i ++)
    //   printf("%lld%c", y[i], i < ySize - 1 ? ' ' : '\n');

    for (i = 0; i < n; ++i) {
        root = iterativeAdd(root, x[i]);
        if (i != n - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
    return 0;
}