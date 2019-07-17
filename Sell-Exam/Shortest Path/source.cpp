#include<iostream>
#include<vector>
#include"heap.h"

using namespace std;
const int integer_limit = 1057483640;

int main(){
	// Store connected vertex and the deriction to it
	// 0 down , 1 right , 2 left , 4 up
	vector<vector<pair<int,int>>> verteces;
	// Least cost for each node
	int cost[10000];
	int vis[10000];
	int prev[10000];
	memset(vis,false,10000);
	memset(cost,integer_limit,10000);
	int n,m,x,start,end;
	cin>>n>>m;
	cin>>x>>start;
	start = x *m +start;
	cin>>x>>end;
	end = x*m+end;
	int input;
	// Store in the 2d array in form of gaph
	for(int i=0;i<n*m;i++)
	{
		vector<pair<int,int>> vertex ;
		pair<int,int> me ;
		pair<int,int>before ;
		cin>>input;
		me.first = input;
		me.second = -1;
		vertex.push_back(me);
		if(input != 1){
			if(i%m !=0 && verteces[i-1][0].first!= 1){
				before.first =i-1 ;
				before.second = 2;
				vertex.push_back(before);
				before.first = i;
				before.second = 1;
				verteces[i-1].push_back(before);
			}
			if( i >=m && verteces[i-m][0].first == 0){
				before.first = i-m;
				before.second = 4;
				vertex.push_back(before);
				before.first = i;
				before.second = 0;
				verteces[i-m].push_back(before);
			}
		}
		verteces.push_back(vertex);
	}
	//dijkestra algo
	heap priorety_queue ;
	// push head
	priorety_queue.insert(start,0,-1,-1);
	while(priorety_queue.notEmpty())
	{
		int id,c,p,car_direction;
		priorety_queue.get_lowest(id,c,p,car_direction);
		if(c<cost[id]) {
			cost[id] = c;
			prev[id] = p;
		}
		if(!vis[id]){
			for(int i=1;i<verteces[id].size();i++)
			{
				int additional_cost =1;
				if(car_direction ==verteces[id][i].second || car_direction == -1 )
				{
					additional_cost--;
				}
				if(c+additional_cost < cost[verteces[id][i].first])
				{
					priorety_queue.insert(verteces[id][i].first,c+additional_cost,id,verteces[id][i].second);
				}
			}
			vis[id]=true;
		}
		priorety_queue.delete_lowest();
	}
	int curr = end;
	while(curr!=-1){
		verteces[curr][0].first = 2;
		curr = prev[curr];
	}
	cout<<endl;
	for(int i =0;i<n;i++){
		for(int j=0;j<m;j++)
		{
			char print;
			if(verteces[i*m+j][0].first==2){
				print = '-';
			} else if (verteces[i*m+j][0].first==1){
				print = '1';
			} else {
				print = '0';
			}
			cout<<print<<" ";
		}
		cout<<endl;
	}
	system("pause");
	return 0;
}
