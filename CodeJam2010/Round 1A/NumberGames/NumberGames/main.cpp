#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h> // INT_MAX
#include <string> // is needed in g++?
#include <math.h> // pow in g++
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int A1, A2, B1, B2;
		cin >> A1 >> A2 >> B1 >> B2;

		double fi = (1 + pow(5, 1 / 2.)) / 2;
		long long count = 0;
		for (int i = B1; i <= B2; i++) {
			// count how many A's there are that are bigger than A >= FI*B
			int lowerBound = ceil(i * fi);
			if (lowerBound > A2) continue;
			lowerBound = max(lowerBound, A1);

			count += (A2 - lowerBound + 1);
		}

		swap(A1, B1);
		swap(A2, B2);

		for (int i = B1; i <= B2; i++) {
			// count how many A's there are that are bigger than A >= FI*B
			int lowerBound = ceil(i * fi);
			if (lowerBound > A2) continue;
			lowerBound = max(lowerBound, A1);

			count += (A2 - lowerBound + 1);
		}

		cout << "Case #" << t << ": " << count << endl;
	}

	return 0;
}