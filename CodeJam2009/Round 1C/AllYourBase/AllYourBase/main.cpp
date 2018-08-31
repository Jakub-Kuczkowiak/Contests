#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string> // is needed in gcc?
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		string input;
		cin >> input;

		/*if (input.size() == 1) {
			cout << "Case #" << t << ": " << 0 << endl;
			continue;
		}*/

		unordered_map<char, int> transform;
		transform[input[0]] = 1;
		int lastDigit = 0;
		for (int i = 1; i < input.size(); i++) {
			if (transform.find(input[i]) == transform.end()) {
				transform[input[i]] = lastDigit;
				lastDigit++;
				if (lastDigit == 1) lastDigit = 2;
			}
		}

		// we now know the base
		int base = max(2, (int)transform.size());
		unsigned long long answer = 0;
		for (int i = 0; i < input.size(); i++) {
			answer = answer * base;
			answer = answer + transform[input[i]];
		}

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}