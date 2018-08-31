#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

pair<short, char> result(pair<short, char> c1, pair<short, char> c2) {
	pair<short, char> result;
	result.first = c1.first ^ c2.first;

	if (c1.second == '1') {
		result.second = c2.second;
	}
	else if (c1.second == 'i') {
		if (c2.second == '1') {
			result.second = 'i';
		}
		else if (c2.second == 'i') {
			result.second = '1';
			result.first ^= 1;
		}
		else if (c2.second == 'j') {
			result.second = 'k';
		}
		else if (c2.second == 'k') {
			result.second = 'j';
			result.first ^= 1;
		}
	}
	else if (c1.second == 'j') {
		if (c2.second == '1') {
			result.second = 'j';
		}
		else if (c2.second == 'i') {
			result.second = 'k';
			result.first ^= 1;
		}
		else if (c2.second == 'j') {
			result.second = '1';
			result.first ^= 1;
		}
		else if (c2.second == 'k') {
			result.second = 'i';
		}
	}
	else {
		if (c2.second == '1') {
			result.second = 'k';
		}
		else if (c2.second == 'i') {
			result.second = 'j';
		}
		else if (c2.second == 'j') {
			result.second = 'i';
			result.first ^= 1;
		}
		else if (c2.second == 'k') {
			result.second = '1';
			result.first ^= 1;
		}
	}

	return result;
}


pair<short, char> prefix[10000 * 24 + 2] = {};
pair<short, char> suffix[10000 * 24 + 2] = {};
pair<bool, bool> prefixIJ[10000 * 24 + 2] = {}; // pierwwszy bool dla znaku 0, drugi dla znaku 1

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int L, X;
		cin >> L >> X;

		if (X >= 20) {
			int remainder = X % 4;
			X = 16 + remainder;
		}

		string s;
		cin >> s;

		string newS = s;
		//string newS(L * X, '\0');

		/*for (int i = 0; i < L * X; i++) {
			newS[i] = s[i % L];
		}*/

		for (int i = 0; i < X - 1; i++) {
			newS += s;
		}

		s = newS;

		 // multiply s * min(x, 20).

		// prefix dla i
		prefix[0] = pair<short, char>(0, s[0]);
		for (int i = 1; i < L*X; i++) {
			prefix[i] = result(prefix[i - 1], pair<short, char>(0, s[i]));
		}

		// suffix dla k
		suffix[L*X - 1] = pair<short, char>(0, s[L*X - 1]);
		for (int i = L * X - 2; i >= 0; i--) {
			suffix[i] = result(pair<short, char>(0, s[i]), suffix[i + 1]);
		}

		// prefix dla ij
		prefixIJ[0].first = false;
		prefixIJ[0].second = false;
		for (int i = 1; i < L * X; i++) {
			prefixIJ[i].first = false;
			prefixIJ[i].second = false;

			pair<short, char> middle;
			middle.second = s[i];
			middle.first = 0;
			for (int j = i - 1; j >= 0; j--) {
				if (prefix[j].second == 'i' && middle.second == 'j') {
					if ((prefix[j].first ^ middle.first) == 0) {
						prefixIJ[i].first = true;
					}
					else {
						prefixIJ[i].second = true;
					}
				}

				middle = result(pair<short, char>(0, s[j]), middle);
			}
		}

		// we look up answer for each prefix IJ
		bool bFound = false;
		for (int i = 1; i < L * X - 1; i++) {
			if (suffix[i + 1].second != 'k') continue;

			// suffix is fine, we check for prefixIJ and minuses
			if (prefixIJ[i].first == true && suffix[i + 1].first == 0) {
				bFound = true;
				break;
			}

			if (prefixIJ[i].second == true && suffix[i + 1].first == 1) {
				bFound = true;
				break;
			}
		}

		if (bFound) {
			cout << "Case #" << t << ": YES" << endl;
		}
		else {
			cout << "Case #" << t << ": NO" << endl;
		}
	}

	return 0;
}