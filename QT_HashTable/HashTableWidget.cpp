#include <QDebug>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainterPath>
#include "HashTableCellWidget.h"

#include "HashTableWidget.h"

HashTableWidget::HashTableWidget(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QGridLayout(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(m_layout);
    setLayout(mainLayout);
    connect(this, &HashTableWidget::cellFound, this, &HashTableWidget::highlightCell);

//    QMargins margins = m_layout->contentsMargins();
//    //TODO: margin recalculating to fit all connections
//    margins.setRight(margins.right() + 15);
//    m_layout->setContentsMargins(margins);
//    //FIXME: remove block below
//    {
//        resize(10);
//        addConnection(0, 3);
//        addConnection(1, 4);
//        addConnection(2, 5);
//    }
}

HashTableWidget::~HashTableWidget()
{
    clear();
}


void HashTableWidget::highlightCell(int bucketIndex, int key) {
    if (bucketIndex == -1) {
        return;
    }

    NodeWidget* current = m_buckets[bucketIndex].head;
    while (current != nullptr) {
        if (current->widget->key() == key) {

            current->widget->setStyleSheet("background-color: green;");
            return;
        }
        current = current->next;
    }
}

void HashTableWidget::resetHighlight() {
    for (BucketWidget& bucket : m_buckets) {
        NodeWidget* current = bucket.head;
        while (current != nullptr) {
            current->widget->setStyleSheet("");
            current = current->next;
        }
    }
}

int HashTableWidget::findRow(int key) const {

    int bucketIndex = m_hashTable.m_hashFunction->hash(key, m_hashTable.capacity());


    NodeWidget* current = m_buckets[bucketIndex].head;
    while (current != nullptr) {
        if (current->widget->key() == key) {

            emit cellFound(bucketIndex, key);
            return bucketIndex;
        }
        current = current->next;
    }


    return -1;
}

void HashTableWidget::addRow(int key, const QString &value) {

    m_hashTable.insert(key, value);
    int bucketIndex = m_hashTable.m_hashFunction->hash(key, m_hashTable.capacity());


    HashTableCellWidget* cell = new HashTableCellWidget(this);
    cell->setKey(key);
    cell->setValue(value);
    connect(cell, &HashTableCellWidget::valueChanged, this, &HashTableWidget::onValueChanged);


    int row = 0;
    NodeWidget* current = m_buckets[bucketIndex].head;
    while (current != nullptr) {
        row++;
        current = current->next;
    }


    m_layout->addWidget(cell, bucketIndex, row + 1, Qt::AlignLeft);


    addNodeToBucket(bucketIndex, cell);
}

bool HashTableWidget::removeRow(int key) {
    if (m_hashTable.erase(key)) {
        int bucketIndex = m_hashTable.m_hashFunction->hash(key, m_hashTable.capacity());
        removeNodeFromBucket(bucketIndex, key);
        return true;
    }
    return false;
}

void HashTableWidget::resize(int newSize) {
    if (newSize <= 0) {
        return; // Некорректный размер
    }

    // 1. Сохраняем старые данные
    std::vector<std::pair<int, QString>> oldData;
    for (int i = 0; i < m_hashTable.capacity(); ++i) {
        for (const auto& node : m_hashTable.m_table[i]) {
            oldData.push_back({node.m_key, node.m_value});
        }
    }

    // 2. Очищаем текущее содержимое виджета
    for (BucketWidget& bucket : m_buckets) {
        // Удаляем все виджеты ячеек из корзины
        NodeWidget* current = bucket.head;
        while (current != nullptr) {
            NodeWidget* next = current->next;
            delete current->widget;
            delete current;
            current = next;
        }
        bucket.head = nullptr; // Сбрасываем указатель на начало списка
    }
    m_buckets.clear(); // Очищаем вектор корзин

    // 3. Изменяем размер хэш-таблицы
    m_hashTable.resize(newSize);

    // 4. Создаем новые корзины
    m_buckets.resize(newSize);
    for (int i = 0; i < newSize; ++i) {
        m_buckets[i].indexLabel = new QLabel(QString::number(i) + ":", this);
        m_layout->addWidget(m_buckets[i].indexLabel, i, 0, Qt::AlignLeft);
    }

    // 5. Вставляем старые данные в новую таблицу
    for (const auto& data : oldData) {
        addRow(data.first, data.second);
    }
}

void HashTableWidget::clear() {

    m_hashTable.clear();


    for (BucketWidget& bucket : m_buckets) {
        NodeWidget* current = bucket.head;
        while (current != nullptr) {
            NodeWidget* next = current->next;
            delete current->widget;
            delete current;
            current = next;
        }
        bucket.head = nullptr;
    }


    QLayoutItem* item;
    while ((item = m_layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }


    m_buckets.clear();
}

void HashTableWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);


    int lineStartY = 0;
    int lineEndY = 0;

    for (int i = 0; i < m_buckets.size(); ++i) {
        BucketWidget& bucket = m_buckets[i];
        NodeWidget* current = bucket.head;


        if (current != nullptr) {
            lineStartY = current->widget->y() + current->widget->height() / 2;
            lineEndY = lineStartY;
        }


        while (current != nullptr && current->next != nullptr) {
            int nextBucketIndex = m_hashTable.m_hashFunction->hash(current->next->widget->key(), m_hashTable.capacity());


            if (nextBucketIndex != i) {
                int lineStartX = current->widget->x() + current->widget->width();
                int lineEndX = m_buckets[nextBucketIndex].indexLabel->x() +
                               m_buckets[nextBucketIndex].indexLabel->width() / 2;

                QPainterPath path;
                path.moveTo(lineStartX, lineStartY);
                path.cubicTo(lineStartX + 20, lineStartY,
                             lineEndX - 20, lineEndY,
                             lineEndX, lineEndY);

                painter.drawPath(path);


                drawArrow(painter, lineEndX, lineEndY, lineStartX, lineStartY);
            }

            current = current->next;
        }
    }
}

