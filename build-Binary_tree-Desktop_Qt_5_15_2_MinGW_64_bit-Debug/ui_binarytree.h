/********************************************************************************
** Form generated from reading UI file 'binarytree.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINARYTREE_H
#define UI_BINARYTREE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BinaryTree
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BinaryTree)
    {
        if (BinaryTree->objectName().isEmpty())
            BinaryTree->setObjectName(QString::fromUtf8("BinaryTree"));
        BinaryTree->resize(800, 600);
        centralwidget = new QWidget(BinaryTree);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        BinaryTree->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BinaryTree);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        BinaryTree->setMenuBar(menubar);
        statusbar = new QStatusBar(BinaryTree);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        BinaryTree->setStatusBar(statusbar);

        retranslateUi(BinaryTree);

        QMetaObject::connectSlotsByName(BinaryTree);
    } // setupUi

    void retranslateUi(QMainWindow *BinaryTree)
    {
        BinaryTree->setWindowTitle(QCoreApplication::translate("BinaryTree", "BinaryTree", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BinaryTree: public Ui_BinaryTree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINARYTREE_H
