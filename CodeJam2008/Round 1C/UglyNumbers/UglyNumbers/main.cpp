#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string> // is needed in gcc?
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
//#include <bits/stdc++.h>

using namespace std;

unsigned long long dp[41][210] = {};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		string s;
		cin >> s;

		int n = s.size();

		memset(dp, 0, sizeof(dp));

		for (int i = 0; i < 210; i++) {
			dp[n - 1][i] = (s[n - 1] - '0' == i);
		}

		for (int i = n - 2; i >= 0; i--) {
			// we choose number now
			int current = 0;
			for (int k = i; k < n - 1; k++) {
				current = (current * 10 + s[k] - '0') % 210;

				for (int j = 0; j < 210; j++) {
					int plusIndex = j - current;
					if (plusIndex < 0) plusIndex += 210;
					int minusIndex = current - j;
					if (minusIndex < 0) minusIndex += 210;

					dp[i][j] += dp[k + 1][plusIndex];
					dp[i][j] += dp[k + 1][minusIndex];
				}
			}

			current = (current * 10 + s[n - 1] - '0') % 210;

			dp[i][current]++;
		}

		unsigned long long result = 0;
		for (int i = 0; i < 210; i++) {
			if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0) {
				result += dp[0][i];
			}
		}

		cout << "Case #" << t << ": " << result << endl;
	}

	return 0;
}