// Вспомогательная функция для рисования стрелки
void HashTableWidget::drawArrow(QPainter& painter, int endX, int endY, int startX, int startY) {
    QPolygonF arrowHead;
    int arrowSize = 10;
    double angle = std::atan2(endY - startY, endX - startX);


    QPointF arrowP1(endX - arrowSize * cos(angle - M_PI / 6),
                    endY - arrowSize * sin(angle - M_PI / 6));
    QPointF arrowP2(endX - arrowSize * cos(angle + M_PI / 6),
                    endY - arrowSize * sin(angle + M_PI / 6));

    arrowHead << arrowP1 << arrowP2 << QPointF(endX, endY) << arrowP1;
    painter.setBrush(Qt::black);
    painter.drawPolygon(arrowHead);
}

void HashTableWidget::addConnection(int fromKey, int toKey) {

    int fromBucketIndex = m_hashTable.m_hashFunction->hash(fromKey, m_hashTable.capacity());
    int toBucketIndex = m_hashTable.m_hashFunction->hash(toKey, m_hashTable.capacity());


    HashTableCellWidget* fromWidget = nullptr;
    HashTableCellWidget* toWidget = nullptr;

    NodeWidget* current = m_buckets[fromBucketIndex].head;
    while (current != nullptr && fromWidget == nullptr) {
        if (current->widget->key() == fromKey) {
            fromWidget = current->widget;
        }
        current = current->next;
    }

    current = m_buckets[toBucketIndex].head;
    while (current != nullptr && toWidget == nullptr) {
        if (current->widget->key() == toKey) {
            toWidget = current->widget;
        }
        current = current->next;
    }


    if (fromWidget == nullptr || toWidget == nullptr) {
        qWarning() << "HashTableWidget::addConnection: Widgets not found for keys"
                   << fromKey << "and" << toKey;
        return;
    }


    NodeWidget* newNode = new NodeWidget(toWidget);
    newNode->next = m_buckets[fromBucketIndex].head;
    m_buckets[fromBucketIndex].head = newNode;
}

void HashTableWidget::removeConnections(int key) {
    int bucketIndex = m_hashTable.m_hashFunction->hash(key, m_hashTable.capacity());
    BucketWidget& bucket = m_buckets[bucketIndex];

    NodeWidget* current = bucket.head;
    NodeWidget* prev = nullptr;

    while (current != nullptr) {
        if (current->widget->key() == key) {
            if (prev == nullptr) {
                bucket.head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current->widget;
            delete current;
            update();
            return;
        }
        prev = current;
        current = current->next;
    }
}

void HashTableWidget::onValueChanged(HashTableCellWidget *item) {
    if (m_hashTable.contains(item->key())) {

        m_hashTable[item->key()] = QString::fromStdString(item->value().toStdString());
    }
}

void HashTableWidget::addNodeToBucket(int bucketIndex, HashTableCellWidget* cell) {
    NodeWidget* newNode = new NodeWidget(cell);
    newNode->next = m_buckets[bucketIndex].head;
    m_buckets[bucketIndex].head = newNode;
}

void HashTableWidget::removeNodeFromBucket(int bucketIndex, int key) {
    BucketWidget& bucket = m_buckets[bucketIndex];
    NodeWidget* current = bucket.head;
    NodeWidget* prev = nullptr;

    while (current != nullptr) {
        if (current->widget->key() == key) {
            if (prev == nullptr) {
                bucket.head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current->widget; // Удаляем виджет ячейки
            delete current;
            update(); // Обновляем виджет
            return;
        }
        prev = current;
        current = current->next;
    }
}

const HashTableWidget::BucketWidget* HashTableWidget::findBucket(int key) const {
    int bucketIndex = m_hashTable.m_hashFunction->hash(key, m_hashTable.capacity());
    return &(m_buckets[bucketIndex]);
}

void HashTableWidget::clearBucket(BucketWidget* bucket) {
    NodeWidget* current = bucket->head;
    while (current != nullptr) {
        NodeWidget* next = current->next;
        delete current->widget;
        delete current;
        current = next;
    }
    bucket->head = nullptr;
}


//QRect HashTableWidget::ItemData::baseConnectionRect(int connectionOffset) const
//{
//    return baseConnectionRect(ptr, next, connectionOffset);
//}

//QRect HashTableWidget::ItemData::baseConnectionRect(HashTableCellWidget *from, HashTableCellWidget *to, int connectionOffset)
//{
//    if (!from || !to) {
//        return QRect();
//    }

//    QPoint startPos = from->pos();
//    startPos.rx() += from->width();
//    startPos.ry() += from->height() / 3 * 2;
//    QPoint endPos = to->pos();
//    endPos.rx() += to->width();
//    endPos.ry() += to->height() / 3;

//    QRect rect;
//    rect.setTopLeft(startPos);
//    rect.setBottom(endPos.y());
//    rect.setRight(qMax(startPos.x(), endPos.x()) + connectionOffset);
//    return rect;
//}

