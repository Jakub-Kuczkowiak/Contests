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

struct tuplehash {
public:
	template <typename T, typename U, typename W>
	std::size_t operator()(const std::tuple<T, U, W> &x) const {
		return std::hash<T>()(get<0>(x)) ^ std::hash<U>()(get<1>(x)) ^ std::hash<W>()(get<2>(x));
	}
};

int N;
vector<long long> v;
unordered_map<long long, int> m;
unordered_map<tuple<long long, long long, int>, bool, tuplehash> dp;

int countDP(long long A, long long B, int index) {
	if (index == N) return 0;

	if (dp.find(make_tuple(A, B, index)) != dp.end()) {
		return dp[make_tuple(A, B, index)];
	}

	if (A == 0 && B == 0) { // base case where we must put something into backet
		bool m = countDP(A, B, index + 1);
		if (m) {
			dp[make_tuple(A, B, index)] = m;
			return m;
		}
		m = countDP(A + v[index], B, index + 1);
		if (m) {
			dp[make_tuple(A, B, index)] = m;
			return m;
		}
		m = countDP(A, B + v[index], index + 1);
		dp[make_tuple(A, B, index)] = m;
		return m;
	}
	else {
		// we must see if we can put something
		// see if we can add something to A to get B
		auto it = m.find(abs(B - A));
		if (it != m.end()) {
			if (it->second >= index) {
				return 1;
			}
		}

		bool m = countDP(A, B, index + 1);
		if (m) {
			dp[make_tuple(A, B, index)] = m;
			return m;
		}
		m = countDP(A + v[index], B, index + 1);
		if (m) {
			dp[make_tuple(A, B, index)] = m;
			return m;
		}
		m = countDP(A, B + v[index], index + 1);
		dp[make_tuple(A, B, index)] = m;
		return m;
	}
}

int main() {
	//ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> N;
		v = vector<long long>(N);

		/*
		Large dataset
		*/
		for (int i = 0; i < N; i++) {
			cin >> v[i];
		}

		// choose fixed number of times, like 10^7 the subset
		for (int i = 0; i < 1000000; i++) {
			map<int, vector<int>> dp;
			for (int j = 0; j < 6; j++) {

			}
		}

		m.clear();

		for (int i = 0; i < N; i++) {
			cin >> v[i];
			m[v[i]] = i;
		}
		dp.clear();

		int answer = countDP(0, 0, 0);
		vector<long long> setA, setB;
		if (answer) {
			int index = 0;
			long long A = 0;
			long long B = 0;
			while (true) {
				if (countDP(A, B, index + 1)) {
					index++;
					continue;
				}
				else if (countDP(A + v[index], B, index + 1)) {
					A += v[index];
					setA.push_back(v[index]);
				}
				else if (countDP(A, B + v[index], index + 1)) {
					B += v[index];
					setB.push_back(v[index]);
				}
				else {
					auto it = m.find(abs(B - A));
					if (A < B) {
						setA.push_back(it->first);
					}
					else {
						setB.push_back(it->first);
					}

					break;
				}

				index++;
			}

			
		}

		cout << "Case #" << t << ": " << endl;
		for (int i = 0; i < setA.size(); i++) {
			cout << setA[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < setB.size(); i++) {
			cout << setB[i] << " ";
		}
		cout << endl;
	}

	return 0;
}