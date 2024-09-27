#include <bits/stdc++.h>

using namespace std;


void generate_test_cases(int max_total_n) {
    int t=1;
    vector<pair<int, string>> cases;
    int total_n = 0;

    for (int i = 0; i < t; i++) {
        // Randomly decide the length of the binary string (1 <= n <= 10^5).
        int n = rand() % min(100000, max_total_n - total_n) + 1;

        // Generate a random binary string of length n.
        string binary_string;
        for (int j = 0; j < n; j++) {
            binary_string += (rand() % 2 == 0) ? '0' : '1';
        }

        // Store the test case (n and binary string).
        cases.push_back({n, binary_string});

        total_n += n;
        if (total_n >= max_total_n) break; // Stop if total length exceeds max allowed
    }

    // Output the generated test cases
    cout << cases.size() << endl;
    for (const auto &test_case : cases) {
        cout << test_case.first << endl; // Length of the string
        cout << test_case.second << endl; // The binary string
    }
}
int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    generate_test_cases(100000);
}