#include <iostream>
#include <vector>
#include <list>

using namespace std;

// g++ -std=c++11

const unsigned MAXN = 1000;
vector<int> adj[MAXN];
int N, M;

/*** lettura da input ***/

void leggiGrafo(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	cin >> N >> M;

	for (int i=0; i<M; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void stampaGrafo(){
	cout << "liste di adiacenza:" << endl;
	for (int u=0; u<N; u++) {
		cout << u << ": ";
		for (auto x: adj[u]){
			cout << x << " ";
		}
		cout << endl;
	} 
}

void stampa_queue(list<int> coda){
	for(auto x: coda){
		cout << x << " | ";
	}
	cout << endl;
}

void stampa_visitato(bool visitato[MAXN]){
	for (int i=0; i<MAXN;i++) {
		cout << "\t| " << i << "|| " << visitato[i] << endl;
	}
}


/*** visita BFS (con coda) ***/

int BFS_preliminar(){
	bool visitato[MAXN];
	for (int i = 0; i < N; i++)
		visitato[i] = false;

	list<int> coda;
	visitato[0] = true;
	coda.push_back(0);

	while(!coda.empty()) {
		int u = coda.front();
		coda.pop_front();

		for (auto x: adj[u]) {
			if(!visitato[x]) {
				visitato[x] = true;
				coda.push_back(x);
			}
		}
	}
	//stampa_visitato(visitato);
	for (int x=0; x<N;x++) {
		if(visitato[x]==false)
			return 1;
	}
	return 0;
}

int BFS(int u){
	int visitato[MAXN];
	for(int x = 0; x < N; x++) {
		visitato[x] = false;
	}
	
	list<int> coda;
	visitato[u] = true;
	coda.push_back(u);
	coda.push_back(-1);
	int level=0;

	while(coda.size()>1) {
		u = coda.front();
		coda.pop_front();

		if(u==-1){
			coda.push_back(-1);
			level++;
		}
		else{
			for (auto x: adj[u]) {
				if (!visitato[x]) {
					visitato[x] = true;
					coda.push_back(x);
				}
			}
		}
	}
	return level;
}

/* Main */

int main(){
	leggiGrafo();
	//stampaGrafo();

	if(BFS_preliminar()){
		cout << -1 << endl;
		return 0;
	}

	int _max=0;
	int temp=0;
	for(int i = 0; i < N; ++i) {
		temp = BFS(i);
		if (temp==-1) {
			_max = -1;
			break;
		}
		_max = max(temp, _max);
	}
	cout << _max << endl;
	return 0;
}
