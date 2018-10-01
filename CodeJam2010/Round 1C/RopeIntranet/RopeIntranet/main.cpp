#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h> // INT_MAX
#include <math.h> // pow in g++
#include <string> // is needed in gcc?
#include <cstring> // one of string can be removed; cstring contains memset
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

/* https://codeforces.com/blog/entry/18051 */

/*
SegmentTree(int n): initializes tree with given size.
int n: maximum number of tree's leafs
T (*func)(T, T): function that returns parent's value based on two leafs. Function must be commutative (i.e. a + b = b + a)
T identity: identity given function 'func' (0 for sum, +inf for min, -inf for max)
Remember to initialize all leafs using initialize_leaf function and when finished call build.
First leaf is at t[n]
Quering interval at [0, x) for any negative x returns identity so we do not need special cases.
*/
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

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

struct Wire
{
	int A;
	int B;
};

int sum(int a, int b) {
	return a + b;
}

bool myfunction(Wire i, Wire j) { return (i.A >= j.A); }

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;

		vector<Wire> W(N);
		for (int i = 0; i < N; i++) {
			cin >> W[i].A;
			cin >> W[i].B;
		}

		sort(W.begin(), W.end(), myfunction);
		SegmentTree<int> tree = SegmentTree<int>(10002, sum, 0);
		for (int i = 0; i < 10002; i++) {
			tree.initialize_leaf(i, 0);
		}

		tree.build();

		int connections = 0;
		for (int i = 0; i < N; i++) {
			connections += tree.query_interval(0, W[i].B);
			int current = tree.get_leaf(W[i].B);
			tree.modify_point(W[i].B, current + 1);
		}

		cout << "Case #" << t << ": " << connections << endl;
	}

	return 0;
}