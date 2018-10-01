#include <iostream>
#include <vector>
#include <queue>
#include <set>
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

struct pairhash {
public:
	size_t operator()(const pair<int, pair<int, pair<long long, long long>>> &x) const {
		return x.first + x.second.first * 100007 + x.second.second.first * 10000007 + x.second.second.second * 117;
	}
};

vector< pair<long long, int>> boxes;
vector< pair<long long, int>> toys;
unordered_map<pair<int, pair<int, pair<long long, long long>>>, long long, pairhash> dp;
int N, M;

long long countDP(int box, int toy, long long curBox, long long curToy) {
	if (box == N || toy == M) return 0;

	auto it = dp.find(make_pair(box, make_pair(toy, make_pair(curBox, curToy))));
	if (it != dp.end()) {
		return it->second;
	}

	// otherwise we combine
	// if both are the same we take as much as possible
	if (boxes[box].second == toys[toy].second) { // they are of the same kind
		if (curBox == curToy) { // we take all of them
			long long result = curBox;
			if (box + 1 < N && toy + 1 < M)
				result += countDP(box + 1, toy + 1, boxes[box + 1].first, toys[toy + 1].first);
			dp[make_pair(box, make_pair(toy, make_pair(curBox, curToy)))] = result;
			return result;
		}
		else if (curBox < curToy) {
			long long result = curBox;
			if (box + 1 < N)
				result += countDP(box + 1, toy, boxes[box + 1].first, curToy - curBox);
			dp[make_pair(box, make_pair(toy, make_pair(curBox, curToy)))] = result;
			return result;
		}
		else { // curToy < curBox
			if (box == 2 && toy == 2 && curBox == 10 && curToy == 5) {
				//return 0;
			}
			long long result = curToy;
			if (toy + 1 < M)
				result += countDP(box, toy + 1, curBox - curToy, toys[toy + 1].first);
			dp[make_pair(box, make_pair(toy, make_pair(curBox, curToy)))] = result;
			return result;
		}
	}
	else {
		// we disgard all of first or second kind
		long long maximum = 0;
		if (box + 1 < N)
			maximum = countDP(box + 1, toy, boxes[box + 1].first, curToy);

		if (toy + 1 < M) {
			long long result = countDP(box, toy + 1, curBox, toys[toy + 1].first);
			if (result > maximum)
				maximum = result;
		}

		dp[make_pair(box, make_pair(toy, make_pair(curBox, curToy)))] = maximum;
		return maximum;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> N >> M;

		dp.clear();

		boxes = vector< pair<long long, int>>(N);
		toys = vector< pair<long long, int>>(M);

		for (int i = 0; i < N; i++) {
			long long a, A;
			cin >> a >> A;

			boxes[i] = make_pair(a, A);
		}

		for (int i = 0; i < M; i++) {
			long long b, B;
			cin >> b >> B;

			toys[i] = make_pair(b, B);
		}

		long long answer = countDP(0, 0, boxes[0].first, toys[0].first);

		/*for (auto it : dp) {
			cout << "(" << it.first.first << ", " << it.first.second.first << ", " << it.first.second.second.first << ", " << it.first.second.second.second<< "):" << it.second;
			cout << endl;
		}*/

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}