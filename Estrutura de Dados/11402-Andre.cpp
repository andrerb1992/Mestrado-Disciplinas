#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define debug if (false)

#define MAX (1024000+100)
#define BUCCANNER 1
#define BARBARY -1

struct lazy_t {
	int set;
	bool inv;
};

struct ST {
	int n;
	ll st[4*MAX];
	lazy_t lazy[4*MAX];

	/**
	 * Build and init tree
	 */
	void build(string &str) {
		n = str.length();
		memset(lazy, 0, sizeof lazy);
		memset(st, 0, sizeof st);

		build(1, 0, n-1, str);
	}

	void build(int node, int l, int r, string &str) {
		if (l == r) {
			st[node] = str[l] - '0'; // tree node
			// debug(cout << "at node " << node << " " << l << " " << str[l] << endl);
		}
		else {
			int mid = (l+r)/2;
			build(node*2, l, mid, str); // Init left child
			build(node*2+1, mid+1, r, str); // Init right child

			st[node] = st[node*2] + st[node*2+1]; // Init root value
		}
	}

	inline void lazy_set_children(int node, int value) {
		lazy[node*2].set = value; 
		lazy[node*2].inv = false;
		lazy[node*2+1].set = value;
		lazy[node*2+1].inv = false;
	}

	inline void lazy_inv_children(int node) {
		if (lazy[node*2].set)      lazy[node*2].set = -lazy[node*2].set;
		else                      lazy[node*2].inv = not lazy[node*2].inv;

		if (lazy[node*2+1].set) lazy[node*2+1].set = -lazy[node*2+1].set;
		else                      lazy[node*2+1].inv = not lazy[node*2+1].inv;
	}

	void push(int node, int i, int j) {
		if (lazy[node].set != 0) { // This node needs to be updated
			if (lazy[node].set == 1)
				st[node] = (j-i+1); // Update it
			else
				st[node] = 0; // Update it

			if (i != j) {
				// Mark child as lazy
				lazy_set_children(node, lazy[node].set);
			}

			lazy[node].set = 0; // Reset it
		}

		if (lazy[node].inv) { // This node needs to be updated
			st[node] = (j-i+1) - st[node]; // Update it

			if (i != j) {
				lazy_inv_children(node);
			}

			lazy[node].inv = false; // Reset it
		}
	}

	/**
	 * Increment elements within range [l, r] with value value
	 */
	void set(int l, int r, ll value) {
		set(1, 0, n-1, l, r, value);
	}

	void set(int node, int i, int j, int ql, int qr, ll value) {
		push(node, i, j);

		if (i > qr || j < ql) // Current segment is not within range [ql, qr]
			return;

		if (ql <= i && j <= qr) { // Segment is fully within range
			if (value == 1) st[node] = (j-i+1); // Update it
			else             st[node] = 0; // Update it

			if (i != j) { // Not leaf node
				lazy_set_children(node, value);
			}

			return;
		}

		int mid = (i+j)/2;
		set(node*2, i, mid, ql, qr, value); // Updating left child
		set(node*2+1, mid+1, j, ql, qr, value); // Updating right child

		st[node] = st[node*2] + st[node*2+1]; // Updating root
	}

	void inv(int l, int r) {
		inv(1, 0, n-1, l, r);
	}

	void inv(int node, int i, int j, int ql, int qr) {
		push(node, i, j);

		if (i > qr || j < ql) // Current segment is not within range [ql, qr]
			return;

		if (ql <= i && j <= qr) { // Segment is fully within range
			st[node] = (j-i+1) - st[node]; // Update it

			if (i != j) { // Not leaf node
				lazy_inv_children(node);
			}

			return;
		}

		int mid = (i+j)/2;
		inv(node*2, i, mid, ql, qr); // Updating left child
		inv(node*2+1, mid+1, j, ql, qr); // Updating right child

		st[node] = st[node*2] + st[node*2+1]; // Updating root
	}

	/**
	 * Query tree to get value within range [l, r]
	 */
	ll query(int l, int r) {
		return query(1, 0, n-1, l, r);
	}

	ll query(int node, int i, int j, int ql, int qr) {
		if (i > qr || j < ql) return 0; // Out of range

		push(node, i, j);

		if (ql <= i && j <= qr) // Current segment is totally within range [l, r]
			return st[node];

		int mid = (i+j)/2;
		ll q1 = query(node*2, i, mid, ql, qr); // Query left child
		ll q2 = query(node*2+1, mid+1, j, ql, qr); // Query right child

		ll res = q1 + q2; // Return final result

		return res;
	}
};

ST st;
int main() {
	int T; cin >> T;

	for (int t = 1; t <= T; ++t) {
		int M; cin >> M;

		string str;
		while (M--) {
			int T; string P;
			cin >> T >> P;
			while (T--) str += P;
		}

		st.build(str);

		// debug cout << "after build" << endl;
		// debug for (int i = 0; i < 4*str.size(); ++i) cout << i%10 << " ";
		// debug cout << endl;
		// debug for (int i = 0; i < 4*str.size(); ++i) cout << st.st[i] << " ";
		// debug cout << endl;

		cout << "Case " << t << ":" << endl; // imprime os caso 
		int Q; cin >> Q; // descreve o numero de consulta 
		int q = 1;
		while (Q--) {
			char op;
			int a, b;
			cin >> op >> a >> b; // string de consulta >> indice a >> indice b

			if (op == 'F') st.set(a, b, BUCCANNER);
			else if (op == 'E') st.set(a, b, BARBARY);
			else if (op == 'I') st.inv(a, b);
			else if (op == 'S') cout << "Q" << q++ << ": " << st.query(a, b) << endl;
		}

	}
}
