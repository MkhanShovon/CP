#include <bits/stdc++.h>
using namespace std;

int main() {
	ifstream in("cowpatibility.in");
	int n;
	in >> n;

	map<vector<int>, int> subsets;
	for (int i = 1; i <= n; i++) {
		vector<int> v(5);
		for (int &num : v) { in >> num; }
		sort(v.begin(), v.end());
		for (int mask = 1; mask < (1 << 5); mask++) {
			vector<int> subset;
			for (int i = 0; i < 5; i++) {
				if ((1 << i) & mask) { subset.push_back(v[i]); }
			}
			subsets[subset]++;
		}
	}

	long long ans = (long long)n * (n - 1) / 2;
	for (const auto &[subset, freq] : subsets) {
		ans -= ((int)subset.size() % 2 == 1 ? 1LL : -1LL) * freq * (freq - 1) / 2;
	}

	ofstream("cowpatibility.out") << ans << endl;
}