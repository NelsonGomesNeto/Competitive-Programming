#include <bits/stdc++.h>
using namespace std;
 
#define MAXN (int)(3e5 + 5)
#define MAXL 20
#define F first
#define S second
#define endl "\n"
#define MOD (lli)(1e9 + 9)
#define MOD2 (lli)(1e9 + 7)
#define lli long long int
#define sz(a) int(a.size())
#define DEBUG if (0) cout << "aqui" << endl;
#define PI 2 * acos(0.0)
typedef pair<int, lli> ii;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int dddx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dddy[] = {0, 0, 1, -1, 1, -1, 1, -1};

int n, m;
vector<int> vec;
vector<pair<int, pair<int, int> > > vec2;

vector<int> tree[4*MAXN];

void build(int node=1, int l=1, int r=n){
	// cout << node << endl;
	if(l == r){
		tree[node].push_back(vec[l-1]);
		return ;
	}
	int mid = (r + l) / 2;
	build(2*node, l, mid);
	build(2*node+1, mid+1, r);
	
	tree[node].resize(sz(tree[2*node]) + sz(tree[2*node+1]));

	merge(tree[2*node].begin(), tree[2*node].end(), tree[2*node+1].begin(), tree[2*node+1].end(), tree[node].begin());

}

int query(int l, int r, int k, int node = 1, int start = 1, int end = n){
	// cout << l << " - " << r << " - " << k << endl;
	if(end < l or start > r) return 0;
	if(l <= start and end <= r){
		return lower_bound(tree[node].begin(), tree[node].end(), k) - tree[node].begin();
	}
	int mid = (start + end) / 2;
	return query(l, r, k, 2*node, start, mid) + query(l, r, k, 2*node+1, mid+1, end);
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> m;

  for(int i=0;i<n;i++) {
    int a;
    cin >> a;
    vec.push_back(a);
  }

  build();

  for(int i=0;i<m;i++) {
    int a, b, c;
    cin >> a >> b >> c;
    // vec2.push_back({a,{b, c}});
    if(vec[a-1] >= b) {
      cout << 0 << endl;
      continue;
    }
    cout << (c) - query(a+1, a+c, b) << endl;
    
  }

  // for(auto i : vec) cout << i << " ";
  // cout << endl;

  //Numero de elementos menores que K
  // cout << query(1, 5, 3) << endl;
  // (c-a) - (a+1, a+c, b)
  // cout << query(2, 5, 3) << endl;
  // cout << query(2, 5, 6) << endl;

  

  return 0;
}