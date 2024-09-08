#include <bits/stdc++.h>
using namespace std;

vector<bool> vstd;
vector<vector<int>> adjList;

int scheduleBroadcast(int v){
	vstd[v] = true;
	int time = 0;
	priority_queue<pair<int,int>> pq;
	for (auto u : adjList[v]) {
		if( vstd[u] ) continue;
		pq.push( {scheduleBroadcast(u),u} );
	}
	int t = 1;
	while( !pq.empty() ){
		auto value = pq.top(); pq.pop();
		time = max(time, value.first + t);
		t++;
	}
	return time;
}

int main(int argc, char const *argv[]) {
	
	int qtVertices;
	int root;
	int u, v;

	cin >> qtVertices >> root;

	adjList.resize(qtVertices);
	vstd.resize(qtVertices, false);

	for( int i = 0 ; i < qtVertices - 1 ; ++i ){
		cin >> u >> v;
		adjList[u-1].push_back(v-1);
		adjList[v-1].push_back(u-1);
	}

	cout << ((qtVertices == 1) ? 0 : scheduleBroadcast(root - 1)) << endl;

	return 0;
}