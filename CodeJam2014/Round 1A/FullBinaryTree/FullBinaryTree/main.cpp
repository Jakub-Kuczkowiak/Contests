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

int N;
vector<vector<int>> edges;

map<pair<int, int>, long long> dp;
map<pair<int, int>, int> children;

long long countChildren(int v, int root) {
	if (children.find(make_pair(v, root)) != children.end()) {
		return children[make_pair(v, root)];
	}

	long long sum = 1;
	for (int i = 0; i < edges[v].size(); i++) {
		if (edges[v][i] == root) continue;

		sum += countChildren(edges[v][i], v);
	}

	children[make_pair(v, root)] = sum;
	children[make_pair(root, v)] = N - sum;
	return sum;
}

long long countDP(int v, int root) { // minimal number of vertices one has to remove to get tree rooted at v coming from root of height K
	if (dp.find(make_pair(v, root)) != dp.end()) {
		return dp[make_pair(v, root)];
	}

	// go through all children
	long long result = 0;

	vector<int> sizes;
	vector<int> subsolutions;

	for (int i = 0; i < edges[v].size(); i++) {
		if (edges[v][i] == root) continue;

		subsolutions.push_back(countDP(edges[v][i], v));
		sizes.push_back(countChildren(edges[v][i], v));
	}

	// 0 and 1 children case
	if (subsolutions.size() == 0) return 0;
	else if (subsolutions.size() == 1) {
		dp[make_pair(v, root)] = sizes[0];
		return sizes[0];
	}

	// find two highest differences
	int largest1Index = 0, largest2Index = 1;
	long long largest1 = sizes[0] - subsolutions[0];
	long long largest2 = sizes[1] - subsolutions[1];
	if (largest1 < largest2) {
		swap(largest1, largest2);
		largest1Index = 1; largest2Index = 0;
	}

	for (int i = 2; i < subsolutions.size(); i++) {
		if (sizes[i] - subsolutions[i] > largest1) {
			largest2 = largest1;
			largest1 = sizes[i] - subsolutions[i];
			largest2Index = largest1Index;
			largest1Index = i;
		}
		else if (sizes[i] - subsolutions[i] > largest2) {
			largest2 = sizes[i] - subsolutions[i];
			largest2Index = i;
		}
	}

	// we take subsolutions of smallest and then size of rest
	long long answer = subsolutions[largest1Index] + subsolutions[largest2Index];
	for (int i = 0; i < subsolutions.size(); i++) {
		if (i == largest1Index || i == largest2Index) continue;
		answer += sizes[i];
	}

	dp[make_pair(v, root)] = answer;
	return answer;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> N;
		edges = vector<vector<int>>(N + 1);

		children.clear();

		for (int i = 1; i < N; i++) {
			int a, b;
			cin >> a >> b;

			edges[a].push_back(b);
			edges[b].push_back(a);
		}

		long long answer = LONG_MAX;

		// vertices 1 ... N
		for (int i = 1; i <= N; i++) {
			dp.clear();
			//children.clear();

			// let's root the tree at i
			long long result = countDP(i, -1);
			if (result < answer)
				answer = result;
		}

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}