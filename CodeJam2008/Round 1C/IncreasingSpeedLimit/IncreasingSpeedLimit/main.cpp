#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string> // is needed in gcc?

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

private:
	T* t;
	int n;
	T identity;

	T(*function)(T leaf1, T leaf2);
};

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		long long n, m, X, Y, Z;
		cin >> n >> m >> X >> Y >> Z;

		vector<long long> signs(n);

		vector<long long> A(m);
		for (int i = 0; i < m; i++) {
			cin >> A[i];
		}

		for (int i = 0; i < n; i++) {
			signs[i] = A[i % m];
			A[i % m] = (X * A[i % m] + Y * (i + 1)) % Z;
		}

		// here we normalize our array
		vector<long long> B = signs;
		sort(B.begin(), B.end());

		for (int i = 0; i < n; i++) {
			// we look for the first position of element A[i] in B
			auto it = lower_bound(B.begin(), B.end(), signs[i]);
			int index = it - B.begin();

			signs[i] = index;
		}

		SegmentTree<long long> tree = SegmentTree<long long>(n, [](long long a, long long b) {return a + b; }, 0);
		for (int i = 0; i < n; i++) {
			tree.initialize_leaf(i, 0);
		}

		tree.build();

		vector<long long> dp(n);
		//dp[0] = 1;
		//tree.modify_point(signs[0], 1);
		for (int i = 0; i < n; i++) {
			dp[i] = 1;

			// sum is O(nlogn) solution doing the inner loop below
			long long sum = tree.query_interval(0, signs[i]);

			/*for (int j = 0; j < i; j++) { // O(n^2) solution
				if (signs[j] < signs[i])
					dp[i] = (dp[i] + dp[j]) % PRIME_MOD;
			}*/

			dp[i] = (dp[i] + sum) % PRIME_MOD;
			tree.modify_point(signs[i], tree.get_leaf(signs[i]) + dp[i]);
		}

		long long result = 0;
		for (int i = 0; i < n; i++) {
			result = (result + dp[i]) % PRIME_MOD;
		}

		cout << "Case #" << t << ": " << result << endl;
	}

	return 0;
}