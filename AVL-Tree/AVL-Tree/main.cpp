#include<vector>

#include "AvlTree.h"

int main()
{
	AvlTree tr;
	int arr[13] = { 10,20,40,35,38,36,5, 13, 15, 56, 12, 67,689 };
	for(int i=0;i<13;++i)
	{
		tr.add(arr[i]);
		tr.print_3(tr.root());
		std::cout << std::endl;
	}
	
}