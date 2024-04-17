#include "binarytree.h"
#include <stdlib.h>
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "TreeWidget.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TreeWidget widget;
    widget.show();
    for (int i = 0; i < 20; ++i) {
        widget.addKey(i + 1);
    }
    return app.exec();
}

//int main(int argc, char *argv[])
//{
//    BinaryTree tr;
//    for (int i = 1; i < 10; ++i)
//    {
//        tr.add(i);
//    }

//    tr.print_3(tr.root());
//    tr.remove(1);
//    tr.print_3(tr.root());
//    return 0;
//}
