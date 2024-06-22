
#pragma once

#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QLabel>
#include "../HashTable/HashTable/HashTable.h"
class QGridLayout;
class HashTableCellWidget;

class HashTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HashTableWidget(QWidget *parent = nullptr);

    ~HashTableWidget();

    int findRow(int key);

public slots:
    void addRow(int key, const QString &value);
    bool removeRow(int key);
    void resize(int size);
    void clear();
    void resetHighlight() ;
    void setHashFunction(HashFunction* newHashFunction);
    //void updateTable();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    struct NodeWidget {
        HashTableCellWidget *widget = nullptr;
        NodeWidget *next = nullptr;

        NodeWidget(HashTableCellWidget* w) : widget(w) {}
    };

    struct BucketWidget {
        QLabel *indexLabel = nullptr;
        NodeWidget *head = nullptr;

        ~BucketWidget();
    };

    void addNodeToBucket(int bucketIndex, HashTableCellWidget* cell);
    void removeNodeFromBucket(int bucketIndex, int key);
    const BucketWidget* findBucket(int key) const;
    void clearBucket(BucketWidget* bucket);
    void drawArrow(QPainter& painter, const QPoint& start, const QPoint& end);
    void clearLayout();
    void drawBorder(HashTableCellWidget* cell, const QColor& color);

private slots:
    void onValueChanged(HashTableCellWidget *item);
    void highlightCell(int bucketIndex, int key);
    void addConnection(int from, int to);
    void removeConnections(int itemIndex);



private:
    QVector<BucketWidget> m_buckets;
    QGridLayout *m_layout = nullptr;
    HashTable<QString> m_hashTable;
    HashTableCellWidget* m_targetCell = nullptr;
    QColor m_borderColor = Qt::green;


signals:
    void cellFound(int bucketIndex, int key) const;
    void isExists(int key) const;
    void isnotFound(int key) const;
};
