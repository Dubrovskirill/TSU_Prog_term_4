#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include<QGraphicsPixmapItem>
#include<QGraphicsView>


#include "SearchTree.h"
#include "SearchTreeTester.h"
#include "TreeWidget.h"
int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    TreeWidget widget;
    widget.show();
    for (int i = 0; i < 20; ++i) {
        widget.addKey(rand() % 100);
    }
    return app.exec();

        srand(time(0));
        SearchTreeTester tester(false);
        tester.test(300);

        return 0;

    SearchTree tr;
    int arr[8] = { 65, 71, 81, 32, 62, 57, 69, 45 };
    for (int i = 0; i < 8; ++i) {
        tr.add(arr[i]);
    }

    tr.print_3(tr.root());
        while(tr.root()!=nullptr)
        {
            tr.remove(tr.root()->getKey());
            tr.print_3(tr.root());

        }
    return 0;
}


