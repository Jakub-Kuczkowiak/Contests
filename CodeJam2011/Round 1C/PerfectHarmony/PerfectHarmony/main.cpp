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
#define foreach(c, itr) for(__typeof((c).begin()) itr=(c).begin(); itr!=(c).end(); itr++)

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		unsigned long long N, L, H;
		cin >> N >> L >> H;

		vector<unsigned long long> nums(N);
		for (int i = 0; i < N; i++) {
			cin >> nums[i];
		}

		bool bFail = true;
		unsigned long long i;
		for (i = L; i <= H; i++) {
			bFail = false;
			for (int j = 0; j < N; j++) {
				if (i % nums[j] != 0 && nums[j] % i != 0) {
					bFail = true;
					break;
				}
			}

			if (!bFail) {
				break;
			}
		}

		if (bFail)
			cout << "Case #" << t << ": " << "NO" << endl;
		else 
			cout << "Case #" << t << ": " << i << endl;
	}

	return 0;
}