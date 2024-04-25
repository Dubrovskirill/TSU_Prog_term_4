#include <iostream>
#include "../../BinarySearchTree/SearchTree.h"
#include "../../BinarySearchTree/SearchTreeTester.h"

#include <cstdlib>
#include <ctime>
int main()
{

    SearchTree tr;
    int arr[8] = { 77, 56, 60, 28, 30, 45, 100, 10 };
    for (int i = 0; i < 8; ++i) {
        tr.add(arr[i]);
    }
    tr.print_3(tr.root());
    tr.clear();
    std::cout << std::endl;
    tr.print_3(tr.root());

    return 0;
    
    

}
