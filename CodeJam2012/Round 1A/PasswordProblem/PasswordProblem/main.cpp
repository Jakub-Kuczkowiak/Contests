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

int main() {
	//ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int A, B;
		cin >> A >> B;

		vector<double> p(A);
		for (int i = 0; i < A; i++) {
			cin >> p[i];
		}

		double minExpected = B + 2; // hit enter right away

		// hit backspace 'i' times
		double probability = 1;
		for (int i = A; i >= 0; i--) {
			double expected = probability * (2 * i + B - A + 1) + (1 - probability) * (2 * i + B - A + 1 + B + 1);
			if (expected < minExpected)
				minExpected = expected;

			probability *= p[A - i];
		}

		cout << "Case #" << t << ": ";
		printf("%.9f\n", minExpected);
	}

	return 0;
}