#include "heap.h"

void heap::swap(int index1,int index2){
	Node temp;
	temp = harr[index1];
	harr[index1] = harr[index2];
	harr[index2]= temp;
}

heap::heap()
{
	heap_size =0;
	for(int i=0;i<10000;i++){
		harr[i].cost = 1057483640;
	}
}


heap::~heap(void)
{
}

void heap::insert(int id,int cost,int prev,int car_deriction) {
	harr[heap_size].id= id;
	harr[heap_size].cost = cost;
	harr[heap_size].prev = prev;
	harr[heap_size].car_deriction = car_deriction;
	while(harr[heap_size/2].cost > cost){
		swap(heap_size,heap_size/2);
	}
	heap_size++;
}

void heap::delete_lowest(){
	if(heap_size ==0)
		return;
	swap(0,heap_size-1);
	harr[heap_size-1].cost= 1057483640;
	heap_size--;
	int higer,higer_id;
	int index = 0;
	if(harr[1].cost>harr[2].cost)
	{
		higer = harr[2].cost;
		higer_id =2 ;
	} else {
		higer = harr[1].cost;
		higer_id = 1;
	}
	while(higer < harr[index].cost)
	{
		swap(higer_id,index);
		index = higer_id;
		if(harr[index*2].cost<harr[index*2+1].cost)
		{
			higer = harr[index*2].cost;
			higer_id =index*2 ;
		} else {

			higer = harr[index*2+1].cost;
			higer_id =index*2+1 ;
		}
	}
}

void heap::get_lowest(int& id,int& cost,int&prev,int&car_derication){
	id = harr[0].id;
	cost = harr[0].cost;
	prev = harr[0].prev;
	car_derication = harr[0].car_deriction;
}
