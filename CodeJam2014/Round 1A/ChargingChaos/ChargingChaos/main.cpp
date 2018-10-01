#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <limits.h> // INT_MAX
#include <math.h> // pow in g++
#include <string> // is needed in gcc?
#include <cstring> // one of string can be removed; cstring contains memset
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define REP(i, n) for((i)=0; (i)<(int)(n); (i)++)
#define foreach(c, itr) for(__typeof((c).begin()) itr = (c).begin(); itr != (c).end(); itr++)

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N, L;
		cin >> N >> L;

		vector<string> outlets(N);
		for (int i = 0; i < N; i++) {
			cin >> outlets[i];
		}

		vector<string> devices(N);
		for (int i = 0; i < N; i++) {
			cin >> devices[i];
		}

		sort(devices.begin(), devices.end());

		// generate masks
		// first device must be matched with some outlet
		vector<string> masks;
		for (int i = 0; i < N; i++) {
			string mask;
			for (int j = 0; j < L; j++) { // for each bit
				mask += ((devices[0][j] - '0') ^ (outlets[i][j] - '0')) + '0';
			}

			masks.push_back(mask);
		}

		// for each mask see if it allows us to match devices
		long long answer = INT_MAX;
		for (int i = 0; i < masks.size(); i++) {
			// change all outlets
			vector<string> outletsCopy(outlets);

			for (int j = 0; j < N; j++) { // choose outlet
				for (int k = 0; k < L; k++) { // loop through outlet's letters
					outletsCopy[j][k] = ((outletsCopy[j][k] - '0') ^ (masks[i][k] - '0')) + '0';
				}
			}

			sort(outletsCopy.begin(), outletsCopy.end());
			
			// compare all
			int ones = 0;
			for (int j = 0; j < L; j++) {
				ones += (masks[i][j] == '1');
			}

			long long minimum = ones;
			for (int i = 0; i < N; i++) {
				if (outletsCopy[i] != devices[i]) {
					minimum = INT_MAX;
					break;
				}
			}

			if (minimum < answer)
				answer = minimum;
		}

		cout << "Case #" << t << ": ";
		if (answer == INT_MAX)
			cout << "NOT POSSIBLE" << endl;
		else
			cout << answer << endl;
	}

	return 0;
}