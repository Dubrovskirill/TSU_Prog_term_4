#pragma once

#include <QWidget>
#include <QVector>

class QGridLayout;
class HashTableCellWidget;

class HashTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HashTableWidget(QWidget *parent = nullptr);
    ~HashTableWidget();

    int findRow(int key) const;

public slots:
    void addRow(int key, const QString &value);
    bool removeRow(int key);
    void resize(int size);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void addConnection(int from, int to);
    void removeConnections(int itemIndex);
    void onValueChanged(HashTableCellWidget *item);

private:
    struct ItemData
    {
        HashTableCellWidget *ptr = nullptr;
        HashTableCellWidget *prev = nullptr;
        HashTableCellWidget *next = nullptr;

        QRect connectionRect;
        QRect baseConnectionRect(int connectionOffset) const;
        static QRect baseConnectionRect(HashTableCellWidget *from, HashTableCellWidget *to, int connectionOffset);
    };

    QVector<ItemData> m_items;
    QGridLayout *m_layout = nullptr;
    int m_baseConnectionOffset = 10;
    int m_connectionOffset = 5;
    //TODO: HashTable m_table;
};

