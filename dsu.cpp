#include<iostream>
#include<string>
 
using namespace std;
 
int p[100001]; // parent
int s[100001];	// rank
 
 
int get(int a) {
	return p[a] = (p[a] == a ? a: get(p[a]));
}
 
void join(int a, int b){
	a = get(a);
	b = get(b);
	if(s[a] < s[b])
        swap(a,b);
    s[a] += s[b];
    p[b]= a;
}
 
int main() {
	int n, m;
	cin >> n >> m;
	for(int i = 0 ; i <= n ; i++) {
		p[i] = i;
	}
	while(m--){
		string s;
		int u, v;
		cin >> s;
		cin >> u >> v;
		if(s[0] =='u'){
			join(u, v);
		} else {
			if(get(u) == get(v)) cout << "YES" <<endl;
			else cout << "NO" << endl;
		}
	}
	return 0;
}
