// C++ Program to find the Sum
// of GCD of all integers up to N
// with N itself

#include <bits/stdc++.h>
using namespace std;

// Function to Find Sum of
// GCD of each numbers
int getCount(int d, int n)
{

    int no = n / d;

    int result = no;

    // Consider all prime factors
    // of no. and subtract their
    // multiples from result
    for (int p = 2; p * p <= no; ++p) {

        // Check if p is a prime factor
        if (no % p == 0) {

            // If yes, then update no
            // and result
            while (no % p == 0)
                no /= p;
            result -= result / p;
        }
    }

    // If no has a prime factor greater
    // than sqrt(n) then at-most one such
    // prime factor exists
    if (no > 1)
        result -= result / no;

    // Return the result
    return result;
}

// Finding GCD of pairs
int sumOfGCDofPairs(int n)
{
    int res = 0;

    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            // Calculate the divisors
            int d1 = i;
            int d2 = n / i;

            // Return count of numbers
            // from 1 to N with GCD d with N
            res += d1 * getCount(d1, n);

            // Check if d1 and d2 are
            // equal then skip this
            if (d1 != d2)
                res += d2 * getCount(d2, n);
        }
    }

    return res;
}

// Driver code
int main()
{
    int n = 12;

    cout << sumOfGCDofPairs(n);

    return 0;
}