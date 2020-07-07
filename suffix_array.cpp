#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

string s;

void countSort(vector<int>& p , vector<int>& c){
	int n = p.size();
	vector<int> count(n), pos(n);
	for(auto i : c){
		count[i]++ ;
	}

	for(int i = 0 ; i < n-1 ; i++){
		pos[i+1] = count[i] + pos[i];
	}
	
	vector<int> p_new (n);
	
	for(auto x :p){
		int i = c[x];
		p_new[pos[i]] = x;
		pos[i]++;
	}
	p = p_new;
}

int greatestlesser(int low, int high, string key , vector<int>& p);

int leastgreater(int low, int high, string key , vector<int>& p);

void suffixArray(string& s, vector<int>& c , vector<int>& p, int l){
	int n = s.size();
	{
		vector<pair<char,int>> temp(n);
		for(int i = 0 ; i < n ; i++) temp[i] = pair<char,int>(s[i] , i);
		sort(temp.begin() , temp.end());
		c[0] = 0 , p[0] = temp[0].second;
		for(int i = 1 ; i < n ; i++){
			p[i] = temp[i].second;
			if(temp[i].first == temp[i-1].first)	c[p[i]] = c[p[i-1]];
			else c[p[i]] = c[p[i-1]] + 1;
		}
	}
	int k = 0;
	while( (1<<k) < n){
		
		for(int i = 0 ; i < n ; i++){
			p[i] = (p[i] - (1<<k) + n ) % n;
		}
		countSort(p,c);
		
		vector<int> c_new(n);
		c_new[p[0]] = 0 ;
		for(int i = 1 ; i < n ; i++){
			pair<int,int> prev(c[p[i-1]] , c[(p[i-1] + (1<<k))%n]);
			pair<int,int> now(c[p[i]] , c[(p[i] + (1<<k))%n]);
			if(prev == now)	c_new[p[i]] = c_new[p[i-1]];
			else c_new[p[i]] = c_new[p[i-1]] + 1;
		}
		k++;
		c = c_new;
	}
	
	vector<int> lcp(n),new_pos(n);
	k = 0;
	for(int i = 0 ; i < n - 1 ; i++){
		int pi = c[i];
		int j = p[pi - 1]; 
		while( s[i + k] == s[j + k])k++;
		// longest common prefix
		lcp[pi] = k;
		k = max( k-1 , 0);
	} 

	int ans = n * (n-1) /2;
	int index_least = 0  ,acc = 0;
	for(int i = 1 ; i < n ; i++){
		ans += acc;
		if( lcp[i-1] == 0){
		    acc = 0 ;
		    index_least = i-1;
		}
		if(lcp[i] < lcp[i-1]){
			int index = i-1;
			acc = 0;
			while(index > index_least){
			    acc += min(lcp[i] , lcp[index]);
				index--;
			}
		}
		
		acc += lcp[i];
	}
	ans += acc;
	cout<<ans<<endl;
}

int binarySearch(vector<int>& p ,string& s, string& query ,int size, int l , int r){
	int mid = (l + r)/2;
	if(r >= l){
		if(s.substr(p[mid],size) == query)
			return mid;

		if(s.substr(p[mid],size) > query)
			return binarySearch(p,s,query,size,l,mid-1);
	
		return binarySearch(p,s,query,size,mid+1,r);
	}
	return -1;
}

int main(){
	cin>>s;
	s += '$';
	int n = s.size();
	vector<int> c(n) , p(n);
	suffixArray(s,c,p,n-1);
	system("pause");
	return 0;
}


int greatestlesser(int low, int high, string key,vector<int>& p) 
{ 
    int ans = -1; 
  
    while (low <= high) { 
        int mid = low + (high - low + 1) / 2; 
        string midVal = s.substr(p[mid],key.size());
  
        if (midVal < key) { 
            ans = mid; 
            low = mid + 1; 
        } 
        else if (midVal > key) { 
            high = mid - 1; 
        } 
        else if (midVal == key) { 
            high = mid - 1; 
        } 
    } 
  
    return ans; 
} 

int leastgreater(int low, int high, string key , vector<int>& p) 
{ 
    int ans = s.size(); 
  
    while (low <= high) { 
        int mid = low + (high - low + 1) / 2; 
         string midVal = s.substr(p[mid],key.size());
  
        if (midVal < key) { 
            low = mid + 1; 
        } 
        else if (midVal > key) { 
            ans = mid; 
            high = mid - 1; 
        } 
        else if (midVal == key) { 
            low = mid + 1; 
        } 
    } 
  
    return ans; 
} 

