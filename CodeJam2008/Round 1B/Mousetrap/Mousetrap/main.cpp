#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/*
SegmentTree(int n): initializes tree with given size.
int n: maximum number of tree's leafs
T (*func)(T, T): function that returns parent's value based on two leafs. Function must be commutative (i.e. a + b = b + a)
T identity: identity given function 'func' (0 for sum, +inf for min, -inf for max)
Remember to initialize all leafs using initialize_leaf function and when finished call build.
First leaf is at position t[n]
*/
template <class T>
class SegmentTree
{
public:
	SegmentTree(int n, T (*func)(T, T), T identity) {
		this->n = n;
		this->function = func;
		this->identity = identity;
		t = new T[2 * n];
	}

	~SegmentTree() {
		delete[] t;
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

	T query_interval(int l, int r) {  // query on interval [l, r) FINE
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
	int* t;
	int n;
	T identity;

	T (*function)(T leaf1, T leaf2);
};

using namespace std;

int K;
int Arr[1000001] = {};

int getNextFree(int position, int move) {
	move = ((move - 1) % (K - move + 1)) + 1;

	while (move > 0) {
		position = (position + 1) % K;
		if (Arr[position] == 0) move--;
	}

	return position;
}

int mbin_search(SegmentTree<int>& tree, int move, int fixedL, int l, int r) {
	if (l > r) return -1;

	int m = (l + r) / 2;

	int free = m - tree.query_interval(fixedL, fixedL + m);
	if (free < move) {
		return mbin_search(tree, move, fixedL, m + 1, r);
	}
	else if (free = move) {
		int index = mbin_search(tree, move, fixedL, l, m - 1);
		if (index == -1) return fixedL + m - 1;
		else return index;
	}
	else { // free > move
		return mbin_search(tree, move, fixedL, l, m - 1);
	}
}

int getNextFree2(SegmentTree<int>& tree, int position, int move) {
	move = ((move - 1) % (K - move + 1)) + 1;

	int free = K - position - 1 - tree.query_interval(position + 1, K);

	int l = -1, r = -1;
	if (position == K - 1) {
		l = 0;
		r = position - 1;
	}
	else {
		if (free < move) {
			l = 0;
			r = position - 1;
			move = move - free;
		}
		else { // free >= move so we can fit in the right part
			l = position + 1;
			r = K - 1;
		}
	}

	int x = r - l + 1;
	return mbin_search(tree, move, l, 1, x);
}

int sum(int a, int b) {
	return a + b;
}

int main() {
	ios_base::sync_with_stdio(false);

	/*SegmentTree<int> tree(13, sum, 0);
	for (int i = 0; i < 10; i++) {
		tree.initialize_leaf(i, 3 + i);
	}

	for (int i = 10; i < 13; i++) {
		tree.initialize_leaf(i, 0);
	}

	int result = 0;
	tree.build();
	result = tree.query_interval(0, 13);
	//tree.modify_point(2, 10);
	result = tree.query_interval(0, 13);
	tree.modify_interval(2, 6, 10);
	result = tree.query_point(3);*/

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> K;

		SegmentTree<int> tree = SegmentTree<int>(K, sum, 0);
		Arr[0] = 1;
		tree.initialize_leaf(0, 1);
		for (int i = 1; i < K; i++) {
			Arr[i] = 0;
			tree.initialize_leaf(i, 0);
		}

		tree.build();

		int pos = 0;
		for (int i = 2; i <= K; i++) {
			//pos = getNextFree(pos, i);
			pos = getNextFree2(tree, pos, i);
			Arr[pos] = i;
			tree.modify_point(pos, 1);
		}

		int n;
		cin >> n;

		int positions[101] = {};

		for (int i = 0; i < n; i++) {
			cin >> positions[i];
		}

		cout << "Case #" << t << ": ";

		for (int i = 0; i < n; i++) {
			cout << Arr[positions[i] - 1] << " ";
		}

		cout << endl;
	}

	return 0;
}