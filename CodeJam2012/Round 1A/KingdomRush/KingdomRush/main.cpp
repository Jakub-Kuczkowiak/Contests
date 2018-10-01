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

struct State
{
	int index;
	int value;
};

class Compare {
public:
	bool operator() (State a, State b) {
		return a.value < b.value;
	}
}compare;

int main() {
	//ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;

		vector<int> s1(N), s2(N);
		vector < State > l2(N);

		for (int i = 0; i < N; i++) {
			int a, b;
			cin >> a >> b;

			s1[i] = a;
			s2[i] = b;

			l2[i].index = i;
			l2[i].value = b;
		}

		sort(l2.begin(), l2.end(), compare);

		int count = 0;
		int stars = 0;

		bool bSuccess = false;

		int a_index = 0, b_index = 0;

		vector<bool> a_used(N), b_used(N);
		for (int i = 0; i < N; i++) {
			a_used[i] = b_used[i] = false;
		}

		// take as many 2nd levels as possible
		while (true) {
			while (b_index < N) {
				int required = l2[b_index].value;

				if (required <= stars) {
					count++;
					b_used[l2[b_index].index] = true;

					if (a_used[l2[b_index].index])
						stars += 1;
					else
						stars += 2;

					b_index++;
				}
				else {
					break;
				}
			}

			if (b_index == N) {
				bSuccess = true;
				break;
			}

			int b_max = -1;
			int index_max = -1;
			for (int i = 0; i < N; i++) {
				if (a_used[i] || b_used[i]) continue;

				if (s1[i] <= stars) {
					if (s2[i] > b_max) {
						b_max = s2[i];
						index_max = i;
					}
				}
			}

			if (index_max == -1) { // failure
				break;
			}

			count++;
			stars += 1;
			a_used[index_max] = true;
		}

		if (bSuccess)
			cout << "Case #" << t << ": " << count << endl;
		else
			cout << "Case #" << t << ": " << "Too Bad" << endl;
	}

	return 0;
}