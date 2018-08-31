#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h> // INT_MAX
#include <string> // is needed in gcc?
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int D, I, M, N;
		cin >> D >> I >> M >> N;

		long long Array[101] = {};
		for (int i = 0; i < N; i++) {
			cin >> Array[i];
		}

		long long dp[101][257] = {};
		// delete first element
		dp[0][256] = D;

		for (int j = 0; j <= 255; j++) { 
			// modify to j
			dp[0][j] = abs(j - Array[0]);
		}

		// we do not want to insert anything for first element/

		for (int i = 1; i < N; i++) {
			// for each new pixel coming
			// delete
			long long min = LONG_MAX;
			for (int j = 0; j <= 256; j++) {
				if (dp[i - 1][j] < min) {
					min = dp[i - 1][j];
				}
			}

			dp[i][256] = min + D;

			// fix value, change this pixel to this value
			for (int j = 0; j <= 255; j++) {
				// this is either removing this value and using last prefix
				long long minimum = dp[i - 1][j] + D;

				// or we now go from any of the previous values to value j
				long long switchThis = abs(Array[i] - j);
				for (int k = 0; k <= 255; k++) {
					if (M == 0) {
						// we cannot insert
						if (j != k) {
							continue;
						}
						else {
							if (switchThis + dp[i - 1][k] < minimum) {
								minimum = switchThis + dp[i - 1][k];
							}
						}
					}
					else {
						long long insertCost = (abs(k - j) + M - 1) / M - 1;
						insertCost *= I;
						insertCost = max(0, (int)insertCost);

						if (insertCost + switchThis + dp[i - 1][k] < minimum) {
							minimum = insertCost + switchThis + dp[i - 1][k];
						}
					}
				}

				dp[i][j] = minimum;
			}
		}

		// find min
		int minimum = LONG_MAX;
		for (int j = 0; j <= 256; j++) {
			if (dp[N - 1][j] < minimum) {
				minimum = dp[N - 1][j];
			}
		}

		cout << "Case #" << t << ": " << minimum << endl;
	}

	return 0;
}