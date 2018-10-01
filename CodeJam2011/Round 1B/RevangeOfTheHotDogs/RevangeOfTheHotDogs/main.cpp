#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <limits.h> // INT_MAX
#include <math.h> // pow in g++
#include <string> // is needed in gcc?
#include <cstring> // one of string can be removed; cstring contains memset
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

using namespace std;

long long C, D;
multiset<long long> hotdogs;

bool solve(long long time) {
	// we try to move them as left as possible; greedy strategy works;
	// assume there is optimal in which we didn't move the topleft as left as we could
	// now move him as much as we could and we get solution which is still valid
	long long left = LLONG_MIN;
	for (auto it = hotdogs.begin(); it != hotdogs.end(); it++) {
		// newleft
		long long atLeast = left + D; // here we must stand at least
		if (*it >= atLeast) {
			// we move him as much as left as possible
			left = max(*it - time, atLeast);
		}
		else {
			// we must move him right
			if (*it + time >= atLeast) { // we managed to survive so we move him to atleast
				left = atLeast;
			}
			else {
				return false;
			}
		}
	}

	return true;
}

// case: no, no, no, yes, yes, yes
long long binary_answer(long long l, long long r, bool (*solve)(long long)) {
	if (l > r) return -1; // base case; no found element

	long long m = l + (r - l) / 2;

	if (solve(m)) {
		long long answer = binary_answer(l, m - 1, solve);
		if (answer != -1) {
			return answer;
		}
		else {
			return m;
		}
	}
	else {
		return binary_answer(m + 1, r, solve);
	}
}

int main() {
	//ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> C;
		cin >> D;
		D *= 2;

		hotdogs.clear();

		for (int i = 0; i < C; i++) {
			int P, V;
			cin >> P >> V;

			for (int j = 0; j < V; j++) {
				hotdogs.insert(2 * P);
			}
		}

		// binary search
		long long time = binary_answer(0, D * 1000000, solve);
		double dTime = (double)time / (double)2.0;

		cout << "Case #" << t << ": ";
		printf("%.1f\n", dTime);
	}

	return 0;
}