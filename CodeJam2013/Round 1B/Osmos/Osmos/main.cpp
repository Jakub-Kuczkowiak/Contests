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

long long A, N;
vector<long long> osmos;

struct pairhash {
public:
	template <typename T, typename U>
	std::size_t operator()(const std::pair<T, U> &x) const {
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};

unordered_map<pair<long long, int>, long long, pairhash> dp;

long long countDP(long long size, int index) {
	if (index == N) return 0;

	if (dp.find(make_pair(size, index)) != dp.end()) {
		return dp[make_pair(size, index)];
	}

	if (size > osmos[index]) {
		long long answer = countDP(size + osmos[index], index + 1);
		dp[make_pair(size, index)] = answer;
	}
	else { // we cannot eat more so we two choices
		// first choice: add (size - 1)
		long long minimum = LLONG_MAX;
		if (size < 1000001 && size > 1) {
			minimum = countDP(2 * size - 1, index) + 1;
		}
		
		// second choice: remove
		long long result = countDP(size, index + 1) + 1;
		if (result < minimum)
			minimum = result;

		dp[make_pair(size, index)] = minimum;
		return minimum;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	dp = unordered_map<pair<long long, int>, long long, pairhash>();

	for (int t = 1; t <= T; t++) {
		cin >> A >> N;
		osmos = vector<long long>(N);

		dp.clear();

		for (int i = 0; i < N; i++) {
			cin >> osmos[i];
		}

		sort(osmos.begin(), osmos.end());

		long long answer = countDP(A, 0);

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}