// const int MOD = 1000003;

// int howMany(vector<string> patterns, int k) {
// 	int n = patterns.size();
// 	int m = patterns[0].size();
// 	vector<vector<int>> dp(50, vector<int>(1 << n));
// 	for (int i = 0; i < m; i++) {
// 		for (char c = 'a'; c <= 'z'; c++) {
// 			int mask = 0;
// 			for (int j = 0; j < n; j++) {
// 				if (patterns[j][i] == c || patterns[j][i] == '?') { mask |= (1 << j); }
// 			}
// 			if (i == 0) {
// 				dp[i][mask]++;
// 			} else {
// 				for (int j = 0; j < (1 << n); j++) {
// 					dp[i][j & mask] = (dp[i][j & mask] + dp[i - 1][j]) % MOD;
// 				}
// 			}
// 		}
// 	}

// 	int ans = 0;
// 	for (int mask = 0; mask < (1 << n); mask++) {
// 		if (__builtin_popcount(mask) == k) { ans = (ans + dp[m - 1][mask]) % MOD; }
// 	}

// 	return ans;
// }