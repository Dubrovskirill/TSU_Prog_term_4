#include <QCoreApplication>
#include "SearchTree.h"
int main()
{
    SearchTree foo, goo;
    int arr[8] = { 50, 70, 60, 20, 30, 90, 100, 10 };
    for (int i = 0; i < 8; ++i) {
        foo.BinaryTree::add(arr[i]);
    }
    foo.print_3(foo.root());


    std::cout << "min = " << foo.min() << "\n";
    std::cout << "max = " << foo.max() << "\n";
    std::cout << "level 10 = " << foo.BinaryTree::level(10);
    foo.BinaryTree::find(10);

    return 0;
}
