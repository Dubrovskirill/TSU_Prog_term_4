#include<vector>
#include <thread>
#include<assert.h>
#include<random>
#include "AvlTree.h"
#include "AvlTreeTester.h"
#include "../../BinarySearchTree/SearchTreeTester.h"
#include <assert.h>


int main()
{

    
    AvlTreeTester tester(false);
    tester.test(250);
    return 0;





    AvlTree tr;
    const int size = 1000;
    int arr[size];
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000; 
    };
    std::cout << "Array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < size; ++i)
    {
        tr.add(arr[i]);
        assert(tr.isBalanced());
       
    }
    std::cout << "ADD CORRECT\n";
    tr.print_3(tr.root());

    tr.clear();
    tr.print_3(tr.root());

   /* for (int i = size-1; i >= 0; --i)
    {
        tr.remove(arr[i]);
        assert(tr.isBalanced());

    }*/
       
    std::cout << "REMOVE CORRECT\n";

   

 





















	
	
}