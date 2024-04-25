#pragma once

#include <QWidget>

#include "BinaryTree.h"
#include <QPainter>
#include <QApplication>

class QGraphicsScene;

namespace Ui {
class TreeWidget;
}

class TreeWidget : public QWidget
{
    Q_OBJECT



public:
    explicit TreeWidget(QWidget *parent = nullptr);
    ~TreeWidget();

    void show();

public slots:
    void addKey(int key);
    void removeKey(int key);

protected:
    void resizeEvent(QResizeEvent *event) override;


private:
    QPointF _drawTree(BinaryTree::Node *root, int leftBorderPos, int rightBorderPos, int yPos);
    void _redrawTree();
    void _updateSceneRect();

private:
    Ui::TreeWidget *ui;
    int m_fontSize = 22;
    BinaryTree *m_tree = nullptr;
    QGraphicsScene *m_scene = nullptr;

};
