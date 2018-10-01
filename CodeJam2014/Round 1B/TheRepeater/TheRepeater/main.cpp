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

class Compare {
public:
	bool operator() (pair<char, int> a, pair<char, int> b) {
		return a.second < b.second;
	}
}compare;

int main() {
	//ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;

		vector < vector< pair<char, int>>> masks = vector < vector< pair<char, int>>>(N);
		bool bSuccess = true;

		for (int i = 0; i < N; i++) {
			string s;
			cin >> s;

			masks[i] = vector<pair<char, int>>();
			
			int same = 1;
			for (int j = 1; j < s.size(); j++) {
				if (s[j] == s[j - 1]) {
					same++;
				}
				else {
					masks[i].push_back(make_pair(s[j - 1], same));
					same = 1;
				}
			}

			masks[i].push_back(make_pair(s[s.size() - 1], same));
		}

		for (int i = 1; i < N; i++) {
			if (masks[i].size() != masks[i - 1].size()) {
				// lost
				bSuccess = false;
				break;
			}
		}

		if (!bSuccess) {
			cout << "Case #" << t << ": Fegla Won" << endl;
			continue;
		}

		long long changes = 0;
		// loop through each mask

		for (int i = 0; i < masks[0].size(); i++) { // for each letter, go through all masks
			vector<long long> values(N);
			values[0] = masks[0][i].second;

			// check if same letter for all
			for (int j = 1; j < N; j++) {
				if (masks[j][i].first != masks[0][i].first) {
					bSuccess = false;
					break;
				}

				values[j] = masks[j][i].second;
			}
			
			sort(values.begin(), values.end());
			
			if (!bSuccess) break;

			long long prefixSum = 0;
			long long suffixSum = 0;
			for (int j = 1; j < N; j++) {
				suffixSum += values[j];
			}

			long long minChanges = LLONG_MAX;
			for (int j = 0; j < N - 1; j++) {
				long long localChanges = suffixSum - prefixSum + (2*j - N + 1) * values[j];
				if (localChanges < minChanges)
					minChanges = localChanges;

				prefixSum += values[j];
				suffixSum -= values[j + 1];
			}

			long long lastChanges = suffixSum - prefixSum + (N - 1) * values[N - 1];
			if (lastChanges < minChanges)
				minChanges = lastChanges;

			changes += minChanges;
		}

		if (!bSuccess) {
			cout << "Case #" << t << ": Fegla Won" << endl;
			continue;
		}
		else {
			cout << "Case #" << t << ": " << changes << endl;
		}
	}

	return 0;
}