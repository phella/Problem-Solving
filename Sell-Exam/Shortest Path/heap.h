#pragma once
#include<iostream>
using namespace std;
struct Node{
	int cost;
	int id;
	int prev;
	int car_deriction;
};

class heap
{

	Node harr[10000];
	int heap_size;
	void swap(int,int);
public:
	heap();
	~heap(void);
	void insert(int,int,int,int);
	void get_lowest(int&,int&,int&,int&);
	void delete_lowest();
	bool notEmpty(){
		if(heap_size!=0){
			return true;
		} else {
			return false;
		}
	};
};
