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

__inline bool isConsonant(char c) {
	return !(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		string s;
		cin >> s;

		int n;
		cin >> n;

		// algorithm with moving window
		int lastIndex = 0;
		int consecutiveConsonants = 0;
		long long answer = 0;
		int left = 0;

		for (int i = 0; i < n; i++) {
			if (isConsonant(s[i])) {
				consecutiveConsonants++;
			}
			else {
				consecutiveConsonants = 0;
			}
		}

		if (consecutiveConsonants == n) {
			// we add to answer
			answer += (s.size() - 1 - n + 1 + 1);
			lastIndex = 1;
		}

		for (int i = n; i < s.size(); i++) { // i points to the right of window
			if (isConsonant(s[i])) {
				consecutiveConsonants++;
			}
			else {
				consecutiveConsonants = 0;
			}

			consecutiveConsonants = min(consecutiveConsonants, n);

			left++;

			if (consecutiveConsonants == n) {
				// we add to answer
				answer += (left - lastIndex + 1) * (s.size() - 1 - i + 1);
				lastIndex = left + 1;
			}
		}

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}