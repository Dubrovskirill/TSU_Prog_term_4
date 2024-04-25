

#include<QGraphicsScene>
#include "TreeWidget.h"
#include "GraphicsNode.h"
#include "ui_TreeWidget.h"
#include "SearchTree.h"

TreeWidget::TreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeWidget),
    m_tree(new SearchTree),
    m_scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(m_scene);
    m_tree = new SearchTree();
    QStringList list_items;
    list_items<<"SearchTree"<<"BinaryTree";
    ui->comboBox->addItems(list_items);
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, [this](){addKey(ui->spinBox->value());});
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, [this] {removeKey(ui->spinBox->value());});
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, [this] { changeTree(ui->comboBox->currentIndex()); });
    connect(ui->pushButtonFind, &QPushButton::clicked, this, [this](){findKey(ui->spinBox->value());});
}

TreeWidget::~TreeWidget()
{
    delete ui;
    delete m_tree;
}

void TreeWidget::show()
{
    QWidget::show();
    _updateSceneRect();
}
void TreeWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    _updateSceneRect();
}

void TreeWidget::addKey(int key)
{
    m_tree->add(key);
    _redrawTree();
}

void TreeWidget::removeKey(int key)
{
    m_tree->remove(key);
    _redrawTree();
}

void TreeWidget::changeTree(int index)
{
    std::vector<int> treeVec = m_tree->bypassLnr();

    delete m_tree;
    if(index == 0)
    {
        m_tree = new SearchTree;
    }
    else if(index == 1)
    {
        m_tree =new BinaryTree ;
    }

    for(int i : treeVec)
    {
        m_tree->add(i);
    }
    _redrawTree();
}

void TreeWidget::findKey(int key)
{
    _redrawTree(m_tree->find(key));
}

QPointF TreeWidget::_drawTree(BinaryTree::Node *root, int leftBorderPos, int rightBorderPos, int yPos, BinaryTree::Node* targetNode)
{
    if (root == nullptr) {
        return QPointF();
    }
    int xPos = (leftBorderPos + rightBorderPos) / 2;
    GraphicsNode *item = new GraphicsNode(QString::number(root->getKey()));
    item->setFontSize(m_fontSize);

    if(root == targetNode)
    {
        item->setFillColor(Qt::red);
        item->update();
    }
    m_scene->addItem(item);
    item->setPos(xPos - item->boundingRect().width() / 2, yPos);
    QPointF center = item->pos() + QPointF(item->boundingRect().center());
    QPointF leftCenter = _drawTree(root->getLeft(), leftBorderPos, xPos, yPos + 75, targetNode);
    QPointF rightCenter = _drawTree(root->getRight(), xPos, rightBorderPos, yPos + 75, targetNode);

    if (!leftCenter.isNull()) {
        auto *line = m_scene->addLine(QLineF(center, leftCenter), QPen(Qt::red));
        line->setZValue(-1);
    }

    if (!rightCenter.isNull()) {
        auto *line = m_scene->addLine(QLineF(center, rightCenter), QPen(Qt::red));
        line->setZValue(-1);
    }

    return center;
}

void TreeWidget::_redrawTree(BinaryTree::Node* targetNode)
{
    m_scene->clear();
    _drawTree(m_tree->root(), 0, m_scene->width(), 0, targetNode);
}

void TreeWidget::_updateSceneRect()
{
    m_scene->setSceneRect(0, 0, qMax(int(m_scene->width()), ui->graphicsView->viewport()->width()),qMax(int(m_scene->height()), ui->graphicsView->viewport()->height()));
    _redrawTree();
}
