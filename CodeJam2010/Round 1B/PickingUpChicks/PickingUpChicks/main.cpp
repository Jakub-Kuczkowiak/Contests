#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h> // INT_MAX
#include <math.h> // pow in g++
#include <string> // is needed in gcc?
#include <cstring> // one of string can be removed; cstring contains memset
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		double N, K, B, Time;
		cin >> N >> K >> B >> Time;

		vector<long long> X(N);
		for (int i = 0; i < N; i++) {
			cin >> X[i];
		}

		vector<long long> V(N);
		for (int i = 0; i < N; i++) {
			cin >> V[i];
		}

		// find first that does not pass on time
		int swaps = 0;
		int i;
		for (i = N - 1; i >= 0; i--) {
			double time = (B - X[i]) / V[i];
			if (time <= Time) {
				K--;
			}
			else {
				break;
			}
		}

		if (K <= 0) {
			cout << "Case #" << t << ": " << swaps << endl;
			continue;
		}

		// i points to the first that doesn't get there on time and the only we need to care about
		int lastElementSwaps = 1;
		for (int j = i - 1; j >= 0; j--) {
			double time = (B - X[j]) / V[j];
			if (time > Time) {
				lastElementSwaps++;
				continue;
			}
			else {
				swaps += lastElementSwaps;
				K--;
				if (K == 0) break;
			}
		}

		if (K <= 0) {
			cout << "Case #" << t << ": " << swaps << endl;
		}
		else {
			cout << "Case #" << t << ": IMPOSSIBLE"<< endl;
		}
	}

	return 0;
}