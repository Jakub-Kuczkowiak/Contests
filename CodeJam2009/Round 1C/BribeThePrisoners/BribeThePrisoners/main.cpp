#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string> // is needed in gcc?
#include <limits.h>
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int P, Q;
		cin >> P >> Q;

		vector<int> C(Q + 2);
		C[0] = 1;
		C[Q + 1] = P;
		for (int i = 1; i < Q + 1; i++) {
			cin >> C[i];
		}

		sort(C.begin(), C.end());

		int dp[101][101] = {};
		for (int i = 0; i < Q + 2 - 1; i++) {
			dp[i][i + 1] = 0;
		}

		for (int k = 2; k < Q + 2; k++) { // for a fixed length 'k'
			for (int i = 0; i + k< Q + 2; i++) { // for each field
				int min = INT_MAX;
				for (int j = i + 1; j < i + k; j++) { // we choose divide poitns
					if (dp[i][j] + dp[j][i + k] < min) {
						min = dp[i][j] + dp[j][i + k];
					}
				}

				if (k == Q + 1) {
					min += P - 1;
				}
				else {
					min = min + C[i + k] - C[i] - 2;
					if (i == 0 || i + k == Q + 1) min++; // the case for dummy interval (1 and P). can be used 0 and P + 1 and we do not need this line then
				}

				dp[i][i + k] = min;
			}
		}

		cout << "Case #" << t << ": " << dp[0][Q + 1] << endl;
	}

	return 0;
}