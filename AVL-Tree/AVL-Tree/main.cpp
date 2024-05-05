#include<vector>
#include <thread>
#include<assert.h>
#include <vector>
#include<random>
#include "AvlTree.h"
#include "AvlTreeTester.h"


int main()
{

    /*srand(time(0));
    AvlTreeTester tester(true);
    tester.test(25);
    return 0;*/



    AvlTree tr;
    int arr[12] = { 10,6,16,2,8,14,20,1,4,12,18,25 };
    for (int i = 0; i < 12; ++i)
    {
        tr.add(arr[i]);
        tr.print_3(tr.root());
        std::cout << std::endl;
    }
  
    for (int i = 0; i < 12; ++i)
    {
        tr.remove(arr[i]);
        tr.print_3(tr.root());
        (tr.isBalanced() ? std::cout << "correct" << std::endl : std::cout << "error" << std::endl);
        std::cout << std::endl;
    }
    return 0;

 





















	
	
}