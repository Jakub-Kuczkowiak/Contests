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

typedef pair<int, pair<bool, pair<bool, bool>>> T;

class Compare {
public:
	bool operator() (T a, T b) const {
		if (a.first == b.first) {
			if (a.second.first == b.second.first) {
				if (a.second.second.first == b.second.second.first) {
					return a.second.second.second < b.second.second.second;
				}
				else {
					return a.second.second.first < b.second.second.first;
				}
			}
			else {
				return a.second.first < b.second.first;
			}
		}
		else {
			return a.first < b.first;
		}
	}
}compare;

int A, B, K;
map<pair<int, pair<bool, pair<bool, bool>>>, long long, Compare> dp;

int findTopLeftBit(int number) {
	for (int i = 30; i >= 0; i--) {
		int bit = number & (1 << i);
		if (bit != 0) {
			return i;
		}
	}

	return -1;
}

bool getBit(int number, int bit) {
	return ((1 << bit) & number) != 0;
}

long long countDP(int index, bool a, bool b, bool k) {
	auto it = dp.find(make_pair(index, make_pair(a, make_pair(b, k))));
	if (it != dp.end()) {
		return it->second;
	}

	int bitA = getBit(A, index);
	int bitB = getBit(B, index);
	int bitK = getBit(K, index);

	// base case
	if (index == 0) {
		// (a = 0 i b = 0) v
		long long result = 1;

		// two cases: k = 0 or k = 1
		// k = 0
		// (a = 1 i b = 0) v (a = 0 i b = 1)
		long long pA = (a || bitA ? 1 : 0);
		long long pB = (b || bitB ? 1 : 0);

		result += pA;
		result += pB;

		// k = 1
		// (a == 1 i b == 1)
		if (k || bitK)
			result += (pA * pB);

		return result;
	}

	// we set bit for number K
	// case: K = 0
	long long result = 0;

	// a = 0, b = 0
	result += countDP(index - 1, a | bitA, b | bitB, k | bitK);

	// a = 1, b = 0
	if (a || bitA) {
		result += countDP(index - 1, a, b | bitB, k | bitK);
	}

	// a = 0, b = 1
	if (b || bitB) {
		result += countDP(index - 1, a | bitA, b, k | bitK);
	}

	// case: K = 1
	if ((bitK || k) && (a || bitA) && (b || bitB)) { // only then we can set 1 here
		// both bits a and b must be also one
		result += countDP(index - 1, a, b, k);
	}

	dp[make_pair(index, make_pair(a, make_pair(b, k)))] = result;
	return result;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> A >> B >> K;
		A--; B--; K--;

		if (A == 0 && B == 0 && K == 0) {
			cout << "Case #" << t << ": " << 1 << endl;
			continue;
		}

		dp.clear();

		// find topleft one
		int index = findTopLeftBit(A);
		index = max(index, findTopLeftBit(B));
		index = max(index, findTopLeftBit(K));

		long long answer = countDP(index, false, false, false);

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}