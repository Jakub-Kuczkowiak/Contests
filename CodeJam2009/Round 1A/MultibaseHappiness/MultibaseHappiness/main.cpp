#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string> // is needed in gcc?
#include <istream>
#include <sstream>  
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

const int LIMIT = 1000000000;


struct pairhash {
public:
	template <typename T, typename U>
	std::size_t operator()(const std::pair<T, U> &x) const
	{
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};

unordered_map<pair<int, int>, bool, pairhash> dp;

int convertTenToBase(int number, int base) {
	int value = number;
	string s;
	while (value > 0) {
		int digit = value % base;
		value /= base;
		s = (char)(digit + '0') + s;
	}

	int tenBaseValue = 0;
	for (int i = 0; i < s.size(); i++) {
		tenBaseValue = tenBaseValue * 10 + (s[i] - '0');
	}

	return tenBaseValue;
}

bool is_happy(int N, int base, unordered_set<int>& rec) {
	if (dp.find(make_pair(N, base)) != dp.end()) return dp.find(make_pair(N, base))->second;

	if (rec.find(N) != rec.end()) {
		dp[make_pair(N, base)] = 0;
		return false;
	}

	int NCopy = N;
	
	int square = 0;
	while (NCopy > 0) {
		int digit = NCopy % 10;
		square += digit * digit;
		NCopy /= 10;
	}

	square=  convertTenToBase(square, base);

	rec.insert(N);
	bool bResult = is_happy(square, base, rec);
	dp[make_pair(N, base)] = bResult;
	return bResult;
}

vector<string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);



	for (int i = 2; i <= 10; i++) {
		dp[make_pair(1, i)] = 1;
	}

	//for (int i = 2; i <= LIMIT; i++) {
	//	for (int j = 2; j <= 10; j++) {
	//		//int square = convertTenToBase(i, j);

	//		////if (i >= LIMIT - 1) {
	//		////	int NCopy = i;
	//		////	while (NCopy > 0) {
	//		////		int digit = NCopy % 10;
	//		////		square += digit * digit;
	//		////		NCopy /= 10;
	//		////	}
	//		////}

	//		////square 

	//		//unordered_set<int> rec;
	//		//dp[make_pair(i, j)] = is_happy(square, j, rec);
	//	}
	//}

	/*for (int i = 1; i <= LIMIT; i++) {
		unordered_set<int> rec;
		dp[i] = is_happy(i, 10, rec);

		if (i % 1000000 == 0) cout << i << endl;
	}
	cout << "finished";*/

	//for (int i = 1; i <= LIMIT; i++) {
	//	cout << i << ": " << dp[i] << endl;
	//}

	

	int T;
	cin >> T;

	string line;
	getline(cin, line);
	for (int t = 1; t <= T; t++) {
		getline(cin, line);
		vector<int> bases;
		vector<string> strings = split(line, ' ');
		for (int i = 0; i < strings.size(); i++) {
			bases.push_back(atoi(strings[i].c_str()));
		}


		//vector<int> bases = { 2, 3, 7};
		int i;
		for (i = 2; i <= LIMIT; i++) {
			bool bFound = true;
			for (int j = 0; j < bases.size(); j++) {
				int base = bases[j];
				int value = convertTenToBase(i, base);
				int NCopy = value;

				int square = 0;
				while (NCopy > 0) {
					int digit = NCopy % 10;
					square += digit * digit;
					NCopy /= 10;
				}

				square = convertTenToBase(square, base);

				unordered_set<int> baseSet;
				int result = is_happy(square, base, baseSet);
				if (result == 0) {
					bFound = false;
					break;
				}
				/*if (dp[square] == 0) {
					bFound = false;
					break;
				}*/
			}

			if (bFound) break;
		}

		cout << "Case #" << t << ": " << i << endl;
	}

	return 0;
}