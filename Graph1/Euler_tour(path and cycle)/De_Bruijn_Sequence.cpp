#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	if (n == 1) {
		cout << "10" << endl;
		return 0;
	}

	vector<vector<int>> adj(1 << (n - 1));
	for (int node = 0; node < (1 << (n - 1)); node++) {
		int son = (node << 1) % (1 << (n - 1));
		adj[node].push_back(son);
		adj[node].push_back(son | 1);
	}

	stack<int> todo;
	todo.push(0);
	vector<int> path;
	while (!todo.empty()) {
		int node = todo.top();
		if (!adj[node].empty()) {
			todo.push(adj[node].back());
			adj[node].pop_back();
		} else {
			path.push_back(node & 1);
			todo.pop();
		}
	}
	for (int i = 0; i < n - 2; i++) { path.push_back(0); }

	for (int digit : path) { cout << digit; }
	cout << endl;
}