#include "binarytree.h"
#include "ui_binarytree.h"

BinaryTree::BinaryTree(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BinaryTree)
{
    ui->setupUi(this);
}

BinaryTree::~BinaryTree()
{
    delete ui;
}

