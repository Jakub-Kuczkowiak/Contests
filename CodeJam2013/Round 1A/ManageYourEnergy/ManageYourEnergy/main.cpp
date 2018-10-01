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

typedef pair<long, long> Pair;

class Compare {
public:
	bool operator() (Pair a, Pair b) {
		return a.second < b.second;
	}
}compare;

template <class T>
class SegmentTree
{
public:
	SegmentTree(int n, T(*func)(T, T), T identity) {
		this->n = n;
		this->function = func;
		this->identity = identity;
		t = new T[2 * n];
	}

	~SegmentTree() {
		delete[] t;
	}

	__inline T get_leaf(int index) const {
		return t[n + index];
	}

	__inline void initialize_leaf(int index, T value) {
		t[n + index] = value;
	}

	// We use build to reduce complexity to O(n) instead of O(nlog n)
	void build() {
		for (int i = n - 1; i > 0; --i) t[i] = function(t[i << 1], t[i << 1 | 1]);
	}

	void modify_point(int p, T value) {  // set value at position p FINE
		for (t[p += n] = value; p > 1; p >>= 1) {
			t[p >> 1] = function(t[p], t[p ^ 1]); // t[p ^ 1] is the other child
		}
	}

	T query_interval(int l, int r) {  // query on interval [l, r); returns identity for (0, -x)
		T res = identity; // ?
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res = function(res, t[l++]);
			if (r & 1) res = function(res, t[--r]);
		}
		return res;
	}

	/*void modify_interval(int l, int r, T value) { // modify interval [l, r)
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) t[l++] = function(t[l], value);
			if (r & 1) t[r] = function(t[--r], value);
		}
	}

	T query_point(int p) { // query value at position p
		T res = identity; // ?
		for (p += n; p > 0; p >>= 1) res = function(res, t[p]);
		return res;
	}*/

	// If at some point after modifications we need to inspect all the elements in the array, 
	// we can push all the modifications to the leaves using the following code. 
	// After that we can just traverse elements starting with index n.
	// Time complexity: O(n)
	void push() {
		for (int i = 1; i < n; ++i) {
			t[i << 1] = function(t[i << 1], t[i]);
			t[i << 1 | 1] = function(t[i << 1 | 1], t[i]);
			t[i] = identity;
		}
	}

private:
	T* t;
	int n;
	T identity;

	T(*function)(T leaf1, T leaf2);
};

int max(int a, int b) {
	return (a > b ? a : b);
}

bool solveLeft(SegmentTree<int>* tree, long long fixed, long long index) {
	return tree->query_interval(index, fixed);
}

bool solveRight(SegmentTree<int>* tree, long long fixed, long long index) {
	return tree->query_interval(fixed + 1, index + 1);
}

long long binary_answer(SegmentTree<int>* tree, long long fixed, long long l, long long r, bool(*solve)(SegmentTree<int>*, long long, long long)) {
	if (l > r) return -1; // base case; no found element

	long long m = l + (r - l) / 2;

	if (solve(tree, fixed, m)) { // we met some 'yes' here
		long long answer = binary_answer(tree, fixed, l, m - 1, solve);
		if (answer != -1) {
			return answer;
		}
		else {
			return m;
		}
	}
	else {
		return binary_answer(tree, fixed, m + 1, r, solve);
	}
}

// yes yes yes no no no
long long binary_answer2(SegmentTree<int>* tree, long long fixed, long long l, long long r, bool(*solve)(SegmentTree<int>*, long long, long long)) {
	if (l > r) return -1; // base case; no found element

	long long m = l + (r - l) / 2;

	if (solve(tree, fixed, m)) { // we met some 'yes' here
		long long answer = binary_answer2(tree, fixed, m + 1, r, solve);
		if (answer != -1) {
			return answer;
		}
		else {
			return m;
		}
	}
	else {
		return binary_answer2(tree, fixed, l, m - 1, solve);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		long long E, R, N;
		cin >> E >> R >> N;

		SegmentTree<int> tree = SegmentTree<int>(N, max, 0);

		priority_queue<Pair, vector<Pair>, Compare> pq; // (index, value)
		vector<long long> activities(N), start(N), end(N);
		vector<bool> filled(N);
		for (int i = 0; i < N; i++) {
			cin >> activities[i];
			start[i] = end[i] = filled[i] = 0;
			pq.push(make_pair(i, activities[i]));
			tree.initialize_leaf(i, 0);
		}

		tree.build();

		unsigned long long answer = 0;

		// for each element
		while (!pq.empty()) {
			Pair el = pq.top();
			pq.pop();

			long long index = el.first;
			long long value = el.second;

			// find first left, find first right
			int left = binary_answer2(&tree, index, 0, index - 1, solveLeft);
			int right = binary_answer(&tree, index, index + 1, N - 1, solveRight);

			if (left == -1)
				start[index] = E;
			else
				start[index] = min(E, (index - left) * R + end[left]);

			if (right == -1)
				end[index] = 0;
			else
				end[index] = max((long long)0, start[right] - (right - index) * R);

			tree.modify_point(index, 1);
			answer += (start[index] - end[index]) * value;
		}

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}