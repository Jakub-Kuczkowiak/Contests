#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <unordered_map>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int S;
		cin >> S;

		vector<string> engines(S);

		string dump;
		getline(cin, dump);

		unordered_map<string, vector<int>> enginePos;

		for (int i = 0; i < S; i++) {
			getline(cin, engines[i]);
			enginePos[engines[i]] = vector<int>();
		}

		int Q;
		cin >> Q;

		vector<string> queries(Q);

		getline(cin, dump);
		for (int i = 0; i < Q; i++) {
			getline(cin, queries[i]);
		}

		for (int i = 0; i < Q; i++) {
			enginePos[queries[i]].push_back(i);
		}

		// we choose initial engine
		string intialEngine;
		int latestOcc = -1;
		for (auto it = enginePos.begin(); it != enginePos.end(); it++) {
			if (it->second.size() == 0) {
				// this engine neever occurs so we choose it
				intialEngine = it->first;
				latestOcc = -1;
				break;
			}

			if (it->second[0] > latestOcc) {
				latestOcc = it->second[0];
				intialEngine = it->first;
			}
		}

		if (latestOcc == -1) {
			cout << "Case " << "#" << t << ": 0" << endl;
			continue;
		}

		// we have choosen initial engine, now we continue like this.
		int answer = 0;
		string latestEngine = intialEngine;
		for (int i = latestOcc; i < Q;) {
			// we look for the engine that is as late as possible
			int latest = -1;

			// take a look at each engine in the list
			string newLatestEngine;
			for (auto it = enginePos.begin(); it != enginePos.end(); it++) {
				if (it->first == latestEngine) continue;

				// look for the occurance of value higher than given index
				int l = 0;
				int r = it->second.size() - 1;

				int result = INT_MAX - 1;
				while (l <= r) {
					int m = l + (r - l + 1) / 2;
					if (it->second[m] >= i + 1) {
						r = m - 1;
						result = it->second[m];
					}
					else {
						l = m + 1;
					}
				}

				if (result > latest) {
					latest = result;
					newLatestEngine = it->first;
				}
			}

			latestEngine = newLatestEngine;

			i = latest;
			answer++;
		}

		cout << "Case " << "#" << t << ": " << answer << endl;
	}

	return 0;
}