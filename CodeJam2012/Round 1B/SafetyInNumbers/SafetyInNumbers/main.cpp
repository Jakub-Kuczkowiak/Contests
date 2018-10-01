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

int N;
vector<int> s;
long long sum;

bool solve(int index, double p) {
	double rest = 1 - p;

	for (int i = 0; i < N; i++) {
		if (i == index) continue;

		double needed = max(0.0, (s[index] - s[i] + sum * p) / (double)sum);
		if (needed > rest) {
			return true;
		}
		
		rest = rest - needed;
	}

	return false;
}

double binary_answer(int index, double low, double high, int iterations) {
	for (int i = 0; i < iterations; i++) {
		double mid = (high + low) / 2.0;
		if (solve(index, mid)) high = mid; else low = mid;
	}

	return high;
}

int main() {
	//ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> N;
		s = vector<int>(N);

		sum = 0;
		for (int i = 0; i < N; i++) {
			cin >> s[i];
			sum += s[i];
		}

		cout << "Case #" << t << ": ";

		for (int i = 0; i < N; i++) { // calculate answer for each player
			double answer = binary_answer(i, 0, 1, 100);
			printf("%.9f ", answer * 100);
		}

		cout << endl;
	}

	return 0;
}