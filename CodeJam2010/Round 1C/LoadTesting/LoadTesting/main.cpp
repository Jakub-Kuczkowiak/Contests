#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h> // INT_MAX
#include <math.h> // pow in g++
#include <string> // is needed in gcc?
#include <cstring> // one of string can be removed; cstring contains memset
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define PRIME_MOD (1000000007) // should add to library

using namespace std;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		unsigned long long L, P, C;
		cin >> L >> P >> C;

		// one test LC^2 >= R; two tests LC^4 >= R; x tests LC^(2^X) >= R
		int x;
		unsigned long long bigC = C;
		for (x = 0; x <= 100; x++) {
			unsigned long long iloczyn = L * bigC;
			bigC = bigC * bigC;
			if (iloczyn >= P) {
				break;
			}
		}

		cout << "Case #" << t << ": " << x << endl;
	}

	return 0;
}