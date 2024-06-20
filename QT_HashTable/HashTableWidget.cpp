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
    m_layout->setSpacing(10);
    m_layout->setColumnStretch(0, 0);
    m_layout->setColumnStretch(1, 1);
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

void HashTableWidget::resetHighlight() const {
    for (int i = 0; i < m_buckets.size(); ++i) {
        BucketWidget& bucket = const_cast<BucketWidget&>(m_buckets[i]); // Снимаем const
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
            resetHighlight();
            emit cellFound(bucketIndex, key);
            return bucketIndex;
        }
        current = current->next;
    }


    return -1;
}

void HashTableWidget::addRow(int key, const QString &value) {

    resetHighlight();
    if (m_hashTable.contains(key)) {

        qDebug() << "Ошибка: Ключ" << key << "уже существует в таблице.";
        return;
    }


    m_hashTable.insert(key, value);
    int bucketIndex = m_hashTable.m_hashFunction->hash(key, m_hashTable.capacity());


    HashTableCellWidget* cell = new HashTableCellWidget(this);
    cell->setKey(key);
    cell->setValue(value);
    connect(cell, &HashTableCellWidget::valueChanged, this, &HashTableWidget::onValueChanged);


    QHBoxLayout* rowLayout = nullptr;
    if (m_layout->itemAtPosition(bucketIndex, 1) != nullptr) {
        rowLayout = dynamic_cast<QHBoxLayout*>(m_layout->itemAtPosition(bucketIndex, 1)->layout());
    }


    if (rowLayout == nullptr) {
        rowLayout = new QHBoxLayout();
        m_layout->addLayout(rowLayout, bucketIndex, 1, Qt::AlignLeft);
    }


    rowLayout->addWidget(cell);


    addNodeToBucket(bucketIndex, cell);


    update();
}

bool HashTableWidget::removeRow(int key) {
    resetHighlight();
    if (m_hashTable.erase(key)) {
        int bucketIndex = m_hashTable.m_hashFunction->hash(key, m_hashTable.capacity());
        removeNodeFromBucket(bucketIndex, key);
        return true;
    }
    return false;
}

void HashTableWidget::resize(int newSize) {
    resetHighlight();
    if (newSize <= 0) {
        return;
    }


    std::vector<std::pair<int, QString>> oldData;
    for (int i = 0; i < m_hashTable.capacity(); ++i) {
        for (const auto& node : m_hashTable.m_table[i]) {
            oldData.push_back({node.m_key, node.m_value});
        }
    }


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
    m_buckets.clear();


    m_hashTable.resize(newSize);


    m_buckets.resize(newSize);
    for (int i = 0; i < newSize; ++i) {
        m_buckets[i].indexLabel = new QLabel(QString::number(i) + ":", this);
        m_buckets[i].indexLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        m_layout->addWidget(m_buckets[i].indexLabel, i, 0, Qt::AlignRight);
    }


    for (const auto& data : oldData) {
        addRow(data.first, data.second);
    }
}

void HashTableWidget::clear() {
    resetHighlight();

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
void HashTableWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int bucketIndex = 0; bucketIndex < m_buckets.size(); ++bucketIndex) {
        NodeWidget* current = m_buckets[bucketIndex].head;

        // Пропускаем пустые корзины и корзины с одним элементом
        if (current == nullptr || current->next == nullptr) {
            continue;
        }

        while (current != nullptr && current->next != nullptr) {
            QWidget* currentWidget = current->widget;
            QWidget* nextWidget = current->next->widget;


            QPoint currentRightCenter = currentWidget->mapToGlobal(currentWidget->rect().topRight());
            currentRightCenter.setX(currentRightCenter.x() - currentWidget->rect().width() / 2);


            QPoint nextLeftCenter = nextWidget->mapToGlobal(nextWidget->rect().topLeft());
            nextLeftCenter.setX(nextLeftCenter.x() + nextWidget->rect().width() / 2);


            int arrowOffset = 15;


            QPoint arrowStart = QPoint(currentRightCenter.x() + arrowOffset, currentRightCenter.y());
            QPoint arrowEnd = QPoint(nextLeftCenter.x() - arrowOffset, nextLeftCenter.y());


            drawArrow(painter, arrowStart, arrowEnd);

            current = current->next;
        }
    }
}

void HashTableWidget::drawArrow(QPainter& painter, const QPoint& start, const QPoint& end) {
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);


    painter.drawLine(start, end);


    qreal angle = atan2(end.y() - start.y(), end.x() - start.x());


    int arrowSize = 10;
    QPointF arrowP1 = end + QPointF(arrowSize * cos(angle + M_PI / 6), arrowSize * sin(angle + M_PI / 6));
    QPointF arrowP2 = end + QPointF(arrowSize * cos(angle - M_PI / 6), arrowSize * sin(angle - M_PI / 6));


    painter.setBrush(Qt::black);
    painter.drawPolygon(QPolygonF() << end << arrowP1 << arrowP2);
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
            delete current->widget;
            delete current;
            update();
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




