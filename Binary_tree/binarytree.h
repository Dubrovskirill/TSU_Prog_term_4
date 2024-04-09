#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class BinaryTree; }
QT_END_NAMESPACE

class BinaryTree : public QMainWindow
{
    Q_OBJECT

public:
    BinaryTree(QWidget *parent = nullptr);
    ~BinaryTree();

private:
    Ui::BinaryTree *ui;
};
#endif // BINARYTREE_H
