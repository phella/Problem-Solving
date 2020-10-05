#include<bits/stdc++.h>

using namespace std;

/*
struct item {
	int m,c;
};
*/

typedef long long item;

// Complexity O( nlog(n) ) in building tree and O( log(n) ) modyfing and retreving
struct segtree {
	
	int size;
	long long NO_OPERATION = LLONG_MAX;
	vector<item> values;
	item NEUTRAL_ELEMENT = 0;

	// Code to be changed with problems ------------
	void init(int n) {
		size = 1;
		while(size < n)	size *= 2;
		values.resize(2*size);
	}

	long long operation(long long a, long long b){
		if(b == NO_OPERATION) return a;
		return b;
	}

	item single(int v) {
		return v;
	}

	item merge(item a, item b) {
		return b - a;
	}

	// ----------------------------

	void build(vector<int> &a, int x, int lx, int rx){
		if(rx - lx == 1) {
			if( lx < (int)a.size()){
				values[x] = a[lx];
			}
			return;
		}
		int m = (lx + rx) / 2;
		build(a, 2 * x + 1, lx, m);
		build(a, 2 * x + 2, m, rx);
		values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
	}

	void build(vector<int> &a) {
		build(a, 0, 0, size);
	}

	void set(int i, int v, int x,int lx, int rx){
		if(rx-lx == 1){
			values[x] = single(v);
			return;
		}

		int m = (lx + rx)/2;
		if( i < m){
			set(i, v, 2 * x + 1, lx, m);
		}else{
			set(i, v, 2 * x + 2, m ,rx);
		}
		values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
	}

	void set(int i , int v){
		set(i, v, 0, 0, size);
	}

	item calc(int l, int r, int x, int lx, int rx){
		if(lx >= r || l >= rx) return NEUTRAL_ELEMENT;
		if(lx >= l && rx <= r) return values[x];
		int m = (lx + rx) /2;
		item s1 = calc(l, r, x * 2 + 1, lx, m); 
		item s2 = calc(l, r, x * 2 + 2, m, rx);
		return merge(s1, s2);
	}
	
	item calc(int l ,int r) {
		return calc(l, r, 0 ,0 , size);
	}

	// Range methods
	void modify(int l, int r, long long v, int x, int lx, int rx){
		propagate(x, lx, rx);
		if(lx >= r || l >= rx) return;
		if(lx >= l && rx <= r) { 
			values[x] = operation(values[x], v);
			return;
		}
		int m = (lx + rx) /2;
		modify(l, r, v, x * 2 + 1, lx, m); 
		modify(l, r, v, x * 2 + 2, m, rx);
	}

	void modify(int l ,int r, int v) {
		modify(l, r, v, 0, 0, size);
	}

	long long get(int i, int x, int lx, int rx) {
		propagate(x, lx, rx);	
		if(rx - lx == 1){
			return values[x];
		}

		int m = (lx + rx) / 2;
		long long res;
		if( i < m){
			res = get(i,2 * x + 1, lx, m);
		}else{
			res = get(i,2 * x + 2, m ,rx);
		}
		return res;
	}

	long long get(int i) {
		return get(i, 0, 0, size);
	}

	void propagate(int x, int lx, int rx){
		if( rx - lx == 1) return;
		values[2 * x + 1] = operation( values[2 * x + 1], values[x]);
		values[2 * x + 2] = operation( values[2 * x + 2], values[x]);
		values[x] = NO_OPERATION;
	}
};

int main(){

	ios::sync_with_stdio(false);
	int n;
	cin >> n;

	segtree st;
	st.init(n);
	/*
	vector<int> a(n);
	for(int i = 0 ; i < n;i++){
		cin>>a[i];
	}
	
	st.build(a);
	*/

	int q;
	cin >> q;
	while(q--){
		int op;
		cin >> op;
		if( op == 1) {
			int l, r, v;
			cin >> l >> r >> v;
			st.modify(l, r, v);
		} else {
			int i;
			cin >> i;
			cout << st.get(i) << endl;
		}
		
	}

	return 0;
}
