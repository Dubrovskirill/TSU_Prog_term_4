#include <QCoreApplication>
#include "SearchTree.h"
#include "SearchTreeTester.h"
int main()
{

    srand(time(0));
    SearchTreeTester tester(false);
    tester.test(1000);

    return 0;
}
